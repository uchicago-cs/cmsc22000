Homework 5: Testing
===================

**Due:** Wednesday, May 5th, 8pm CDT

By this point in your CS studies, you’ve probably experienced the
following at least once:

1. Your programming assignment is almost done, and everything works so
   far.
2. Start working on the last task of the assignment.
3. Make some minor changes.
4. Run program.
5. Everything stops working. The first task, the last task, and
   everything in between.
6. Spend several hours debugging your code.
7. Narrow down the issue to a silly mistake in the first task that only
   made things fail once the last task was implemented.
8. Ponder all the fun stuff you could’ve done if you had come to that
   realization sooner.

It would’ve been nice if, once we implemented that last task, there was
some mechanism to check whether our changes had broken other parts of
the code which we assumed to be working correctly. This is one of the
things that we can do by writing *tests* for our code. Besides
reassuring us that our code does what it is supposed to do, it can also
make debugging a much more painless experience, by quickly narrowing
down our search for the part of our code that is failing.

Generally speaking, there are two kinds of tests: *unit tests* and
*integration tests*. In this homework we will focus on *unit tests*, which
check the correctness of a single component or module, typically by
testing individual functions within that component. *Integration tests*,
on the other hand, check the correctness of multiple components at once,
or of an entire system.

By the end of this homework, you’ll have experience writing unit tests, as
well as an appreciation for their importance. You’ll be writing tests
for existing code, as well as using the practice of *Test-Driven
Development* to develop new code.

Creating your homework repository
---------------------------------

Like previous homeworks, we will provide you with an *invitation URL* that
will allow you sign up for the homework assignment on GitHub, and which will
result in the creation of a repository called
``2021-hw5-GITHUB_USERNAME`` inside our ``uchicago-cmsc22000`` organization
on GitHub.

Your repository will be seeded with some files for the homework
and, more specifically, will contain a ``libgeometry`` directory with an
updated version of ``libgeometry`` with the refactored ``segment``
module we asked you to implement in Homework #5.



Task 0: A bit about ``criterion``
=================================

The ``libgeometry`` library already includes several unit tests, which
use a testing framework called
`Criterion <https://github.com/Snaipe/Criterion>`__. This framework is
already installed on the CS machines. Let’s learn a little bit about
this testing framework before we get to the actual tasks for this homework.
Consider the following sample tests:

.. code:: c

   Test(foo, add)
   {
       int x, y;

       x = 4;
       y = 5;

       cr_assert_eq(x + y, 9, “4 + 5 should be 9!”);
       cr_assert_eq(x + y, y + x, “Addition should be commutative!”);
   }

   Test(foo, subtract)
   {
       int x, y;

       x = 2;
       y = 10;

       cr_assert_eq(y - x, 8, “10 - 2 should be 8!”);
       cr_assert_eq(x - y, -8, “2 - 10 should be -8!”);
   }

Let’s unpack what’s going on here. First of all, ``Test`` is actually a
`macro <https://en.wikipedia.org/wiki/C_preprocessor>`__, not a
function. We’re not defining two functions both called ``Test``, we’re
calling the ``Test`` macro twice (this will actually result in two
functions being generated, one for each test; the ``Test`` macro just
provides a more convenient syntax to define the functions that Criterion
expects).

``Test`` takes two arguments (strictly speaking it actually supports
many more, but for our purposes we’ll only need these two): a *suite
name* and a *test name*. The suite name is just the name of the relevant
context: if you take a look at ``test_point.c`` and ``test_polygon.c``,
you’ll see that the suite names are just ``point`` and ``polygon``. The
test name should just be a short identifier of what the test is testing.

Now let’s discuss the meat of these tests. Each test makes two
*assertions* and exits. An assertion tests the validity of a given
statement, and panics (causes the test to fail) if the statement is
invalid. The way we make an assertion in ``criterion`` is by calling any
one of a number of functions prefixed by ``cr_assert`` (you can find a
full reference
`here <https://criterion.readthedocs.io/en/master/assert.html#assertions-ref>`__).
These tests use ``cr_assert_eq``, which takes 3 arguments. It checks
whether the first argument is equal to the second, and if not, causes
the test to fail and prints out the error message given in the third
argument (for those of you who took CS 151, this is very similar to
Racket’s ``check-expect`` function).

The tests are compiled into their own executable. So, if you run this:

.. code:: sh

   $ make tests

This will result in the generation of a new executable called
``tests/test-libgeometry`` which will run all the tests we specified
inside the ``tests/`` directory. Try running this executable; it should
produce the following output:

.. code:: sh

   $ tests/test-libgeometry 
   [====] Synthesis: Tested: 24 | Passing: 24 | Failing: 0 | Crashing: 0 

