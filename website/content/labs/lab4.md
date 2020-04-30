---
title: "Lab 4: Debugging"
date: 2018-01-28
publishdate: 2018-01-28
draft: false
---

**Due:** Thursday, May 6th, 8pm

In this lab, you will get some practice debugging a few programs and, in particular, will resolve some of the errors we described in class. In some of the tasks, you will also become more familiar with GDB, a popular debugger.

As you work through this lab, you may want to refer to our [Debugging Guide](https://uchicago-cs.github.io/debugging-guide/), which covers (and expands on) many of the topics we covered in class.

## Creating your lab repository

Like previous labs, we will provide you with an  *invitation URL* that will allow you sign up for the lab assignment on GitHub, and which will result in the creation of a repository called `2020-lab4-GITHUB_USERNAME` inside our `cmsc22000-labs` organization on GitHub. Like previous labs, your repository will be seeded with some files for the lab, which will be contained in four `task` directories inside the repository.

Please note that, while you will be modifying some of the files we give you, in this lab we will mostly be looking at the answers you provide to a number of questions. Instead of adding them to a "tasks.txt" file like you did in past labs, you will enter these answers directly into Gradescope.


## Task 1: Compiler/Linker Error Debugging

(25 points)

As mentioned in class, this kind of debugging is easier to do without using a debugger. How you debug this next file is up to you.

Compile each C file in the task 1 directory (you can simply run `gcc <filename>.c -o <filename>`, e.g., `gcc task1a.c -o task1a`). They will each produce a compiler/linker error (and/or warnings). For each C file, answer the following questions on Gradescope:

* What is causing the error/warning? Make sure to include the exact line that causes the error/warning (and remember that this might not be the same line number reported by the compiler! You must provide the number of the line that is *directly* responsible for the error).
* How did you fix the error/warning?

Make sure to also fix the errors in the C file (and make sure to commit and push this fix to your repository).


## Task 2: GDB Warmup

(25 points)

GDB, short for GNU Debugger, is a debugger for Unix-like systems and works for languages like C and C++. It essentially allows you to inspect and dissect your program as it is running, which is super helpful for finding errors.

{{% warning %}}
Besides being familiar with GDB on the command-line, you may want to also become familiar with how graphical debuggers work. Here are a few options you may want to check out:

* [gdbgui](https://gdbgui.com/) allows you to work with GDB through a browser-based interface, allowing you to better visualize the state of your program while you're debugging it.
* VSCode has built-in [debugging support](https://code.visualstudio.com/docs/editor/debugging).
* Most IDEs, including CLion, have [excellent built-in debuggers](https://www.jetbrains.com/clion/features/run-and-debug.html).

While the lab instructions are written for the terminal-based gdb, we encourage you to learn about a graphical debugger on your own after you've completed this lab. Take into account that these graphical debuggers all use gdb in the backend, which means that everything you'll learn about the terminal-based gdb will translate well into a graphical debugger.
{{% /warning %}}

Compile your program with the following command:

    gcc -g task2.c -o task2

Notice the use of the `-g` flag. This enables built-in debugging support. To start gdb, run the following command:

    gdb ./task2

`gdb` starts the debugger, and `./task2` specifies the program we are debugging. Now that `gdb` is running, you can start the program by typing `run`. The program will then run as normal but, if we want to be able to stop at certain points in the program, we need to set *breakpoints*. These could be done in one of the following ways using the command `break`:

    break task2.c:line_number
    break function_name

The first one sets a breakpoint at the provided line number, and the second sets it at the start of the provided function. You can set multiple breakpoints. Notice that, to break right when the program starts, you can just set a breakpoint on the `main` function:

    break main

When you reach a breakpoint, execution of the program will pause at that breakpoint. If you want to continue running the program, then type `continue`. Careful: if you type `run`, it will restart the execution of the program from the beginning. 

To look at all the breakpoints you have, run `info breakpoints`, and you will see a numbered list of breakpoints. Run `delete` to delete all breakpoints. If you specify a number with delete, for example `delete 2`, the breakpoint corresponding to that number on the list will be deleted.

It would be annoying to have to set a breakpoint for every line of code you want to look at, especially if they are consecutive. A useful command for this is `next`. Let's say you reach a breakpoint (in this case, on line 35 of `task2.c`):
    
    Breakpoint 4, main () at task2.c:35
    35	    *p += 5;
    (gdb) 

At this point, line 35 has not yet been run. If you type `next`, gdb will run line 35, and will advance to the *next* line:

    Breakpoint 4, main () at task2.c:35
    35	    *p += 5;
    (gdb) next
    36	    c = 8;
    (gdb) 
    
Please note that, if you want to run through the next lines, you don't have to keep typing `next`. After using `next` a first time, you can just hit the Enter key to keep running through the program line by line.

A similar command is `step` which, like `next`, will execute the next line of code, but will handle function calls differently. If you are in function `foo`, and `foo` calls `bar`, `step` allows you to go line-by-line through `bar` as well when it is called in `foo`, whereas `next` would execute `bar` without letting you step through it and execute the next line of `foo`. Look at the example below:


    int bar() {
        int x = 1;
        printf(“I’m in bar!”);
        return x;
    }

    int foo() {
        printf(“I’m in foo!”);
        int x = bar();
        x++;
        return x;
    }

When you get to the second line of `foo()`, if you use `step` you will go to the first line of `bar` (`int x = 1;`), whereas if you use `next` you will go to the next line in `foo` (`x++;`). If you do use `step`, once you return from `bar`, you then execute the next line in `foo` (`x++;`).

As you are stepping through your program, you might want to be able to see the values of certain variables. You can do this by running the `print` command. `print val`, for example, will print the value `val`. With pointers, you can use `print *p` to print out the value pointed to by p. If you want to print in hex, use `print/x val`, and to print in binary use `print/b val`

There is also a useful command to keep track of when a variable changes. This command is `watch`. If you want to keep track of when the variable `x` changes, type `watch x`. Every time it is changed when you run your program or execute a line of code, the program will stop and print the old and new values.

When you're done using gdb, you can exit by typing `quit` or by pressing Ctrl+D.

Now that you know these commands, let’s have some practice with them! Using gdb, answer the following questions on Gradescope:

1. At what line(s) does the value of variable `c` change?
2. What does the code at line 12 do?
3. What is the value pointed to by pointer `p` after line 42?
4. Set a breakpoint at line 38. Over lines 38-41, three operations are performed on the variable `a`. What are these operations? (explain them, do not just copy/paste the code)
5. What is the return value of the function `num()` in hexadecimal?

## Task 3: Runtime Error Debugging

(30 points)

Runtime errors make the program crash while it is running, and sometimes they are hard to find because the compiler doesn’t always give particularly informative error messages. GDB is a really useful tool because it helps you pinpoint, for example, where a segfault is happening and what might be causing it. You can use all the commands we’ve already talked about, but there are a couple of additional ones that might be useful.

`kill` will stop the current run of the program. You can then restart it by running `run` again. Frequently you’ll want to run a program until it segfaults, `kill` it (stop the program without exiting gdb), add breakpoints, and then run it again.

`backtrace` will print out the call stack. What this means is that it will print the function being called as well as the function that called that, and the function that called that, etc.

`frame n` (where `n` is the frame number from the backtrace) allows you to go to the function in that frame and see what line in that particular function caused the error.

Compile `task3.c` (don't forget to include the `-g` option! Otherwise you won't be able to debug it). Now run it; the program should segfault. Now it’s time to debug! There are three errors in this file. For each error, answer the following question on Gradescope:

* Where was the segfault? Give the function, line number, and copy-paste the line of code itself. What was causing the segfault and how did you fix it?

It is a good idea to fix one error before moving on to the next. Make sure to also commit and push your fix for each segfault!

You must also answer the following question for the entire task:

* Describe the steps you took in gdb to narrow down the exact location of one of the segfaults. You can also copy-paste the contents of one debugging session with gdb, with a brief note at the end explaining how that debugging session narrowed down the location of the error.

## Task 4: Logic Error Debugging

(20 points)

Logic errors can happen even when your program compiles and runs, but may result in incorrect behavior. The commands we went through in the warmup can help you find logic errors by allowing actions such as stepping through the program line-by-line, printing variables, and seeing when variables are changed.

Compile `task4.c` and run it. As you can see from the print messages, the variables don’t have the expected values! Use gdb to find the five errors. For each error you find, answer the following questions on Gradescope:

* Copy-paste the relevant lines of code, explain what is wrong with them, and then copy-paste the fixed code (with a brief explanation of how you fixed the code).

Please note that, while you might also be able to find the logic errors just by looking at the code, that will rob you of the opportunity to practice using gdb to step through a running program.

## Submitting your lab

Please note that you will not be submitting your code through Gradescope. Instead, make sure that the questions posed above are answered on Gradescope. That said, we still need you to push your code in case we need to look at any of your code (but we will not be grading the code itself).




