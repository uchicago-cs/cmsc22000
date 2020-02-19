---
title: "Lab 4: Debugging"
date: 2018-01-28
publishdate: 2018-01-28
draft: true
---

**Due:** Thursday, May 2nd, 2:30pm

In this lab, you will get some practice debugging a few programs and, in particular, will resolve some of the errors we described in class. In some of the tasks, you will also become more familiar with GDB, a popular debugger.

As you work through this lab, you may want to refer to our [Debugging Guide](https://uchicago-cs.github.io/debugging-guide/), which covers (and expands on) many of the topics we covered in class.

## Task 0: Pulling from upstream

(0 points)

You should already have the "upstream" remote set up in your repository. If you do, simply run

```
$ git pull upstream master
```

to get the files for this lab. If you don't have the "upstream" remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).

This lab is organized into folders, one for each task.

## Task 1: Compiler/Linker Error Debugging

(25 points)

As mentioned in class, this kind of debugging is easier to do without using a debugger. How you debug this next file is up to you.

Compile each C file in the task 1 directory. In task1.txt answer the following questions for each

1. List the line number that causes the error. Remember that this might not be the same line number reported by the compiler! You must provide the number of the line that is directly responsible for the error.
2. Fix the errors (do this in the C file directly)


## Task 2: GDB Warmup

(25 points)

GDB, short for GNU Debugger, is a debugger for Unix-like systems and works for languages like C and C++. It essentially allows you to inspect and dissect your program as it is running, which is super helpful for finding errors.

{{% warning %}}
{{% md %}}
There is also a fairly new GUI for GDB called [gdbgui](https://gdbgui.com/) which allows you to work with GDB through a browser-based interface, allowing you to better visualize the state of your program while you're debugging it. While the lab instructions are written for the terminal-based gdb, we encourage you to learn about `gdbgui` on your own *after* you've completed these labs (many of the concepts and commands we explore in this lab will make it easier to understand `gdbgui`). In particular, you may want to try to debug some of the programs in this lab using `gdbgui` (note: `gdbgui` is installed on the CS machines)
{{% /md %}}
{{% /warning %}}

Compile your program with the following command:

    gcc -g task2.c -o task2

Notice the use of the `-g` flag. This enables built-in debugging support. To start gdb, run the following command:

    gdb ./task2

`gdb` starts the debugger, and `./task2` specifies the program we are debugging. Now that `gdb` is running, you can start the program by typing `run`. The program will then run as normal but, if we want to be able to stop at certain points in the program, we need to set *breakpoints*. These could be done in one of the following ways using the command `break`:

    break task2.c:line_number
    break function_name

The first one sets a breakpoint at the provided line number, and the second sets it at the start of the provided function. You can set multiple breakpoints. To continue the program execution, you can type `continue`. If you type `run`, it will restart the execution of the program. To look at all the breakpoints you have, run `info breakpoints`, and you will see a numbered list of breakpoints. Run `delete` to delete all breakpoints. If you specify a number with delete, for example `delete 2`, the breakpoint corresponding to that number on the list will be deleted.

It would be annoying to have to set a breakpoint for every line of code you want to look at, especially if they are consecutive. Two useful commands to know for this are `step` and `next`. These both will execute the next line of code. The main difference between the two is how they handle function calls. If you are in function `foo`, and `foo` calls `bar`, `step` allows you to go line-by-line through `bar` as well when it is called in `foo`, whereas `next` would execute `bar` without letting you step through it and execute the next line of `foo`. Look at the example below:


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

Now that you know these commands, let’s have some practice with them! Using gdb, answer the questions in `task2.txt` about `task2.c`.

1. At what line(s) does the value of variable `c` change?
2. What does the code at line 12 do?
3. What is the value pointed to by pointer `p` after line 42?
4. Set a breakpoint at line 38. Over lines 38-41, three operations are performed on the variable `a`. What are these operations? (explain them, do not just copy/paste the code)
5. What is the return value of the function `num()` in hexadecimal?

## Task 3: Runtime Error Debugging

(25 points)

Runtime errors make the program crash while it is running, and sometimes they are hard to find because the compiler doesn’t always give particularly informative error messages. GDB is a really useful tool because it helps you pinpoint, for example, where a segfault is happening and what might be causing it. You can use all the commands we’ve already talked about, but there are a couple of additional ones that might be useful.

`kill` will stop the current run of the program. You can then restart it by running `run` again. Frequently you’ll want to run a program until it segfaults, `kill` it (stop the program without exiting gdb), add breakpoints, and then run it again.

`backtrace` will print out the call stack. What this means is that it will print the function being called as well as the function that called that, and the function that called that, etc.

`frame n` (where `n` is the frame number from the backtrace) allows you to go to the function in that frame and see what line in that particular function caused the error.

Compile `task3.c` and run it. You will segfault. Now it’s time to debug! There are three errors in this file. For each error, answer the following questions in `task3.txt`. It is a good idea to fix one error before moving onto the next.

1. Where was the segfault? Give the function, line number, and the line of code itself.
2. What variables were involved?
3. Why was this causing an error?
4. What gdb commands did you use to debug this, and what did they help you with?
5. Fix the errors in `task3.c` (do this in the C file directly)


## Task 4: Logic Error Debugging

(25 points)

Logic errors can happen even when your program compiles and runs, but may result in incorrect behavior. The commands we went through in the warmup can help you find logic errors by allowing actions such as stepping through the program line-by-line, printing variables, and seeing when variables are changed.

Compile `task4.c`. As you can see from the print messages, the variables don’t have the expected values! Use gdb to find the five errors. For each error you find, answer the following questions in `task4.txt`.

1. What line of code was causing the error? Give the line number and the actual code.
2. What variables were involved?
3. Why was this causing an error?
4. What gdb commands did you use to debug this, and what did they help you with?
5. Fix the errors in `task4.c` (do this in the C file directly)



### Submitting your lab

Before submitting, make sure you've added, committed and pushed all your work in the `lab4` directory (remember you can run `git status` to check this). Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab4
    chisubmit student assignment submit lab4

