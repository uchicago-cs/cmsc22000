Homework 3: Make
================

**Due:** Wednesday, April 20st, 8pm CDT

In the class project, you will likely produce dozens of C files that
will ultimately produce a single executable. When dealing with multiple
source files, specially when there are dependencies between them, it is
common to use a *build system* instead of manually compiling and linking
all the files. in this homework, we’ll explore the ways a program can be
“built”–that is, the way that source code is turned into binary code so
that a computer can execute it. In some cases, “building” may refer to
compiling a single file, but usually it refers to the whole process of
linking and creating a project: which can include linking, compiling,
and running tests. We’ll look at testing in later homeworks, and for this homework
we’ll focus on the ``make`` command as a way to compile and build
projects.

Similar to Homework #1, this homework involves following some tutorial-style
instructions to familiarize yourself with ``make``, and will also include
some exercises where you can apply what you've learned about ``make``.

Project Team Exercise: Design Warm-up (Part II)
-----------------------------------------------

Along with this week’s homework, we are also assigning the second part of the
design warm-up exercise, which you can find `here <../project/design.html>`__.
Please note that the second part of the design exercise is due at the same time as this homework.

Creating your homework repository
---------------------------------

Like previous homeworks, we will provide you with an *invitation URL* that
will allow you sign up for the homework assignment on GitHub, and which will
result in the creation of a repository called
``hw3-GITHUB_USERNAME`` inside our ``uchicago-cmsc22000-2022`` organization
on GitHub. Like Homework #2, your repository will be seeded with some files
for the homework.

Writing Makefiles
-----------------

Before we get to the actual tasks in this homework, you will work through
a tutorial-style explanation of Makefiles. This will involve editing
a Makefile in your repository; make sure to commit your changes as
you complete them, as we will be checking whether you followed the steps
described in this tutorial (it is ok if you don't commit every single
change as you make it, but it should be apparent from your commit log
that you worked through these steps).

Compiling a program with multiple C files
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In the ``polygon-area`` directory, you will see the following files:

- Point module: ``point.c`` and ``point.h``
- Polygon module: ``polygon.c`` and ``polygon.h``
- Auxiliary files: ``common.h`` and ``utils.h``
- Polygon Area program: ``polygon-area.c``

Before proceeding, make sure you're inside the ``polygon-area/``
directory:

.. code-block:: shell

    $ cd polygon-area

All the files, except ``polygon-area.c``, are taken directly from
the ``libgeometry`` example from Homework #2. Later in this homework
we will explain why ``libgeometry`` has a more elaborate directory
structure but, for the purposes of this homework, it'll be simpler
to start with all the files in the same directory.

The ``polygon-area.c`` file contains a ``main()`` function that relies
on the point and polygon modules to compute the area of a polygon
(after asking the user to provide the points in the polygon).

Notice how we can't compile the ``polygon-area.c`` file by itself:

.. code-block:: shell

    $ gcc polygon-area.c -o polygon-area
    /usr/bin/ld: /tmp/ccmgP8wg.o: in function `main':
    polygon-area.c:(.text+0x21): undefined reference to `polygon_new'
    /usr/bin/ld: polygon-area.c:(.text+0x95): undefined reference to `polygon_add_xy'
    /usr/bin/ld: polygon-area.c:(.text+0x10c): undefined reference to `polygon_area'
    collect2: error: ld returned 1 exit status

This results in a bunch of *linker errors* (not compiler errors). There is nothing wrong
with ``polygon-area.c`` itself, but it depends on functions like ``polygon_area``,
which are defined in a different C file (``polygon.c``). We need to compile that
file, as well as ``point.c`` (which the polygon module depends on), to be able
to produce the ``polygon-area`` executable.

The simplest way to accomplish this is to simply pass all those files to the compiler:

.. code-block:: shell

   $ gcc point.c polygon.c polygon-area.c -o polygon-area -lm

Remember that, internally, this is divided into two separate steps:

- Compiling: The compiler will compile each C file into an object file.
- Linking: The compiler will link together all those files together into a single executable
  (``polygon-area``). Here, we also link to the math library, since
  the point module relies a couple of functions from that library (if you try re-running
  the above command without the ``-lm`` option, you will see linker errors that refer
  to math functions).

Because we're making a single call to the compiler, it doesn't actually save the
object files anywhere, but that step is still happening internally.

At this point, you can try running the program. For example::

    $ ./polygon-area
    Please enter a value for x: 0
    Please enter a value for y: 0
    Would you like to enter another point? (y/n) y
    Please enter a value for x: 0
    Please enter a value for y: 2
    Would you like to enter another point? (y/n) y
    Please enter a value for x: 2
    Please enter a value for y: 2
    Would you like to enter another point? (y/n) y
    Please enter a value for x: 2
    Please enter a value for y: 0
    Would you like to enter another point? (y/n) n
    The area is 4.00

