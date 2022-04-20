Homework 4 Rubric
=================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../grading.html>`__ page for more details.

When grading your work, the graders will be checking for the following issues in your code. Please
note that some of the issues are labelled as "[Major]" (these will have a greater effect on your score
for the homework)

Task 1
------

- ``compiler-error.c``: Fixing the wrong line, identifying the wrong error, or applying an incorrect fix.
- ``compiler-error.c``: Not specifying the before and after of the responsible line
- ``compiler-warning.c``: Fixing the wrong line, identifying the wrong error, or applying an incorrect fix.
- ``compiler-warning.c``: Not specifying the before and after of the responsible line

Task 2
------

Task 2.1
~~~~~~~~

- Identified lines that do not update ``ctx->num_rows``
- Identified lines that update ``ctx->num_rows``, but that are not related to loading the file from disk.
- [Major] Did not include GDB session

Task 2.2
~~~~~~~~

- Arrived at the wrong values for ``ctx->cx`` and ``ctx->cy``
- [Major] Did not include GDB session

Task 3
------

Bug #1
~~~~~~

- Identified the wrong line
- Did not fix the bug, or applied an incorrect fix
- [Major] Did not include GDB session


Bug #2
~~~~~~

- Identified the wrong line
- Did not fix the bug, or applied an incorrect fix
- Did not include GDB session

ESNU Score
----------

The ESNU score will be determined as follows:

- Excellent: No major issues, and at most one other issue.
- Satisfactory: No major issues, and at most three other issues.
- Needs Improvement: At least one major issue, or five other issues.
- Ungradable: Two or more major issues.

Please note that Bug #2 in Task 3 can be challenging to track down,
so the rubric for this homework is set up so that you can still
get a Satisfactory if you leave that question blank (but you must
then have no issues on the remaining questions).