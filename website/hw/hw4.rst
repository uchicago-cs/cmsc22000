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
for the homework.

Please note that, while you will be modifying some of the files we give
you, in this homework we will mostly be looking at the answers you provide to
a number of questions on Gradescope. Nonetheless, you should still push
your changes to your repository, in case we need to look at your code.



Task 1: Compiler/Linker Error Debugging
---------------------------------------

(30 points)

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

    While the homework instructions are written for the terminal-based gdb, we
    encourage you to learn about a graphical debugger on your own after
    you’ve completed this homework. Take into account that these graphical
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
to print in binary use ``print/t val``

There is also a useful command to keep track of when a variable changes.
This command is ``watch`` (careful: you can't use this command before
you start running the program in GDB; otherwise, GDB won't know what
variables are currently in scope). If you want to keep track of when the
variable ``x`` changes, type ``watch x``. Every time it is changed when
you run your program or execute a line of code, the program will stop
and print the old and new values (note that it will break in the line
*after* the variable was changed).

When you’re done using gdb, you can exit by typing ``quit`` or by
pressing Ctrl+D. If the program you're debugging is still running,
you will see the following message::

    A debugging session is active.

        Inferior 1 [process 642037] will be killed.

    Quit anyway? (y or n)

You can safely select ``y`` here.

If you'd like to practice using these commands a bit more, try doing
the following (you don't have to answer these questions
on Gradescope; they are just for you to practice):

- **Practice Question A**: Set a breakpoint at the start of the ``main`` function.
  Can you find the line(s) where the value of variable ``c`` changes?
- **Practice Question B**: What is the value pointed to by pointer p after line 42?
- **Practice Question C**: Set a breakpoint at line 38. Print the value of variable ``a`` and step through lines 38-41,
  then print the value of variable ``a`` after line 41.
- **Practice Question D**: What is the return value of the function ``num()`` in hexadecimal?

You can find the answers to these questions at the end of this homework.

The Micro Editor
----------------

We've seen how GDB works with some simple examples, but now it's time to debug
a more complex piece of software. We will be using a very simple terminal-based
editor called ``micro``. This is our version of the ``kilo`` editor, a simple
but functional text editor that can be implemented in about 1,000 lines of C
code; if you're interested, you can see a step-by-step guide to writing this
editor here: https://viewsourcecode.org/snaptoken/kilo/ (please note that you
do not have to read this to complete this homework; however, if you're interested
in the inner workings of a text editor, you may find that guide interesting)

``micro`` largely follows the same structure as the ``kilo`` code, except we
divided it into multiple modules and documented the code following our style guide.

You can build the ``micro`` editor by going into the ``micro/`` directory in
your repository and running the following::

    cmake -B build/
    make -C build/

This will generate a ``micro`` executable inside a ``build/`` directory.
Let's give it a try! Run the following from the ``micro/`` directory::

    build/micro

This will open the editor with a "blank file". You can start typing to edit
the file, and you'll notice that you can move around with the arrow keys, use
the Backspace key, and the Delete key. You should be able to quit the editor
by pressing Ctrl-Q (if you modified the file, you'll have to press it three
times to confirm you want to exit without saving).