Writing a basic ``Makefile``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

At this point, compiling our program involves running the following:

.. code-block:: shell

   $ gcc point.c polygon.c polygon-area.c -o polygon-area -lm

This involves writing a relatively long command (which will only get longer
if we need to add more C files) that always involves re-compiling
every C file from scratch (and then linking them together).
Instead, we can use ``make`` to not just automate the building
of the program, but also optimize it (by avoiding un-necessary
compilation steps).

To use ``make``, we will need to create a file called ``Makefile``
that specifies what we want to build. A ``Makefile`` is just a
regular text file, so you are welcome to use your editor of choice
to create and edit Makefiles.

Let's start by creating this very simple ``Makefile``:

.. code-block:: makefile

   polygon-area:
    	gcc point.c polygon.c polygon-area.c -o polygon-area -lm

The above code specifies a single **make rule**, that basically
says "To produce the file ``polygon-area`` run the command ``gcc point.c polygon.c ...``".

Before trying out our ``Makefile``, we're going to remove the
``polygon-area`` executable we previously compiled manually:

.. code-block:: shell

    $ rm polygon-area

You can now run the ``Makefile`` by running the following:

.. code-block:: shell

    $ make polygon-area

By calling ``make`` like this, we are telling ``make`` "I need you to produce file ``polygon-area``"
``make`` will check the list of rules (by default, it will always look at the ``Makefile`` in the
same directory you are running ``make``) and, if it finds a matching rule, it will run it.
In this case, it will run the ``gcc`` command we specified in the ``polygon-area`` rule:

.. code-block:: shell

    $ make polygon-area
    gcc point.c polygon.c polygon-area.c -o polygon-area -lm

If we run this again, we'll get a different output:

.. code-block:: shell

    $ make polygon-area
    make: 'polygon-area' is up to date.

This is because ``make`` will skip producing the ``polygon-area`` file
if it already exists (later on, we'll see how we can affect this behaviour,
since there will be situations where we *do* want ``polygon-area`` to be
compiled again, e.g., if we make a change to ``point.c``).

You may notice that you can also just run ``make`` without any parameters
(notice how we first remove ``polygon-area``, so we don't get the "up to date"
message):

.. code-block:: shell

    $ rm polygon-area
    $ make
    gcc point.c polygon.c polygon-area.c -o polygon-area -lm

There is a reason why this works as well, and we'll explain it later on but,
for now, we'll stick to explicitly specifying our *build target* when calling
``make``.

.. warning::

    **Beware the curse of the tabs and the missing separators!**

    If you get an error message like this:

    ::

       Makefile:2: *** missing separator.  Stop.

    This means there may have been an issue when copy-pasting from this page
    to the ``Makefile``. More specifically, Makefiles use `tab
    characters <https://en.wikipedia.org/wiki/Tab_key>`__ to indent the
    commands in a rule. This makes it challenging to edit Makefiles if you
    have set up your editor to use spaces to indent your code. If you’re
    getting the “missing separator error”, it’s likely that your editor
    automatically converted the tab characters to spaces.

    If that is the case, you can tell ``make`` to use spaces instead of tabs
    by adding the following at the top of your Makefile:

    ::

       .RECIPEPREFIX +=

Make rules
~~~~~~~~~~

We've seen earlier that, assuming the ``polygon-area`` file
doesn't exist, running ``make`` will run the ``gcc`` command
to compile it, and subsequent calls to ``make`` will just tell
us that the file is "up to date":

.. code-block:: shell

    $ make polygon-area
    gcc point.c polygon.c polygon-area.c -o polygon-area -lm
    $ make polygon-area
    make: 'polygon-area' is up to date.
    $ make polygon-area
    make: 'polygon-area' is up to date.

So, ``make`` is definitely saving us from having to remember the full
command we want to type, and will also ensure we're not needlessly
re-compiling the file if it already exists.

However, what if we make a change to one of the C files? In that
situation, we *do* want ``polygon-area`` to be recompiled.
``make`` can also help us here: we can tell ``make`` what files ``polygon-area``
depends on, so it will re-build ``polygon-area`` if any of
those files change.

We can do this by adding a list of dependencies or *prerequisites*
after the colon in the rule:

.. code-block:: makefile

   polygon-area: point.c polygon.c polygon-area.c
    	gcc point.c polygon.c polygon-area.c -o polygon-area -lm

