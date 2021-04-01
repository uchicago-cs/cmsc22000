Homework 2: Software Design
===========================

**Due:** Wednesday, April 14, 8pm CDT

In this homework, you will carry out some basic software design tasks. This
homework will be shorter than other homeworks, because you will also be working
on a design warmup exercise with your project team. Please note that,
while the design warmup exercise is due at the same time as this homework, it
will be part of your project score (it is not counted as an additional
homework assignment).

Creating your homework repository
---------------------------------

In this homework, you will be using a different repository than the one you
used in the previous homework (in general, GitHub will create a new
repository for each assignment). Like the previous homework, we will provide
you with an *invitation URL* that will allow you sign up for the homework
assignment on GitHub, and which will result in the creation of a
repository called ``2021-hw2-GITHUB_USERNAME``` inside our
``uchicago-cmsc22000`` organization on GitHub.

One thing that will be different in this homework is that your homework repository
will be seeded with some code. So, once you’ve signed up for the homework
assignment on GitHub, you will just need to clone the repository to
start working on it (you won’t need to run ``git init`` or add any files
to the repository before you start working on the homework).

Please note that there will be a separate invitation URL for the
team design exercise, since that will involve creating a separate
repository that your entire team has access to.

Refactoring libgeometry
-----------------------

Your repository contains a single directory ``libgeometry`` that
contains the implementation of a simple library for manipulating basic
geometric shapes. You can build the library just by running this inside
the ``libgeometry`` directory:

::

   $ make

And build some sample programs that use the library like this:

::

   $ make samples

You can run the sample program like this:

::

   $ samples/polygon-sample
   The perimeter is 8.00
   The area is 4.00

You’ll notice there is also a ``polygon-sample-static`` program as well;
you can ignore it for now.

When we get to *Implementation* in class, we’ll discuss exactly how a
“library” is built, and how it is linked with other programs. You will
not need to understand how the code is built to complete this homework.

The library currently provides two modules:

-  A Point module (``include/point.h`` and ``src/point.c``) that provides
   a number of operations on two-dimensional points
-  A Polygon module (``include/polygon.h' and ``src/polygon.c``) that
   provides a number of operations on polygons, and which depends on the
   Point module.

We encourage you to read through the above files, and ask questions if
anything is unclear in that code.

One thing to note is that the Point module provides the following
function:

::

   bool segment_intersect(point_t *p1, point_t *q1, point_t *p2, point_t *q2)

While this function operates on points, what it really does is operate
on line segments (i.e., a finite-length line in two-dimensional space,
delimited by two points). That said, placing the ``segment_intersect``
function inside ``point.c`` / ``point.h`` is arguably a valid design
choice: if segment intersection is the only operation for which we have
to work with segments, it would be potentially wasteful to spend the
time to define a Segment module just to compute segment intersections.

However, as we continue to develop libgeometry, we realize that we need
to perform segment operations in a variety of other places. So, it now
makes sense to refactor our code to add a Segment module.

You must do the following:

-  **Task 1** (30 points) Add ``segment.c`` / ``segment.h`` files with
   the implementation and interface of a new Segment data type. Make
   sure to include new/init/free functions (like the ones for Point and
   Polygon). You will also need to update the Makefile to make sure this
   new file is compiled and included in the libgeometry library. Just
   update the ``SRCS`` variable in the Makefile to include your new
   ``segment.c`` file.
-  **Task 2** (20 points) Take ``segment_intersect`` (and associated
   helper functions) out of ``point.c`` / ``point.h`` and make them a
   part of the Segment module. Take into account that this will involve
   changing the parameters of the function, since it now has to operate
   on Segments, not on Points.
-  **Task 3** (20 points) Update the Polygon implementation so it uses
   this updated ``segment_intersect`` function. At this point, you
   should be able to build the entire library by running ``make``
-  **Task 4** (30 points) Uh oh, the libgeometry library may build
   correctly, but not the tests! (try this by running ``make tests``)
   This is because they still depend on the old version of the
   ``segment_intersect`` function. This is an example of how things can
   break if dependencies are not properly managed.

   In the ``test_point.c`` file, update the intersection tests to make
   sure they use the new version of the file (you don’t need to know
   exactly how these tests work, and you can keep these tests inside the
   ``test_point.c``; in a future homework, we will see a cleaner way of
   updating the tests). Once you have fixed this, you should be able to
   run ``make tests`` followed by ``tests/test-libgeometry``.

Submitting your homework
------------------------

Before submitting, make sure you’ve added, committed, and pushed all
your code to GitHub. You will submit your code through Gradescope but,
unlike the previous homework, we need you to submit the code that is in your
repository (as opposed to filling in some text fields).

When submitting through Gradescope, you will be given the option of
manually uploading files, or of uploading a GitHub repository (we
recommend the latter, as this ensures you are uploading exactly the
files that are in your repository). If you upload your repository, make
sure you select your ``2021-hw2-GITHUB_USERNAME`` repository, with
“main” as the branch. Please note that you can submit as many times as
you want before the deadline.

Once you submit your files, an “autograder” will run. This won’t
actually be doing any grading, but it will try to build your code, to
make sure you don’t have any compiler errors, etc. If you do, make sure
to fix them and re-submit again.