However, we have inserted a few bugs in the code, so don't be surprised if
you do something that makes the editor crash! Please note that, if this
happens, your terminal may be left in a seemingly unusable state (in particular,
it will seem like you can't type anything into the terminal). When this happens,
press Enter followed by typing the word ``reset`` followed by pressing Enter (this doesn't
reset your computer, it just resets your terminal). You can also just close the
terminal and open it up again.

Let's say we wanted to debug this executable. We actually cannot call GDB like
before, because the text editor needs to use the entire terminal, so it
would be impractical to have a GDB prompt interfering with that. So, this will
allow us to do *remote debugging*, where the program and the debugger are
run separately (and could even be running in completely different computers,
and communicating over the network).

To do this, open two terminals (if you're logging to a CS Linux server, make
sure you're logged into the same Linux server on both terminals). On the first one, run the following from the
``micro/`` directory::

    gdbserver :50000 build/micro

The editor won't actually start just yet (this is normal!) and you'll see something
like this::

    Process build/micro created; pid = 549651
    Listening on port 50000

.. note::

   If you see the following message::

        Can't bind address: Address already in use.
        Exiting

   Then pick a number other than 50000 in the parameter to ``gdbserver``
   (any number between 50000 and 60000 should work). This number is known
   as a "port", and we will be using it to connect to the editor from GDB.
   We have to pick a number that is unique within the machine we are running
   on; this means that if you are running this on one of the CS Linux server,
   and multiple people choose 50000, only one of them will actually be able
   to run the debugger.

Now, on the second terminal, run this::

    gdb build/micro

This will open the usual GDB prompt but, instead of typing "run", we need to
connect to the editor that is running on the other terminal. You need
to run the following command from the GDB prompt::

    target remote :50000

You will see something like this::

    (gdb) target remote :50000
    Remote debugging using :50000
    Reading /lib64/ld-linux-x86-64.so.2 from remote target...
    warning: File transfers from remote targets can be slow. Use "set sysroot" to access files locally instead.
    Reading /lib64/ld-linux-x86-64.so.2 from remote target...
    Reading symbols from target:/lib64/ld-linux-x86-64.so.2...
    Reading /lib64/ld-2.31.so from remote target...
    Reading /lib64/.debug/ld-2.31.so from remote target...
    Reading /usr/lib/debug//lib64/ld-2.31.so from remote target...
    Reading /usr/lib/debug/lib64//ld-2.31.so from remote target...
    Reading target:/usr/lib/debug/lib64//ld-2.31.so from remote target...
    (No debugging symbols found in target:/lib64/ld-linux-x86-64.so.2)
    0x00007ffff7fd0100 in ?? () from target:/lib64/ld-linux-x86-64.so.2

You can ignore the warning about file transfers being slow, or the message about
"No debugging symbols" (this refers to a system library, not to our editor)

You can now run any of the commands we've seen previously, with one caveat: once
you want to start running the editor, you must use the ``continue`` command,
and not the ``run`` command. In fact, try just running the ``continue`` command;
GDB will show something like this::

    (gdb) continue
    Continuing.
    Reading /lib/x86_64-linux-gnu/libc.so.6 from remote target...
    Reading /lib/x86_64-linux-gnu/libc-2.31.so from remote target...
    Reading /lib/x86_64-linux-gnu/.debug/libc-2.31.so from remote target...
    Reading /usr/lib/debug//lib/x86_64-linux-gnu/libc-2.31.so from remote target...
    Reading /usr/lib/debug//lib/x86_64-linux-gnu/libc-2.31.so from remote target...

And, on the first terminal, the editor will start running.

If you need to quit the editor, we suggest doing so from the first terminal
(by pressing Ctrl-Q). If you start the editor again on the first terminal,
you can actually "reattach" the debugger by running ``target remote :50000``
again from inside GDB. You don't have to also quit GDB and start it again.

You can also force the editor to terminate the
program by pressing Ctrl-C in GDB, followed by Ctrl-D. Please note that this
may leave the first terminal in an unstable state (in the same way as described
above in the case of the editor crashing). If that happens, simply perform
the steps described earlier.


Task 2: Stepping Through the Micro Editor Code
----------------------------------------------

(20 + 20 points)

As you can see in the ``micro/src/main.c`` file, the ``main()`` function of our
editor is actually pretty simple and brief (in large part, thanks to the
modular design of the code which hides the various complexities of
running an editor). The ``main()`` function basically does the following:

- Enable "raw mode" on the terminal, which will allow the editor to effectively
  take over the terminal and "draw" characters anywhere on it (when the terminal
  is running in normal mode, we typically can only print to the terminal line
  by line)
- We initialize an ``editor_ctx_t`` struct, which we use as a context object
  to store global information about the editor.
- If a file was specified in the command-line when running the ``micro`` executable,
  we load that file.
- We set a status message at the bottom of the screen.
- We enter an "event loop", where we continously repeat the following two operations:

  - We refresh the screen with the most up-to-date content of the editor.
  - We wait for a keypress (our "event")

  Event loops are a common way of structuring interactive applications, where we just
  wait for something to happen (in this case, input from the user), and then refresh the
  contents of the screen based on that event. For example, if the user presses the ``F``
  key, we would expect an ``F`` to be inserted at the position of the cursor in the editor.

When debugging our code, we may want to see how some of the fields of our context object
evolve as we use the editor. You must do the following:

1. Open file ``samples/simple.txt`` in the editor. Remember to do this using two terminals;
   in one terminal run this::

       gdbserver :50000 build/micro samples/simple.txt

   In the other terminal, run this::

       gdb build/micro

   Notice how, when opening a file, we only need to specify the file in the first terminal,
   when calling ``gdbserver``.

   You may also want to open a third terminal in case you need to inspect or edit any files
   from a conventional editor.

   On to our task: we would like to figure out the
   exact line(s) in our code where the ``ctx->num_rows``
   variable is updated when we load a file. On Gradescope, specify the line(s) of code
   where this happens, and copy-paste the full and unabridged GDB session that helped
   you determine this.

2. Open file ``samples/lorem-ipsum.txt`` in the editor. We can press Ctrl-F to search
   for a piece of text within the file. Internally, the ``editor_find`` function
   will be called when this happens. Set one or more breakpoints that allow you to determine the
   values of ``ctx->cx`` and ``ctx->cy`` after searching for the term ``Integer``.
   Please note that using ``watch`` in this task is impractical, since those values
   actually can change a lot during a search, and all we're interested in is their
   final value.

   So, in this particular task, it can be beneficial to read through the ``editor_find`` to
   get a sense of where you should set the breakpoint, and at what point you'll be able to
   obtain the final values of ``ctx->cx`` and ``ctx->cy``. On
   Gradescope, specify those values and copy-paste the full and unabridged GDB session
   that helped you determine this.

.. note::

   This homework is also, indirectly, an exercise in diving into an existing codebase.
   While we encourage you to read through the editor code to figure out what it does
   (this is a very valuable skill!) you're also welcome to ask us any questions you want
   about the editor code itself.

Runtime Error Debugging
-----------------------

Runtime errors make the program crash while it is running, and sometimes
they are hard to find because the compiler doesn’t always give
particularly informative error messages.

For example, your repository includes an ``examples/sefault.c`` that will
crash with a segmentation fault when run::

    $ gcc -g segfault.c -o segfault
    $ ./segfault
    Segmentation fault (core dumped)

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

**Practice Question E**: Try running the ``segfault`` program with gdb and using the above
commands to figure out what is causing the segfault. You will find
the answer at the bottom of this homework.

Task 3: Fixing Runtime Errors in the Micro Editor
-------------------------------------------------

We have inserted two bugs in the Micro code that will cause the editor to
crash, and which would be challenging to spot
just by code inspection, given the amount of code you'd have to read through.
This is where a debugger can make your life much easier!

Bug #1
~~~~~~

(20 points)

The editor will crash if you try to save any file by pressing Ctrl-S.
That said, if you have trouble reproducing this issue, you can try
opening the provided ``micro/samples/lorem-ipsum.txt`` file. If you immediately
try to save it, the editor should segfault (you don't even have to make
any modifications to the file).

.. note::

   When the editor crashes, it may leave the terminal in an unstable state.
   Remember that you can resolve this by pressing Enter followed by typing
   the word ``reset`` followed by pressing Enter. You can also close and re-open
   the terminal.

Use GDB to track down the source of the segfault, and to fix it. Provide
the following information on Gradescope:

- Copy-paste the line that is causing the segfault.
- Explain why the segfault is happening.
- The before and after version of any lines of code you changed to
  fix the bug. Remember: the line that causes the segfault may not
  be the line you have to edit to fix the bug.



Bug #2
~~~~~~

(10 points)

If you place the cursor at the start of a line (other than the first line
of the file) and press the "Backspace" key, this will move the contents
of that line to the end of the previous line. For example, open the file
``micro/samples/lines-1.txt``, which contains the following::

    AAAAAAAAAA
    BBBBBBBBBB

If you place the cursor at the start of the second line and press "Backspace",
the editor will now display this::

    AAAAAAAAAABBBBBBBBBB

So far, so good. However, try doing the same thing with the file
``micro/samples/lines-2.txt``, where the second line is much longer than the first.
The editor will now crash with an error like this::

    munmap_chunk(): invalid pointer
    Aborted (core dumped)

This is not a segfault, but we can debug it with GDB following the same steps
we followed to debug a segfault (this error is alerting
us to the fact that a system library received an invalid pointer, which may help us
narrow down the issue).

That said, this bug is much more insidious than the previous one: the line that
causes the editor to crash is actually a *spurious error*. There is actually nothing
wrong with that line or even with the variable that is being manipulated in that line.
However, something in the lines of code leading up to that line has corrupted the
editor's data structures, causing that variable to contain an
invalid pointer. So, to debug this issue, you should look at what happens before
the line that causes the crash (including prior functions in the backtrace) to
see if you can spot anything wrong.

For this task, you must provide the following information on Gradescope:

- Copy-paste the line that is causing the crash.
- Identify the programming error that leads to that crash happening.
- The before and after version of any lines of code you changed to
  fix the bug.

**NOTE:** This is a particularly challenging bug. We will give partial credit
if you describe how you attempted to track down the bug but, for full credit,
you must actually fix the bug.

Submitting your homework
------------------------

Please note that you will not be submitting your code through
Gradescope. Instead, make sure that the questions posed in each task are
answered on Gradescope. That said, we still need you to push your code
in case we need to look at any of your code (but we will not be grading
the code itself).


Answers to Practice Questions
-----------------------------

**Practice Question A**

Variable ``c`` changes at lines 34, 36, 44, 47, 53, 55, 56.

Notice how GDB will break in the line *after* the variable changes:

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

**Practice Question B**

The value is ``42``.

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


**Practice Question C**

The value of ``a`` at line 38 is ``5``. After line 41, it is ``42``.

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


**Practice Question D**

The return value is ``0xa``

::

    (gdb) break gdb-warmup.c:27
    Breakpoint 8 at 0x5555555551bb: file gdb-warmup.c, line 27.
    (gdb) run
    Starting program: gdb-warmup

    Breakpoint 8, num () at gdb-warmup.c:27
    27	    return num;
    (gdb) print/x num
    $5 = 0xa

**Practice Question D**

The segfault happens in line 16:

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