Now, let's run ``make`` again:

.. code-block:: shell

    $ make polygon-area
    make: 'polygon-area' is up to date.

Given that we haven't made any changes to ``point.c``, ``polygon.c``,
or ``polygon-area.c`` since the last time we produced the
``polygon-area`` executable, ``make`` can tell that there is
no need to re-build ``polygon-area``.

Now, try editing ``polygon-area.c`` (any trivial edit is enough,
e.g., add a newline at the bottom of the file). If we run
``make`` again, it will detect that one of the prerequisite
files has changed, and it will re-build ``polygon-area``:

.. code-block:: shell

   $ make polygon-area
   gcc point.c polygon.c polygon-area.c -o polygon-area -lm

In general, Make rules have the following structure:

.. code-block:: makefile

   rule-name: prerequisite
       command

Rules can have any number of (or zero) prerequisites
(separated by spaces), and any number of (or zero) commands (separated
by newlines). It’s important to note that while ``make`` is probably
most often used with C programs, ``make`` is a generic tool supporting
arbitrary commands.

.. note::

    Building produces a number of binary files,
    including object files, executables, and (as we’ll see later in this
    homework) library files. These should *never* be added to your Git
    repository! You’ll notice that there’s actually a ``.gitignore`` file in
    the root of your repository with a list of files that Git should ignore
    (so you won’t inadvertently add them to your repository). It is good
    practice to have such a file in any repository you create, to make sure
    you never add binary files to your repository.


Separating the compilation and linking steps
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

There is still an issue with our Makefile: any time any of the
pre-requisite files change, all the files are re-compiled from
scratch. So, in the example above, we only changed ``polygon-area.c``,
but that resulted in running this command::

   gcc point.c polygon.c polygon-area.c -o polygon-area -lm

Which tells ``gcc`` to compile all three files.

Ideally, if we only modified ``polygon-area.c``, we would like to only
re-compile that file. However, to do this, we have to separately
produce the object files for each of the C files. From the command-line,
we would do so like this:

.. code-block:: shell

    $ gcc point.c -c -o point.o
    $ gcc polygon.c -c -o polygon.o
    $ gcc polygon-area.c -c -o polygon-area.o

Notice how we use the ``-c`` parameter to the compiler: this tells
the compiler to only compile the specified file, and to not attempt
to link it. This produces an *object* file with the compiled version
of the code in that C file (and that C file alone).

To link those object files together, we call the compiler like this:

.. code-block:: shell

    $ gcc point.o polygon.o polygon-area.o -o polygon-area -lm

Notice how we're not passing any C files to the compiler: by passing
only object files, ``gcc`` knows that no further compilation is required,
and that all it has to do is to link them together (and with the math
library, specified with the ``-lm`` parameter).

