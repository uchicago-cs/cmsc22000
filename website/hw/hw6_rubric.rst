Homework 6 Rubric
=================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../grading.html>`__ page for more details.

When grading your work, the graders will be checking for the following issues in your code. Please
note that some of the issues are labelled as "[Major]" (these will have a greater effect on your score
for the homework)

Task 1
------

- Did not provide a URL for Task 1.1
- Did not provide a URL for Task 1.2, or provided a workflow that runs successfully, or fails for a reason other than the code not compiling.
- Did not provide a URL for Task 1.3, or provided a workflow that runs successfully, or fails for a reason other than the tests failing.

Task 2
------

- Did not provide a URL for Task 2.1
- Updated the matrix correctly in Task 2.1, but did not update the ``runs-on`` option (so the jobs still all run with Ubuntu 18.04)
- [Major] Did not provide a URL for Task 2.2, or provided a workflow that doesn't actually include a gcc job and clang job.
- In Task 2.2, the clang job doesn't actually use clang.
- In task 2.2, the gcc job doesn't actually use gcc.

Task 3
------
- [Major] Did not provide a URL for Task 3, or provided a workflow that doesn't include the specified matrix.
- [Major] Solved this task by updating the ``run`` option
- Added the two separate installation steps, but they are not
  being applied to the appropriate job(s).

Task 4
------
- [Major] Did not provide a URL for Task 4, or provided a workflow that doesn't include the expected three jobs.
- Specified three individual jobs instead of figuring out how to add/remove individual
  jobs from a matrix.

ESNU Score
----------

The ESNU score will be determined as follows:

- Excellent: No major issues, and at most one other issue.
- Satisfactory: No major issues, and at most three other issues.
- Needs Improvement: At least one major issue, or at least four other issues.
- Ungradable: Two or more major issues.