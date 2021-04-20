Homework 4: Debugging
=====================

**Due:** Wednesday, April 28th, 8pm CDT

In this homework, you will get some practice debugging a few programs and, in
particular, will resolve some of the errors we described in class. In
some of the tasks, you will also become more familiar with GDB, a
popular debugger.

Some of the tasks in this homework will require reading through the `Debugging
Guide <https://uchicago-cs.github.io/debugging-guide/>`__, which covers
(and expands on) many of the topics we covered in class. You can either read through
the guide before starting the homework, or read through the pertinent sections as needed
(we will point which ones you need to read throughout the homework).

Creating your homework repository
---------------------------------

Like previous homeworks, we will provide you with an *invitation URL* that
will allow you sign up for the homework assignment on GitHub, and which will
result in the creation of a repository called
``2021-hw4-GITHUB_USERNAME`` inside our ``uchicago-cmsc22000`` organization
on GitHub. Like Homework #3, your repository will be seeded with some files
for the homework, TODO

Please note that, while you will be modifying some of the files we give
you, in this homework we will mostly be looking at the answers you provide to
a number of questions on Gradescope. Nonetheless, you should still push
your changes to your repository, in case we need to look at your code.



Task 1: Compiler/Linker Error Debugging
---------------------------------------

(XX points)

Read the `Debugging
Guide <https://uchicago-cs.github.io/debugging-guide/>`__ up to (and including)
the "Build Errors" section (i.e., stop when you get to "Runtime Errors").

Your repository includes the following two files:

* ``examples/compiler-error.c``: This file will produce a compiler error when compiled.
* ``examples/compiler-warning.c``: This file will compile, but will produce a compiler warning.

Compile each of these files (you can simply run
``gcc <filename>.c -o <filename>``). Your goal is to fix the code to address the
error or warning in each of them (note: you are not allowed to just comment out
the responsible line of code). On Gradescope, you must provide the
following information for each file:

-  In each file, there is a singular line that is responsible for the error or warning.
   You must show the "before" and "after" version of that line (i.e., before you fixed
   the code, and after you fixed the code). Remember that the line reported
   by the compiler may not be the one responsible for the error/warning!
-  Briefly describe what was causing the error/warning and how you fixed it.

Make sure to actually fix the errors in the C file (and make sure to commit
and push this fix to your repository).

GDB Warmup
----------

Read up to, and including, the "Using a debugger" section of the `Debugging
Guide <https://uchicago-cs.github.io/debugging-guide/>`__ (i.e., stop when you
get to "Preemptive Techniques"). The guide
itself does not go into details on how to use a debugger, like GDB,
to debug these kind of errors. That is what we will do in this section
of the homework.

GDB, short for GNU Debugger, is a debugger for Unix-like systems and
works for languages like C and C++. It essentially allows you to inspect
and dissect your program as it is running, which is super helpful for
finding errors.

.. note::

    Besides being familiar with GDB on the command-line, you
    may want to also become familiar with how graphical debuggers work. Here
    are a few options you may want to check out:

    -  `gdbgui <https://gdbgui.com/>`__ allows you to work with GDB through
       a browser-based interface, allowing you to better visualize the state
       of your program while you’re debugging it.
    -  VSCode has built-in `debugging
       support <https://code.visualstudio.com/docs/editor/debugging>`__.
    -  Most IDEs, including CLion, have `excellent built-in
       debuggers <https://www.jetbrains.com/clion/features/run-and-debug.html>`__.

    While the lab instructions are written for the terminal-based gdb, we
    encourage you to learn about a graphical debugger on your own after
    you’ve completed this lab. Take into account that these graphical
    debuggers all use gdb in the backend, which means that everything you’ll
    learn about the terminal-based gdb will translate well into a graphical
    debugger.

Your repository includes an ``examples/gdb-warmup.c`` file that we will
use to familiarize ourselves with GDB. From inside the ``examples/`` directory,
compile the program with the following command:

::

   gcc -g gdb-warmup.c -o gdb-warmup

Notice the use of the ``-g`` flag. This enables built-in debugging
support. To start gdb, run the following command:

::

   gdb ./gdb-warmup

``gdb`` starts the debugger, and ``./gdb-warmup`` specifies the program we
are debugging. Now that ``gdb`` is running, you can start the program by
typing ``run``. This program won't actually print anything and, if you
look at the code, it doesn't do anything particularly useful, but
it will allows us to showcase some simple GDB commands.

For example, we may want to stop at certain points in the program. We can
do this by setting *breakpoints*. These could be done in one of the following ways using
the command ``break``:

::

   break gdb-warmup.c:line_number
   break function_name

The first one sets a breakpoint at the provided line number, and the
second sets it at the start of the provided function. You can set
multiple breakpoints. Notice that, to break right when the program
starts, you can just set a breakpoint on the ``main`` function:

::

   break main

When you reach a breakpoint, execution of the program will pause at that
breakpoint. If you want to continue running the program, then type
``continue``. Careful: if you type ``run``, it will restart the
execution of the program from the beginning.

To look at all the breakpoints you have, run ``info breakpoints``, and
you will see a numbered list of breakpoints. Run ``delete`` to delete
all breakpoints. If you specify a number with delete, for example
``delete 2``, the breakpoint corresponding to that number on the list
will be deleted.

It would be annoying to have to set a breakpoint for every line of code
you want to look at, especially if they are consecutive. A useful
command for this is ``next``.

Let's give all of this a try. Make sure you are running GDB as described
earlier:

::

   gdb ./gdb-warmup

Then, from the GDB prompt, set the following breakpoint:

::

    break gdb-warmup.c:35

Now, run the program (by typing ``run`` in the GDB prompt). It should break at line 35, showing something like this:

::

    Breakpoint 1, main () at gdb-warmup.c:35
    35	    *p += 5;


At this point, line 35 has not yet been run. If you type ``next``, gdb
will run line 35, and will advance to the *next* line:

::

   Breakpoint 1, main () at gdb-warmup.c:35
   35      *p += 5;
   (gdb) next
   36      c = 8;
   (gdb) 

Please note that, if you want to run through the next lines, you don’t
have to keep typing ``next``. After using ``next`` a first time, you can
just hit the Enter key to keep running through the program line by line.

A similar command is ``step`` which, like ``next``, will execute the
next line of code, but will handle function calls differently. If you
are in function ``foo``, and ``foo`` calls ``bar``, ``step`` allows you
to go line-by-line through ``bar`` as well when it is called in ``foo``,
whereas ``next`` would execute ``bar`` without letting you step through
it and execute the next line of ``foo``. Look at the example below:

::

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

When you get to the second line of ``foo()``, if you use ``step`` you
will go to the first line of ``bar`` (``int x = 1;``), whereas if you
use ``next`` you will go to the next line in ``foo`` (``x++;``). If you
do use ``step``, once you return from ``bar``, you then execute the next
line in ``foo`` (``x++;``).

As you are stepping through your program, you might want to be able to
see the values of certain variables. You can do this by running the
``print`` command. ``print val``, for example, will print the value
``val``. With pointers, you can use ``print *p`` to print out the value
pointed to by p. If you want to print in hex, use ``print/x val``, and
to print in binary use ``print/b val``

There is also a useful command to keep track of when a variable changes.
This command is ``watch`` (careful: you can't use this command before
you start running the program in GDB; otherwise, GDB won't know what
variables are currently in scope). If you want to keep track of when the
variable ``x`` changes, type ``watch x``. Every time it is changed when
you run your program or execute a line of code, the program will stop
and print the old and new values (note that it will break in the line
*after* the variable was changed).

When you’re done using gdb, you can exit by typing ``quit`` or by
pressing Ctrl+D.

If you'd like to practice using these commands a bit more, try doing
the following (you don't have to answer these questions
on Gradescope; they are just for you to practice):

- Set a breakpoint at the start of the ``main`` function.
  Can you find the line(s) where the value of variable ``c`` changes?
- What is the value pointed to by pointer p after line 42?
- Set a breakpoint at line 38. Print the value of variable ``a`` and step through lines 38-41,
  then print the value of variable ``a`` after line 41.
- What is the return value of the function ``num()`` in hexadecimal?

You can find the answers to these questions at the end of this homework.

The Micro Editor
---------------

TODO: Describe what it is and how to build. Source: https://viewsourcecode.org/snaptoken/kilo/

Task 1: Stepping Through the Micro Editor Code
----------------------------------------------

(XX points)

TODO: Exercise where they have to set breakpoints in the Micro code and answer some
basic questions about what is happening to certain variables.


Runtime Error Debugging
-----------------------

Runtime errors make the program crash while it is running, and sometimes
they are hard to find because the compiler doesn’t always give
particularly informative error messages.

For example, your repository includes an ``examples/sefault.c`` that will
crash with a segmentation fault when run:

```
$ gcc -g segfault.c -o segfault
$ ./segfault
Segmentation fault (core dumped)
```

Segmentation faults (or "segfaults") typically arise when we access memory we shouldn't
be accessing (e.g., by using an uninitialized pointer). While we can
sometimes spot the issue by looking at the code, it would be nice
to know exactly where the segfault is happening.

GDB is a really useful tool because it helps you pinpoint where a segfault is
happening and what might be causing it. You can use all the commands
we’ve already talked about (e.g., to step through a program line
by line until it segfaults), but there are a couple of additional ones
that might be useful.

