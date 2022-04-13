Homework 3 Rubric
=================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../grading.html>`__ page for more details.

When grading your work, the graders will be checking for the following issues in your code. Please
note that some of the issues are labelled as "[Major]" (these will have a greater effect on your score
for the homework)

Writing Makefiles + Building a library
--------------------------------------

- [Major] Not adding a ``Makefile`` in ``polygon-area``
- Adding the final (complete) ``Makefile`` in a single commit. You should try
  to make a few intermediate commits as you create the ``Makefile`` described
  in this section.

Task 1: Makefile for the micro editor
-------------------------------------

- [Major] Not adding a ``Makefile`` in ``micro-editor/``
- Having individual rules for each object file
- Not using variables (``CC``, ``CFLAGS``, etc.)
- Makefile does not correctly produce a ``micro`` executable.

Task 2: Makefile for the libgraph editor
----------------------------------------

- [Major] Not adding a ``Makefile`` in ``libgraph/``
- Having individual rules for each object file
- Having individual rules for each executable
- Not using variables (``CC``, ``CFLAGS``, etc.)
- Makefile does not correctly produce a ``libgraph.so`` library.
- Makefile does not correctly produce a ``best-first`` or ``toposort`` executable.

ESNU Score
----------

The ESNU score will be determined as follows:

- Excellent: No major issues, and at most one other issue.
- Satisfactory: No major issues, and at most three other issues.
- Needs Improvement: At least one major issue, or five other issues.
- Ungradable: Two or more major issues.