Note: you can use the ``--verbose`` option to get more detailed output
from Criterion.

If you look at the code inside ``tests/``, you’ll see that the bulk of
the code is in the ``test_point.c`` and ``test_polygon.c`` files, and
that these files focus exclusively on defining tests. We don’t need to
write any code to run the tests themselves, check the results of the
tests, print the output shown by ``tests/test-libgeometry``, etc.
because this is all handled for us by the Criterion framework.

Notice, however, how the ``tests/`` directory also contains a ``main.c``
file with a ``main()`` function. This is not strictly necessary, as
Criterion will provide a default ``main()`` function if we do not do so,
but providing our own ``main()`` function can allow us to customize the
behaviour of Criterion. If you’re curious, you can read more about this
in `this
page <http://criterion.readthedocs.io/en/master/internal.html?highlight=criterion_run_all_tests#providing-your-own-main>`__
of the Criterion documentation.

Before continuing, take a moment to look at the ``Makefile`` contained
inside the ``tests/`` directory, as this is the Makefile that builds the
``tests/test-libgeometry`` executable. If there is anything in that
Makefile that you do not understand, please make sure to ask us.

Task 1: Testing existing code
=============================

Remember that, in Homework #2, we asked you to refactor some of the code in
``point.c`` to a new ``segment.c`` module. At the time, you may have
asked yourself: “If I’m implementing this code as part of a library, how
can I *run* the segment code I just wrote?”. One answer to that question
is that you could’ve written a separate program that links with
libgeometry, and calls the segment functions to see whether they work
(and, with what you know about Makefiles, it should be possible for you
to do that). However, what we really want to do is write tests for this
new segment datatype, similar to the ones that already exist for the
point and polygon datatypes. In Homework #2 we asked you to simply modify the
calls to ``segment_intersect`` in ``test_point.c``, which was a
temporary solution before we learned how tests work. Now, we will write
proper tests for the segment datatype.

Create a new file in the ``libgeometry/tests/`` directory called
``test_segment.c``. You’ll need a few ``#include`` statements to get
started:

.. code:: c

   #include <criterion/criterion.h>
   #include <stdlib.h>
   #include <stdbool.h>
   #include "point.h"
   #include "segment.h"

.. note::

    Because this homework depends on the
    ``criterion`` library, you should make sure to compile and test your
    work on a CS environment, which will has the ``criterion`` library
    properly set up and ready to go. You can find instructions on how to
    access a CS environment (including options that will allow you to work
    on your computer, and just compile/run your code in a CS environment) in
    our `developer
    guide <https://uchicago-cs.github.io/dev-guide/environment.html>`__.
    While it is possible to install ``criterion`` on an unsupported machine,
    we may not be able to provide support for that setup.

You will also need to modify the ``Makefile`` in the ``tests/``
directory to add your new file.

.. warning::

    Careful: There are *three*
    ``Makefile``\ s in this project! There’s the root-level ``Makefile`` for
    building the library, a ``Makefile`` in the ``samples`` directory to
    build the sample programs, and a ``Makefile`` in the ``tests`` directory
    specifically for building test files. You should only modify this last
    ``Makefile``.

It’s time to write your first tests! In your ``test_segment.c`` file, do
the following:

-  Write at least one test case for each of ``segment_new``,
   ``segment_init``, ``segment_free``. You may find it helpful to look
   at similar tests in ``test_point.c`` and ``test_polygon.c``.
-  We already had some tests for ``segment_intersect`` in
   ``test_point.c``. *Refactor* them into ``test_segment.c``, and make
   sure they’re in the correct test suite!
-  Write test cases for ``on_segment`` and ``point_orientation``
   (previously known as ``orientation``). For these test cases, remember
   that you should have as much *coverage* as possible: your test cases
   should cover as many outcomes (and as many flows of execution through
   the individual function) as possible. You should be able to
   accomplish this by writing 3-4 tests for each function, but please
   note we won’t be grading you on the number of tests your write, but
   on how much coverage they provide.

   Note: Remember that, in Homework #2, you had the option of moving these
   functions to ``segment.c``, or to keep them in ``point.c`` (and
   exposing them through ``point.h``). In the code we’ve provided,
   ``on_segment`` has been moved to the segment module, and
   ``orientation`` has been renamed to ``point_orientation`` and
   kept in the point module (and both have been
   added to their respective module’s header file).

For each of the tests (except the ``segment_intersect`` ones refactored
from ``test_point.c``), the test must include a header comment
explaining the test. For example:

.. code:: c

   /* Checks that two parallel segments do not intersect */
   Test(segment, no_intersection_parallel)
   {
       check_intersect(2,  2, 4, 2,
                       2, 10, 4, 10,
                       false);
   }