.. admonition:: What happens if we omit the ``-c`` option?

   Let's see what happens if we omit the ``-c`` option when
   compiling the object files:

   .. code-block:: shell

      $ gcc polygon.c -o polygon.o
      /usr/bin/ld: /usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu/Scrt1.o: in function `_start':
      (.text+0x24): undefined reference to `main'
      /usr/bin/ld: /tmp/cc5mU0L8.o: in function `polygon_add_xy':
      polygon.c:(.text+0x212): undefined reference to `point_init'
      /usr/bin/ld: /tmp/cc5mU0L8.o: in function `polygon_add_point':
      polygon.c:(.text+0x3e5): undefined reference to `segment_intersect'
      /usr/bin/ld: /tmp/cc5mU0L8.o: in function `polygon_perimeter':
      polygon.c:(.text+0x64f): undefined reference to `point_distance'
      collect2: error: ld returned 1 exit status

   If we run the compiler like this, it will perform both a compilation and linking
   step. This means that, since ``polygon.c`` includes calls to function like
   ``point_init`` and ``segment_intersect``, it will attempt to link those calls
   to their implementation (but that implementation is nowhere to be found in ``polygon.c``).
   If we only perform the compilation step (by using the ``-c`` option) those calls
   are left unlinked in the object file, so they don't cause any errors.

   Notice how we also get this error::

       (.text+0x24): undefined reference to `main'

   This is because, by default, the compiler will try to produce an executable file,
   which means it will look for a ``main()`` function that specifies what that
   executable will do (and will produce a linker error if no such function is found)

Now that we've separated the compiling and linking steps, we can avoid
re-compiling all the C files every time. For example, if we modify only
the ``point.c`` file, producing an updated ``polygon-area`` executable
would just require running the following:

.. code-block:: shell

    $ gcc point.c -c -o point.o
    $ gcc point.o polygon.o polygon-area.o -o polygon-area -lm

To automate this with ``make``, we need to specify separate
rules for the object files. For example, this is what the rule
for producing the ``point.o`` object file would look like.

.. code-block:: makefile

    point.o: point.c
        gcc point.c -c -o point.o

Remember that this is basically saying "To produce file ``point.o``, run
``gcc point.c ...``, but only if ``point.c`` has changed since the last
time we built ``point.o``".

Our full ``Makefile`` would now look like this:

.. code-block:: makefile

    point.o: point.c
        gcc point.c -c -o point.o

    polygon.o: polygon.c
        gcc polygon.c -c -o polygon.o

    polygon-area.o: polygon-area.c
        gcc polygon-area.c -c -o polygon-area.o

    polygon-area: point.o polygon.o polygon-area.o
        gcc point.o polygon.o polygon-area.o -o polygon-area -lm

Notice how the ``polygon-area`` rule now depends on the object files,
not on the C files.

Let's give this a try, but lets first make sure that we're starting
from scratch. Run the following to delete any files we may have built:

.. code-block:: shell

   $ rm -f point.o polygon.o polygon-area.o polygon-area

Now, let's run ``make``:

.. code-block:: shell

    $ make polygon-area
    gcc point.c -c -o point.o
    gcc polygon.c -c -o polygon.o
    gcc polygon-area.c -c -o polygon-area.o
    gcc point.o polygon.o polygon-area.o -o polygon-area -lm

Notice how ``make`` was able to sort out all the dependencies, and figure out
that, to produce ``polygon-area``, it first needed to produce the object files
listed in its prerequisites.

If we try to run ``make`` again, it will correctly realize that nothing has
changed, and that we don't need to re-build anything:

.. code-block:: shell

    $ make polygon-area
    make: 'polygon-area' is up to date.

Now, let's see what happens if we edit one of the files except, instead of
editing the file, we will use the ``touch`` command:

.. code-block:: shell

    $ touch polygon.c

The ``touch`` command is a handy command that will simply update the
"last modified" date on a file, without actually changing its contents.
(that timestamp is actually what ``make`` is looking at when determining
whether a file has changed since the last time it was compiled).

If we run ``make`` again, we'll see that it correctly figures out that
it only needs to re-build the ``polygon.o`` file, and then re-link it
with the existing object files:

.. code-block:: shell

    $ make polygon-area
    gcc polygon.c -c -o polygon.o
    gcc point.o polygon.o polygon-area.o -o polygon-area -lm


Phony rules
~~~~~~~~~~~

So far, we've defined a couple of rules whose goal is to
produce specific files (either the object files or the ``polygon-area``
executable). However, it is also possible to write so-called
*phony* rules that don't produce any files, and which instead just perform
some action.

For example, we've previously run the following command
to delete all the generated files:

.. code-block:: shell

    $ rm -f point.o polygon.o polygon-area.o polygon-area

We can create a ``clean`` rule that performs this action:

.. code-block:: makefile

    clean:
    	rm -f point.o polygon.o polygon-area.o polygon-area

And which we can run like this:

.. code-block:: shell

    $ make clean
    rm -f point.o polygon.o polygon-area.o polygon-area

However, notice how running the ``rm`` command doesn't
produce a file called ``clean`` (like our previous rules did,
where the effect of the rule's command was to generate a file
matching the target of the rule).

So, while the rule will work as-is, we will want to label it
as a "phony" rule, by adding this to our ``Makefile``:

.. code-block:: makefile

    .PHONY: clean

This lets ``make`` know that it should not expect the ``clean``
rule to actually produce a file called ``clean``. This means that,
in the unlikely event that we actually need to create a file called
``clean`` for some other purpose, ``make`` won't take that file
into account when deciding to run the ``clean`` rule.

In general, it is good practice to always include a ``clean`` rule
in your ``Makefile``, specifying how to "clean up" all the files
generated by the compiler.

Before we see another common phony rule, try running ``make`` without
any parameters (make sure you've run ``make clean`` as shown above before
doing this):

.. code-block:: shell

    $ make
    gcc point.c -c -o point.o

This seems wrong: if I run ``make clean`` and then run ``make`` again,
I would expect ``polygon-area`` to be built again, instead of just
the ``point.o`` object file. The reason this is happening is that
*if you run make without any parameters, it will run the first rule
in the file* (which, in our case, happens to be rule for building
the ``point.o`` file).

While we could move the ``polygon-area`` rule to the top of the file,
a more common practice is to create a phony ``all`` rule that specifies
what the ``Makefile`` should build, and which appears before all other
rules.

In our case, this rule would look like this:

.. code-block:: makefile

   all: polygon-area

And let's make sure we add it to the list of phony rules:

.. code-block:: makefile

   .PHONY: clean all

To recap, our full Makefile should now look like this:

.. code-block:: makefile

    all: polygon-area

    .PHONY: clean all

    point.o: point.c
        gcc point.c -c -o point.o

    polygon.o: polygon.c
        gcc polygon.c -c -o polygon.o

    polygon-area.o: polygon-area.c
        gcc polygon-area.c -c -o polygon-area.o

    polygon-area: point.o polygon.o polygon-area.o
        gcc point.o polygon.o polygon-area.o -o polygon-area -lm

    clean:
        rm -f point.o polygon.o polygon-area.o polygon-area

Let's try running ``make clean`` followed by ``make``:

.. code-block:: shell

    $ make clean
    rm -f point.o polygon.o polygon-area.o polygon-area
    $ make
    gcc point.c -c -o point.o
    gcc polygon.c -c -o polygon.o
    gcc polygon-area.c -c -o polygon-area.o
    gcc point.o polygon.o polygon-area.o -o polygon-area -lm

Now, when we call ``make`` (without any parameters), Make will try to build
the first rule in the file. That rule is the ``all`` rule, which has one
prerequisite, ``polygon-area``, so it will perform the steps needed to
build that file.

Variables
~~~~~~~~~

Besides defining rules, Make also allows us to define variables,
which can help keep our Makefile tidy. Two variables you'll
often see in Makefiles are ``CC``, to specify the compiler
we want to use, and ``CFLAGS``, to specify the parameters
we want to pass to the compiler.

For example, let's add this at the top of our ``Makefile``:

.. code-block:: makefile

    CC = clang
    CFLAGS = -g -O2 -Wall -Wextra

To use a variable, we just write it's name between ``$(`` and ``)``.
For example, our previous rule for the ``point.o`` file:

.. code-block:: makefile

    point.o: point.c
        gcc point.c -c -o point.o

Will now look like this:

.. code-block:: makefile

    point.o: point.c
        $(CC) $(CFLAGS) point.c -c -o point.o

Notice how this is not a direct translation of the previous rule:
we've generalized it so that we can use whatever compiler is
specified the ``CC`` variable (which is different from the
one we were previously using), and are now able to easily
specify additional compiler options in the ``CFLAGS`` variable
(we didn't include these options in our previous rules to keep
them simple). The options we've included are common options that
enable debugging symbols (``-g``, we'll learn more about this
in the next homework), enable optimizations (``-O2``), and tells
the compiler to enable more warning messages (``-Wall -Wextra``).

Next, when writing a Makefile that compiles multiple object files
and then links them together, it is common to have an ``OBJS`` variable
to specify the list of object files, and a ``BIN`` variable to
specify the executable we are generating (an executable is sometimes
referred to as a "binary"). It is also common to define a
``LDLIBS`` variable to specify any additional libraries we
are going to link with.

So, let's add this at the top of our Makefile:

.. code-block:: makefile

    LDLIBS = -lm
    OBJS = point.o polygon.o polygon-area.o
    BIN = polygon-area

Then, this rule:

.. code-block:: makefile

    polygon-area: point.o polygon.o polygon-area.o
        gcc point.o polygon.o polygon-area.o -o polygon-area -lm

Would become this:

.. code-block:: makefile

    $(BIN): $(OBJS)
        $(CC) $(OBJS) -o $(BIN) $(LDLIBS)

After updating all the rules, our Makefile would look like this:

.. code-block:: makefile

    CC = clang
    CFLAGS = -g -O2 -Wall -Wextra
    LDLIBS = -lm

    OBJS = point.o polygon.o polygon-area.o
    BIN = polygon-area

    all: $(BIN)

    .PHONY: clean all

    point.o: point.c
        $(CC) $(CFLAGS) point.c -c -o point.o

    polygon.o: polygon.c
        $(CC) $(CFLAGS) polygon.c -c -o polygon.o

    polygon-area.o: polygon-area.c
        $(CC) $(CFLAGS) polygon-area.c -c -o polygon-area.o

    $(BIN): $(OBJS)
        $(CC) $(OBJS) -o $(BIN) $(LDLIBS)

    clean:
        rm -f $(OBJS) $(BIN)

Notice how this makes it much easier for us to update something like the
compiler flags, or the name of the executable we are generating, without
having to muck around with the rules themselves. All that would be required
would be to update the variables at the top of the file.

Before moving on, let's make sure this works as expected:

.. code-block:: shell

    $ make clean
    rm point.o polygon.o polygon-area.o polygon-area
    $ make
    clang -g -O2 -Wall -Wextra point.c -c -o point.o
    clang -g -O2 -Wall -Wextra polygon.c -c -o polygon.o
    clang -g -O2 -Wall -Wextra polygon-area.c -c -o polygon-area.o
    clang point.o polygon.o polygon-area.o -o polygon-area -lm

Notice how ``make`` is now using ``clang`` as the compiler, and is including
the specified compiler parameters when compiling the object files.

Automatic Variables and Patterns
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Our Makefile is looking pretty good, but notice how the following
rules all follow the same pattern: an object file that depends on a
C file, where the command to build the object file is identical
across all the rules (except for the files involved).

.. code-block:: makefile

    point.o: point.c
        $(CC) $(CFLAGS) point.c -c -o point.o

    polygon.o: polygon.c
        $(CC) $(CFLAGS) polygon.c -c -o polygon.o

    polygon-area.o: polygon-area.c
        $(CC) $(CFLAGS) polygon-area.c -c -o polygon-area.o

Fortunately, Make provides a number of mechanism that can allow us
to build more general rules, instead of having to write a single
rule per object file.

First, we have *automatic variables* that allow us to access
information about a rule. The ones we'll need to use are the
following:

-  ``$@`` refers to the target of the rule
-  ``$^`` is the names of all the prerequisites, separated by spaces
-  ``$<`` is the name of the first prerequisite

So, for example, it would be possible to rewrite this rule:

.. code-block:: makefile

    point.o: point.c
        $(CC) $(CFLAGS) point.c -c -o point.o

Like this:

.. code-block:: makefile

    point.o: point.c
        $(CC) $(CFLAGS) $< -c -o $@

This makes the rule a bit less error-prone, as it ensures that we're using the
correct values in the command, but we would still need to write a separate
rule for each object file.

To write a single general rule for all the object files, we will need to use
*patterns*. For example, we could write a pattern rule like this:

.. code-block:: makefile

    %.o: %.c
        $(CC) $(CFLAGS) $< -c -o $@

In this rule, ``%.o`` will match any file ending with ``.o``, and will
set its prerequisite to the same file, but replacing ``.o`` with ``.c``.

While this can be a useful rule, it is a bit too broad for our purposes,
since we have a specific list of object files we want to compile. We can
instead write the rule like this:

.. code-block:: makefile

    $(OBJS): %.o:%.c
        $(CC) $(CFLAGS) $< -c -o $@

This has the same effect as the previous (more general) rule, but
limiting the list of targets only to the files in the ``OBJS`` variable.

It is also possible to peform pattern substitutions on variables.
For example, we could redefine our ``OBJS`` variable like this:

.. code-block:: makefile

    SRCS = point.c polygon.c polygon-area.c
    OBJS = $(SRCS:.c=.o)

We first define a ``SRCS`` variable with our source files,
and then define ``OBJS`` to be ``$(SRCS:.c=.o)``, which just means
"take the ``SRCS`` variable, and substitute the ``.c`` extension for ``.o``
in all files".

To recap, our Makefile should now look like this:

.. code-block:: makefile

    CC = clang
    CFLAGS = -g -O2 -Wall -Wextra
    LDLIBS = -lm

    SRCS = point.c polygon.c polygon-area.c
    OBJS = $(SRCS:.c=.o)
    BIN = polygon-area

    all: $(BIN)

    .PHONY: clean all

    $(OBJS): %.o:%.c
        $(CC) $(CFLAGS) $< -c -o $@

    $(BIN): $(OBJS)
        $(CC) $(OBJS) -o $(BIN) $(LDLIBS)

    clean:
        rm -f $(OBJS) $(BIN)

Let's make sure it works correctly:

.. code-block:: shell

    $ make clean
    rm -f point.o polygon.o polygon-area.o polygon-area
    $ make
    clang -g -O2 -Wall -Wextra -c -o point.o point.c
    clang -g -O2 -Wall -Wextra -c -o polygon.o polygon.c
    clang -g -O2 -Wall -Wextra -c -o polygon-area.o polygon-area.c
    clang point.o polygon.o polygon-area.o -o polygon-area -lm

Task 1: Makefile for the micro editor
-------------------------------------

We have included a ``micro-editor`` directory in your repository with
the code for a very simple terminal-based editor
called ``micro``. This is our version of the ``kilo`` editor, a simple
but functional text editor that can be implemented in about 1,000 lines of C
code; if you're interested, you can see a step-by-step guide to writing this
editor here: https://viewsourcecode.org/snaptoken/kilo/ (please note that you
do not have to read this to complete this homework; however, if you're interested
in the inner workings of a text editor, you may find that guide interesting).

``micro`` largely follows the same structure as the ``kilo`` code, except we
divided it into multiple modules and documented the code following our style guide.

You can compile and run the editor like this:

.. code-block:: shell

    $ gcc src/*.c -o micro
    $ ./micro

This will open the editor with a "blank file". You can start typing to edit
the file, and you'll notice that you can move around with the arrow keys, use
the Backspace key, and the Delete key. You should be able to quit the editor
by pressing Ctrl-Q (if you modified the file, you'll have to press it three
times to confirm you want to exit without saving).

Your task is simple: write a Makefile that will build the ``micro``
executable. Take into account that, while we were able to compile
the executable just by running ``gcc src/*.c -o micro``, your Makefile
should follow the same approach as the Makefile for ``polygon-area``:
you must build each object file separately, and link them together
into a ``micro`` executable. You must also use variables and patterns
to avoid repeated code in your Makefile.

.. admonition:: The ``CMakeLists.txt`` file

    You'll notice there is also a ``CMakeLists.txt`` file in the
    ``micro-editor`` directory. You can ignore that file for now;
    we will come back to it later in the homework.

Building a library
------------------

So far, we've written a Makefile whose ultimate purpose is to build
a ``polygon-area`` executable. However, let's say that we now
wanted to build an additional executable, ``point-distance``, that
relied on the Point module. Go ahead and create a file called
``point-distance.c`` with the following code:

.. code-block:: c

    #include <stdio.h>
    #include "point.h"

    int main()
    {
        point_t p1, p2;

        printf("[Point 1] Please enter a value for x: ");
        scanf("%lf", &p1.x);

        printf("[Point 1] Please enter a value for y: ");
        scanf("%lf", &p1.y);

        printf("[Point 2] Please enter a value for x: ");
        scanf("%lf", &p2.x);

        printf("[Point 2] Please enter a value for y: ");
        scanf("%lf", &p2.y);

        printf("The distance between (%.2lf, %.2lf) and "
               "(%.2lf, %.2lf) is %.2lf\n", p1.x, p1.y, p2.x, p2.y,
               point_distance(&p1, &p2));
    }

We *could* create another Makefile where the ``BIN`` variable is set
to ``point-distance``, or we could even edit our existing Makefile
with an additional rule to build ``point-distance``. However,
this would result in ``polygon-area`` and ``point-distance``
being *statically linked* with the Point and Polygon modules,
meaning that the ``polygon-area`` and ``point-distance`` executables
will contain the compiled binary code for any Point or Polygon functions they
use. If we have a lot of executables like this, that could mean
a lot of repeated binary code across all the executables.

Instead, it would be preferable to build the Point and Polygon modules
into a *shared library* that can be *dynamically linked* with the
``polygon-area`` and ``point-distance`` executables. More specifically,
we will build a ``libgeometry.so`` file containing the binary code
of the Point and Polygon modules.

For example, the compiled binary code for the ``point_distance``
function would be contained in ``libgeometry.so``, and the ``point-distance``
executable would just include a reference to that function
(that would be linked to the actual ``point_distance`` code in ``libgeometry.so``
when the ``point-distance`` executable is run).

To build the library, we would just need to run this:

.. code-block:: shell

    $ gcc -fPIC -c point.c -o point.o
    $ gcc -fPIC -c polygon.c -o polygon.o
    $ gcc -shared -o libgeometry.so point.o polygon.o

Notice how we're compiling the Point and Polygon modules as we did
before, but we are now using the ``-fPIC`` option. This flag tells
gcc to enable *position-independent code*. Position-independence
is beyond the scope of this homework, but it’s necessary for
building shared libraries.

Then, we simply link the ``point.o`` and ``polygon.o`` object files
like we did before except, instead of producing an executable,
we produce the ``libgeometry.so`` file (the ``-shared`` option
instructs the linker to produce a library instead of an executable)

Then, to build the ``point-distance`` executable, we do the following:

.. code-block:: shell

    gcc point-distance.c -o point-distance -L. -lgeometry -lm

Notice how we now include an ``-lgeometry`` option to tell the
linker to link with the ``libgeometry.so`` library (by default,
passing *NAME* to the ``-l`` option will result in the linker
searching for a file called ``libNAME.so``). We additionally
pass the ``-L.`` option to tell the linker to look for
libraries in the current directory.

.. admonition:: What about ``-lm``?

   We've used the ``-lm`` option previously to link
   our executables to the standard math library, but
   we've just said that using an option like ``-lm``
   would result in linking with with a library called
   ``libm.so``. So, where is that file?

   Since the math library is a standard library,
   it is located in a system directory that the
   linker will also be looking at when trying
   to find library files. In most Linux systems,
   this file can be found here::

      /usr/lib/x86_64-linux-gnu/libm.so

If you run the commands above, the result should be
a ``point-distance`` executable. However, there is
one final wrinkle when we try to run it:

.. code-block:: shell

    $ ./point-distance
    ./point-distance: error while loading shared libraries: libgeometry.so: cannot open shared object file: No such file or directory

We also need to tell the *shell* where to look for library
files when running executables. We can do this by setting
the ``LD_LIBRARY_PATH`` environment variable:

.. code-block:: shell

    $ export LD_LIBRARY_PATH=.
    $ ./point-distance
    [Point 1] Please enter a value for x: 0.0
    [Point 1] Please enter a value for y: 1.0
    [Point 2] Please enter a value for x: 1.0
    [Point 2] Please enter a value for y: 0.0
    The distance between (0.00, 1.00) and (1.00, 0.00) is 1.41

Note: Setting the ``LD_LIBRARY_PATH`` environment variable only needs to be done once
each time you start a new terminal. You do not need to run it every time you want
to run the executable.

Our updated Makefile will now look like this:

.. code-block:: makefile

    CC = clang
    CFLAGS = -fPIC -g -O2 -Wall -Wextra
    LDFLAGS = -L.
    LDLIBS = -lgeometry -lm

    SRCS = point.c polygon.c
    OBJS = $(SRCS:.c=.o)
    LIB = libgeometry.so

    BINS = polygon-area point-distance

    all: $(LIB) $(BINS)

    .PHONY: clean all

    $(OBJS): %.o:%.c
        $(CC) $(CFLAGS) $< -c -o $@

    $(LIB): $(OBJS)
        $(CC) -shared -o $@ $^

    $(BINS): %:%.c $(LIB)
        $(CC) $< -o $@ $(LDFLAGS) $(LDLIBS)

    clean:
        rm -f $(OBJS) $(LIB) $(BINS)

At this point, it should be possible for you to understand the
changes we've made to the Makefile. Pay special attention to the
new ``$(LIB)`` target, and the new ``BINS`` variable (which now
specifies multiple executables), as well as how we're using patterns in the
``$(BINS)`` pattern to build those executables.

.. admonition:: The directory structure in Homework #2's libgeometry

    TODO

Task 2: The libgraph library
----------------------------

We have included in your repository a ``libgraph`` directory that contains
the code for a graph library (in the ``src/libgraph`` directory),
as well as a few executables that use that library (in the ``src/tools``
directory). You do not need to understand the graph code itself but,
if you're curious, it provides a series of data structures and functions
to manipulate graphs, as well as a few common graph algorithms.

Your task is to write a Makefile that will build a ``libgraph.so`` library,
along with the ``best-first`` and ``toposort`` executables, which will
use that library. Notice how the directory structure is
different from the ``polygon-area`` example, where all the files
were in a single directory. Instead, the files are organized
similar to the ``libgeometry`` example from Homework #2.

You are not allowed to move any of
the files in the ``libgraph/`` directory, and must instead account
for this directory structure in your Makefile. One particular aspect
you'll have to figure out (which we have not explained) is how to
tell the compiler to look for header files in a different directory
(notice how several of the header files are in a separate ``include/``
directory).

If you are successful, you should be able to run the executables as follows:

.. code-block:: shell

    $ ./best-first -g examples/cities.graph -s SanFrancisco -f NewYork
    SanFrancisco -> LosAngeles -> LasVegas -> Phoenix -> SaltLakeCity -> Denver -> KansasCity -> Minneapolis -> Chicago -> Cleveland -> NewYork
    Total weight: 4365.00

.. code-block:: shell

    $ ./toposort -g examples/flow.graph
    START R1 R2 R3 R4 R5 R6 END

The first executable does a `best-first search <https://en.wikipedia.org/wiki/Best-first_search>`__
on the graph, while the second executable does a `topological sort <https://en.wikipedia.org/wiki/Topological_sorting>`__.

CMake
-----

TODO

Submitting your homework
------------------------

Before submitting, make sure you’ve added, committed, and pushed all
your work to GitHub. When submitting through Gradescope, you will be given the option of
uploading a GitHub repository. Make sure you select your ``hw3-GITHUB_USERNAME``
repository, with “main” as the branch. Please note that you can submit as many times as
you want before the deadline.

Once you submit your files, an “autograder” will run. This won’t
actually be doing any grading, but it will try to build your code, to
make sure you don’t have any compiler errors, etc. If you do, make sure
to fix them and re-submit again.
