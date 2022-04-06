Homework 2 Rubric
=================

The grading of this project follows a specifications grading approach. If you have not already
done so, make sure to read our `Grading <../grading.html>`__ page for more details.

When grading your work, the graders will be checking for the following issues in your code. Please
note that some of the issues are labelled as "[Major]" (these will have a greater effect on your score
for the homework)

Task 1
------

- [Major] Did not implement any of the required functions (``segment_new``, ``segment_init``, or ``segment_free``)
- Implemented some, but not all of the required functions (``segment_new``, ``segment_init``, or ``segment_free``)
- Defined a segment type that does not use the ``point_t`` type to represent points.
- Does not use the ``point_t`` type to represent points in the parameters to  ``segment_new`` or ``segment_init``.

Task 2
------

- [Major] Did not move ``segment_intersect`` or ``on_segment`` from the Point module to the new Segment module.
- Did not update the parameters of ``segment_intersect`` or ``on_segment`` to use the new segment type.
- Did not add the ``orientation`` function (renamed to ``point_orientation``) to the Point header file.

Task 3
------

- [Major] Did not update the call to ``segment_intersect`` in ``polygon_add_point``

Task 4
------

- [Major] Did not update the call to ``segment_intersect`` in ``check_intersect``.
- The library builds correctly, but the tests do not.
- The library and the tests build correctly, but the tests fail.

General
-------

- Running "make" fails to build the library.
- Running "make" builds the library, but produces "implicit declaration" warnings (note: this usually means you forgot to ``#include``
  a header file, or forgot to include a function in that header file)


ESNU Score
----------

The ESNU score will be determined as follows:

- Excellent: No major issues, and at most one other issue.
- Satisfactory: No major issues, and at most three other issues.
- Needs Improvement: At least one major issue, or five other issues.
- Ungradable: Two or more major issues.