Task 2: Test-Driven Development
===============================

*Test-Driven Development* (or *TDD* for short) is a method of
programming that uses tests to guide implementation. The goal of TDD is
to make it easier to create clean, correct code on the first try and
reduce debugging cycles. The key innovation of TDD is that it puts tests
*before* code in the development cycle. A TDD development cycle looks
something like this:

1. Write tests that cover all behavior of the interface you’re
   implementing
2. Write skeleton functions (i.e., functions that have the correct type
   signature but return dummy values, and don’t contain any logic) so
   that your program compiles
3. All of your tests fail because nothing is implemented yet
4. Inspect the first failing test. Implement the things it tests for.
5. Does the test pass? Great! Go back to step 4 for the next failing
   test. If the test doesn’t pass, debug what you implemented.

In this task, you will implement a new ``circle_t`` data structure for
representing circles in ``libgeometry``. For the purposes of this homework,
circles will be represented by a center and radius. The center will be
represented by a ``point_t``, and the radius by a ``double``.

You should create three new files: ``include/circle.h``,
``src/circle.c``, and ``tests/test_circle.c``. You will need to update
both the root-level ``Makefile`` and the ``Makefile`` in the ``tests``
directory to ensure the new files are compiled. Make a commit with the
new files as well as the changes to the ``Makefile``\ s, with the
message “Starting homework 5 task 2”.

*Don’t forget to "git add" the new
files; otherwise, they won’t be included in the commit.*

Now, use TDD to develop ``new``, ``init``, and ``free`` functions for
circles.

.. note::

    To ensure that you are following TDD, we will
    be inspecting your commit history to check that you actually wrote your
    tests first. At a minimum, we require the following workflow:

    1. Write your tests in ``tests/test_circle.c``
    2. Write a struct definition in ``include/circle.h``
    3. Write skeleton functions in ``src/circle.c``, and put their headers
       in ``include/circle.h``
    4. **Make a commit** indicating that you’ve written tests, and are about
       to start implementation
    5. Write your implementations
    6. **Make a commit** indicating that you’ve finished implementation and
       that your tests pass.

    By all means, please make more commits as you write individual tests and
    implement individual functions. This is just the *minimum* we require to
    tell whether or not you implemented tests first.

Next, let’s use TDD to implement a few slightly more complex functions
that compute things about circles:

-  ``circle_diameter``, ``circle_circumference``, and ``circle_area``.
   Each of these functions should take a pointer to a ``circle_t``
   struct as input, and return a ``double``. The logic should be
   self-explanatory.
-  ``circle_overlap``: Takes pointers to two ``circle_t`` structs as
   input, and returns one of the following values:

   -  ``0``: The circles do not overlap in any way.
   -  ``1``: The circles overlap at a singular point (you do not need to
      compute this point)
   -  ``2``: The circles overlap, and the area of overlap is non-zero
      (you do not need to compute this area). Note that this also
      includes a circle being wholly contained inside another circle.

You are allowed to consult online sources to find the exact formula for
determining whether two circles overlap (this is often referred to the
*intersection* of two circles). As usual, you must cite these sources.

When writing the tests for the first three functions, you may find the
function ``cr_assert_float_eq`` helpful. As you may know, floating-point
arithmetic on computers is not 100% accurate; ``cr_assert_float_eq``
allows you to check that the first value you supply to it is within some
range of the second value. For example:

.. code-block:: c

   circle_t *c = circle_new(point_new(0, 0), 5);
   cr_assert_float_eq(circle_area(c), 3.14159*5*5, 10E-4, "Circle area wasn’t correct!");

This checks whether or not our ``circle_area`` function is within 10-4
(0.0001) of the expected value.

As above, you should use the TDD workflow when implementing these new
functions: write the tests first, make a commit indicating you’ve
written the tests, write the implementation, and then make a commit with
that implementation.

Finally, as before, you should include header comments in all the tests
you write.

Submitting your homework
------------------------

Before submitting, make sure you’ve added, committed, and pushed all
your code to GitHub. *Don’t forget to "git add" any new files.*

When submitting through Gradescope, you will be given the option of
manually uploading files, or of uploading a GitHub repository (we
recommend the latter, as this ensures you are uploading exactly the
files that are in your repository). If you upload your repository, make
sure you select your ``2021-hw5-GITHUB_USERNAME`` repository, with
“main” as the branch. Please note that you can submit as many times as
you want before the deadline.

Once you submit your files, an “autograder” will run. This won’t
actually be doing any grading, but it will try to build your code and
run the tests, which can help you verify that your submission doesn’t
have any last-minute issues in it. If it does, make sure to fix them and
re-submit again.
