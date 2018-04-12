---
title: "Lab 3: Make"
date: 2018-01-28
publishdate: 2018-01-28
---

**Due:** Thursday, April 19th, 4pm

In the class project, you will be working with a large C project called [Redis](https://redis.io/) that is composed of hundreds and hundreds of C files. How do these files become the program called `redis`? In this lab, we’ll explore the ways a program can be “built”--that is, the way that  source code is turned into binary code so that a computer can execute it.  In some cases, “building” may refer to compiling a single file, but usually it refers to the whole process of linking and creating a project: which can include linking, compiling, and running tests. We’ll look at testing in later labs, and for this lab we’ll focus on the “make” command as a way to compile and build projects. 

{{% warning %}}
**Note:** For some of these tasks, you may be tempted to look at the Makefiles included with libgeometry, and copy-paste parts of them into your Makefiles. There are two important reasons not to do this:

1. It is important that you understand what you're doing in each of the tasks in this lab. If you get stuck and you're not sure how to proceed, ask us (either during the lab session or on Piazza). If you just copy-paste from one of our Makefiles, you won't understand how those parts of the Makefile work.
2. The tasks in this lab actually ask you to modify a Makefile in ways that are different from how the libgeometry Makefile is written. If you just copy-paste from our Makefile, it is almost certain we will be able to tell that you did so. 

That said, by the end of this lab you should be able to understand almost everything that is contained in the libgeometry Makefiles. However, it is important that you perform all the intermediate tasks before you get to that point.

{{% /warning %}}

Finally, for your reference, you may find the following resources helpful:

- The GNU `make` documentation, available in full [here](https://www.gnu.org/software/make/manual/html_node/index.html); and
- The `make` and `gcc` man pages, available in your terminal through `man make`
  and `man gcc`.


## Task 0: Pulling from upstream

(0 points)

You should already have the "upstream" remote set up in your repository. If you do, simply run

```
$ git pull upstream master
```

to get the files for this lab. If you don't have the "upstream" remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).

This lab is organized into folders, one for each task. You'll be provided with the source for a program or library in each task, and you'll write the `Makefile` for that task.

## Task 1: A simple `Makefile`

(15 points)

In the `task1` directory, you'll see a simple program (`hello.c`) that prints "Hello there" to the screen and exits. As you've done in previous courses, you can compile and run the program like so:

```
$ gcc -o greet greet.c
$ ./greet
```

And when you're done, you can always remove the executable (also called the binary) to prevent adding it to version control like so:

```
$ rm -f greet
```

Now, let's say you want to change your program so that instead of printing "Hello there", it prints "General Kenobi!" You either have to hit the up arrow on your keyboard a million times, or remember `gcc -o hello hello.c`. And perhaps you want to enable optimizations, enable all the warnings, and enable debugging symbols (so you can use `gdb`):

```
$ gcc -O2 -Wall -Wextra -g -o greet greet.c
```

Yuck! Who likes typing all that every time? Let's simplify this process using `make`. `make` is a simple tool that does one and only one thing: it looks for a file in the current directory called `Makefile`, and executes commands according to **rules** specified in the `Makefile`. A rule looks something like this:

```
rule-name: prerequisite
	command
```

In general, rules can have any number of (or zero) prerequisites (separated by spaces), and any number of (or zero) commands (separated by newlines). It's important to note that while `make` is probably most often used with C programs, `make` is a generic tool supporting arbitrary commands. Here's a simple "hello world" `Makefile`, that uses the shell command "echo" (which does exactly what you think it does):

```
hello:
	echo "Hello"

world: hello
	echo "World!"
```

We can use this `Makefile` like so:

```
$ make hello
echo "Hello"
Hello
$ make world
echo "Hello"
Hello
echo "World!"
World!

```

{{% warning %}}
**Beware the curse of the tabs and the missing separators!** 

If you get an error message like this:

```
Makefile:2: *** missing separator.  Stop.
```

This means there may have been an issue when copy-pasting from this page to the `Makefile`. More specifically, Makefiles use [tab characters](https://en.wikipedia.org/wiki/Tab_key) to indent the commands in a rule. This makes it challenging to edit Makefiles if you have set up your editor to use spaces to indent your code. If you're getting the "missing separator error", it's likely that your editor automatically converted the tab characters to spaces.

If that is the case, you can tell `make` to use spaces instead of tabs by adding the following at the top of your Makefile:

    .RECIPEPREFIX +=
{{% /warning %}}

First, notice how `make hello` prints both the command that is run by that rule, as well as the result of running that command. Next, notice how since the `world` rule depends on the `hello` rule, the `hello` rule is executed first when we run `make world`. It’s important to note that the topmost rule in a file (that is, the rule defined the earliest in the file) is the **default rule**, which means that it will be executed when calling `make` with no arguments. In the case above, `make` and `make hello` will produce identical output. 

One more thing to note is that since `make` was designed to work with C, it also has a number of *implicit rules*. For example, run the following to delete the `greet` program we created earlier:

    rm -f greet

Now, run this:

    make greet

Our Makefile doesn't have a `greet` rule and, yet, because there is a `greet.c` file, `make` interprets that as "I should generate a `greet` executable from `greet.c`". Similarly, if you run this:

    make greet.o

`make` will generate an object file from `greet.c` (but won't generate an executable).

The problem here is that if we have a rule called `clean`, we can’t ever create a file called `clean.c` in the current directory, or `make` will get confused as to whether it’s supposed to use our rule or apply an implicit rule. Poor design, sure, but it can be mitigated by adding the following to your `Makefile`:

```
.PHONY: rule1 rule2 ...etc
```

Where rule1 and rule2 and so on are the names of the rules you’ve defined in your `Makefile`.

For this task, create a file called `Makefile` in the `task1` directory with two rules:

1. A rule called `all` (a common default rule name) that compiles the program using `gcc`; and
2. A rule called `clean` that removes the binary produced by `all`.

You can run the rules in your `Makefile` by running `make all` (or, since `all` is the default rule, just running `make`) and `make clean`. Add your `Makefile` to git, commit it, and push.




## Task 2: Let's generalize!

(15 points)

What happens if we want to change the name of the binary to `shblah`? We'd have to go into our `Makefile` and replace every occurrence of `hello` with `shblah`. That might be fine for now, but when our `Makefile`s have more rules and are being used to compile lots of different C files, that simply won't do. Fortunately, `make` includes a notion of **variables** that we can use here. Working with the example from task 1, they work like so:

```
COMMAND = echo

hello:
	$(COMMAND) "Hello"

world: hello
	$(COMMAND) "World!"
```

This `Makefile` works the same as it did above, but now if we ever want to change `echo` to a different command, we need only change it in one place. In general, variables are used to avoid repeating code between rules. If we have multiple rules specified for compiling different C files, and the only flag they don't share is the output flag, we wouldn't want to type out `gcc -g -O2 -Wall -Wextra -g -o hello hello.c`. We'd rather type `gcc $(CFLAGS) -o hello hello.c`. That way, if we then want to change the optimization level or add a warning flag, we need only change the `CFLAGS` variable.

For task 2, copy your `Makefile` from task 1 into the `task2` directory, and add the following four variables:

1. A variable called `BIN` that is used for passing the name of the binary to
   `gcc` and `rm`; and
2. A variable called `CC` that specifies the C compiler to be used (in our case
   this is just gcc, but it's important to have this as an option; for example, we may want to use a different C compiler, like `clang`); and
3. A variable called `CFLAGS` (a very common practice) that holds the common
   extra options passed into `gcc` (you should include the optimization, warning, and debug flags in the example from task 1); and
4. A variable called `RM` that specifies the `rm` command along with its
   options.

Then, update your rules to use the newly-defined variables (that is, replace instances of `gcc` with `$(CC)`, and so on). You should make a commit at this point.

## Task 3: Building a (somewhat) realistic library

(15 + 20 points)

This task is split into two phases: the first will help you familiarize yourself with the structure of a project with multiple files, and the second will actually have you build the project as a library.

In the task 3 directory, you’ll see a new program structure. We have two header files in the `include` directory, and three C files in the `src` directory. Basically, we have `obi_wan.c` and `obi_wan.h`, which define a function called `hello_there`, that prints `Hello there` to the screen. Similarly, we have `grievous.c` and `grievous.h`, which define `general_kenobi`, which prints `General Kenobi!` to the screen. `main.c` defines a `main` function that calls `hello_there` and `general_kenobi`. To compile these files together, recall from 152 / 162 that you have to pass them to `gcc` like so:

```
$ gcc -g -O2 -Wall -Wextra -g src/main.c src/obi_wan.c src/grievous.c -o hello
```

There’s a problem with this: how does `gcc` know where to find the header files? For this we use the `-I` flag:

```
$ gcc -g -O2 -Wall -Wextra -g -I ./include/ src/main.c src/obi_wan.c src/grievous.c -o hello
```

Yuck! Let’s streamline this. Copy your `Makefile` from the previous task and add a new variable, `SRCS`, that defines the list of source files to pass to `gcc`. Furthermore, you’ll need to modify your `CFLAGS` variable to add the new `-I ./include/` option, so that `make` knows where to find our header files. You should make a commit at this point.

Now on to phase 2. Due to overwhelming demand from your userbase, you’re going to package these files up as a **library** that other people can include in their projects. This means that instead of producing an executable file (that we can run like `./hello`), you’re going to produce a dynamically-linked library, like the ones we described in class.

First, remove the `main.c` file - we don’t want `main` in a library. From inside the `task3` directory:

```
$ git rm src/main.c
```

Note that the `git rm` command both removes the file from the filesystem, *and* removes it from version control. You should now make a commit with the message “Starting task 3 phase 2”.

First things first: we’re no longer building a binary called `hello`, we’re building a **shared object file** called `libstarwars.so`. For starters, go ahead and change your `BIN` variable to be called `LIB`, and have it specify `libstarwars.so`. At this point, we need to radically change the compilation structure of our project. Up till now, we’ve been basically asking `gcc` to compile our set of C files, take the resultant machine code, and mash it together into a single file that we can run. Instead, to build a library, we’re going to invoke `gcc` *individually*, once per file that’s part of the compilation, and ask it to produce an **object** file. Then, we’ll invoke `gcc` one more time, asking it to mash all the object files together into one large **shared object** file.

To compile a file `hello.c` into an object file `hello.o`:

```
gcc -Wall -Wextra -O2 -g -fPIC -o hello.o hello.c
```

Note the presence of the new `gcc` flag `-fPIC`. This flag tells `gcc` to enable position-independent code. Position-independence is beyond the scope of this lab, but it’s necessary for building shared libraries. Accordingly, you’ll need to add `-fPIC` to your `CFLAGS`.

To build one or several object files into a shared library, we would do this:

```
gcc -shared -o libhello.so hello.o
```

The `-shared` option, unsurprisingly, tells `gcc` to output a shared object file.

Add a rule to your `Makefile` for `obi_wan.o` and `grievous.o`, specifying how to compile them, using your previously-defined variables. Then, make the `all` rule depend on each of those new object rules. Finally, change the `all` rule to compile those two `.o` files into a shared library. You’ll likely want an `OBJS` variable, which defines `.o` files for each `.c` file in the `SRCS` variable. You should make a commit at this point.

## Task 4: Maximum modularity and elegance

(15 points)

In task 3, you defined separate, explicit rules for each object file in the project. This has a number of disadvantages: you repeat a lot of code, and if you want to, say, change the name of a variable or update the structure of the compilation command, you have to make those changes in multiple places. To combat this problem, `make` includes many built-in variables and functions to aid in writing concise, elegant `Makefile`s. Here are some of the more useful variables and functions:

- `$@` is the name of the current rule
- `$^` is the names of all the prerequisites, separated by spaces
- `$<` is the name of the first prerequisite
- There are three different patterns for substituting text:
  - In a prerequisite, you can do substitution like so: `%.o:%.c`. This means: “take a file and substitute the extension `.o` for the extension `.c`”.
  - In a variable, you can do substitution like so: `FOO = $(BAR:.txt=.pdf)`. This means: “take the `BAR` variable, substitute the `.txt` extension for `.pdf` in all files in `BAR`, and then save the result in `FOO`.”
 - Inside a rule, you can use the `patsubst` function like so: `gcc $(patsubst %.o,%.d,$@)`. This means: “take the name of the current rule, substitute the extension `.o` for `.d`, and pass that file to gcc".

Finally, rules can have variable names: if you want to parameterize a rule so that it works for any files in a list of files, you could for example name a rule `$(SRCS)`.

Given this information, take your `Makefile` from task 3, copy it to the task 4 directory, and modularize it: you should have no hardcoded rules or values, except for flags/filenames/etc that only apply to one specific rule. Note that there are possibly many correct ways to do this. You should make a commit at this point.


## Task 5: Linking with your library

(20 points)

At this point, you have a Makefile that produces a `libstarwars.so` library. For this final task, you must write, inside the `task5` directory, a C file that uses that library, and a Makefile that correctly builds and runs your program. We have not explicitly explained some of the steps that will be required to do this, but you may use the `Makefile` from the `samples/` directory in [libgeometry](https://github.com/uchicago-cs/cmsc22000/tree/master/examples/libgeometry) as a guide. However, it is not enough for you to copy-paste parts of that `Makefile`: your `Makefile` for this task must be annotated with comments (comments in Makefiles begin with `#`). These comments must explain what each rule does, and you must explain any detail or feature that was not explicitly explained earlier in the lab.

You must also include a `readme.txt` file with instructions on how to build and run your program. Remember that, by default, programs running on a Linux system will look for shared libraries in specific locations, so you must tell us how we must run your program so that it can correctly find the `libstarwars.so` library when it runs.


### Submitting your lab

Before submitting, make sure you've added, committed and pushed all your work in the `lab3` directory (remember you can run `git status` to check this). Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab3
    chisubmit student assignment submit lab3