``backtrace`` will print out the call stack. What this means is that it
will print the function being called as well as the function that called
that, and the function that called that, etc. Using this command
after a segfault in GDB can often tell us exactly what is causing the
segfault.

``frame n`` (where ``n`` is the frame number from the backtrace) allows
you to go to the function in that frame and see what line in that
particular function caused the error.

If ``backtrace`` and ``frame n`` don't reveal any useful information,
you may want to set breakpoints close to the point where the segfault happens,
to see exactly what happens in the lines leading up to the segfault. However,
to do this, you must first use the ``kill`` to stop the current run of the program
(without exiting GDB).
You will then be able to ``run`` the program again, stopping at any additional
breakpoints you specify.

Try running the ``segfault`` program with gdb and using the above
commands to figure out what is causing the segfault. You will find
the answer at the bottom of this homework.

Task 2: Fixing Segfaults in the Micro Editor
--------------------------------------------

(XX points)

TODO: Micro will segfault under certain conditions. Figure out what the issue is.


Task 3: Logic Error Debugging
-----------------------------

(XX points)

Logic errors can happen even when your program compiles and runs, but
may result in incorrect behavior. The commands we went through in the
warmup can help you find logic errors by allowing actions such as
stepping through the program line-by-line, printing variables, and
seeing when variables are changed.

TODO: Finding a logic error in Micro editor

Submitting your lab
-------------------

Please note that you will not be submitting your code through
Gradescope. Instead, make sure that the questions posed in each task are
answered on Gradescope. That said, we still need you to push your code
in case we need to look at any of your code (but we will not be grading
the code itself).


Answers to Practice Questions
-----------------------------

**Finding the lines where variable c changes**

::

    (gdb) break main
    Breakpoint 3 at 0x5555555551c0: file gdb-warmup.c, line 30.
    (gdb) run
    Starting program: gdb-warmup

    Breakpoint 3, main () at gdb-warmup.c:30
    30	int main() {
    (gdb) watch c
    Hardware watchpoint 4: c
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = -8528
    New value = 12
    main () at gdb-warmup.c:35
    35	    *p += 5;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 12
    New value = 8
    main () at gdb-warmup.c:38
    38	    a += 20;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 8
    New value = 7
    main () at gdb-warmup.c:46
    46	    int b = c - 1;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 7
    New value = 42
    main () at gdb-warmup.c:50
    50	    b *= 8;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 42
    New value = 40
    main () at gdb-warmup.c:54
    54	    b++;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 40
    New value = 50
    main () at gdb-warmup.c:56
    56	    c -= 8;
    (gdb) continue
    Continuing.

    Hardware watchpoint 4: c

    Old value = 50
    New value = 42
    main () at gdb-warmup.c:58
    58	    return 0;
    (gdb) continue
    Continuing.

**Finding the value pointed by p after line 42**

::

    (gdb) break gdb-warmup.c:42
    Breakpoint 5 at 0x55555555521a: file gdb-warmup.c, line 42.
    (gdb) run
    Starting program: gdb-warmup

    Breakpoint 5, main () at gdb-warmup.c:42
    42	    *p -= 1;
    (gdb) print *p
    $1 = 43
    (gdb) next
    44	    c--;
    (gdb) print *p
    $2 = 42


**Stepping through lines 38-41**

::

    (gdb) break gdb-warmup.c:38
    Breakpoint 6 at 0x5555555551fe: file gdb-warmup.c, line 38.
    (gdb) run
    Starting program: gdb-warmup

    Breakpoint 6, main () at gdb-warmup.c:38
    38	    a += 20;
    (gdb) print a
    $3 = 5
    (gdb) next
    39	    *p += 3;
    (gdb)
    40	    a *= 2;
    (gdb)
    41	    a = a - c;
    (gdb)
    42	    *p -= 1;
    (gdb) print a
    $4 = 42


**Return value of num()**

::

    (gdb) break gdb-warmup.c:27
    Breakpoint 8 at 0x5555555551bb: file gdb-warmup.c, line 27.
    (gdb) run
    Starting program: gdb-warmup

    Breakpoint 8, num () at gdb-warmup.c:27
    27	    return num;
    (gdb) print/x num
    $5 = 0xa

**Debugging a segfault**

::

    (gdb) run
    Starting program: segfault

    Program received signal SIGSEGV, Segmentation fault.
    0x00005555555551e4 in foo (n=1) at segfault.c:16
    16	        strcpy(p, "faa");
    (gdb) backtrace
    #0  0x00005555555551e4 in foo (n=1) at segfault.c:16
    #1  0x00005555555552e8 in main () at segfault.c:63
    (gdb) print p
    $1 = 0x0

It looks like ``p`` was not initialized! (it is a null pointer) To fix this, we would need to ``malloc`` memory for ``p``.