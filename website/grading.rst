.. _grading:

Grading
=======



This year (2022), we have overhauled the grading scheme in CMSC 22000, and are following a *specifications grading* approach. Many of you have likely not encountered specifications grading before, so we encourage you to carefully read this page to make sure you understand how it works.

Coursework Grading Scale
------------------------

Specifications grading is a learning-focused approach that prioritizes student learning over scores or grades. A key aspect of specifications grading is to provide opportunities for students to learn from their mistakes and demonstrate growth and
improvement throughout the quarter.

However, the traditional 0-100 grading scale makes it challenging for a student to understand
if their work needs improvement (and how much improvement). For example, getting 85 points out of 100 on a project could be considered an excellent
performance in one class, but a dismal score in a different class. Providing medians and quartiles may not be helpful,
as it only tells you how you performed relative to the rest of the class; again, 85 points might be an excellent score
in an absolute sense, but may lead you to believe it's a poor score because everyone else in the class happened to
do much better than you.

So, this year, coursework in this class will be scored according to the following scale:

- **Excellent** (E): The work is either perfect, or has only very minor flaws.
- **Satisfactory** (S): While the work has some room for improvement, the student has put in a good-faith effort to complete all the work and demonstrated sufficient mastery of the material. Only minor revisions would be needed for the work to be Excellent.
- **Needs Improvement** (N): The student has put in a good-faith effort to complete the work, but revealed a lack of mastery in the material that can be addressed via concrete feedback. The work could become Satisfactory or Excellent with some major revisions.
- **Ungradable** (U): The student did not make a good-faith effort to complete the work. This includes not submitting the work at all, but also situations like submitting only placeholder code, work that barely passes any tests, etc.

This is often referred to as the ESNU scale. It is important that you avoid thinking of these scores in terms of how they map to an A, B, C, etc. (the manner in which we compute your final grade is described below). The ESNU scale is intended to help you understand your mastery of the material, so you can identify areas for improvement as the quarter progresses. All assigned work will include a more precise specification of what is required for an E, S, N, or U in that particular piece of work.

Resubmissions
-------------

Another key aspect of specifications grading is lowering the stakes of any individual assignment. In other words,
a poor performance in one assignment should not tank your grade for the entire quarter, and (as noted earlier)
there should be an opportunity for you to demonstrate you've learned from those mistakes and are able to
improve your work.

One way of accomplishing this is by allowing students to submit a revised version of their work after
they've gotten feedback from the graders. In this class, you will be allowed to resubmit your work as follows:

- **Homeworks**: You are allowed to resubmit **at most two** homeworks. Once a homework is returned to you,
  you will typically have one week to submit a revised version that addresses any feedback you received
  from the graders.
- **Individual Project Tasks**: While you will not be able to resubmit tasks themselves, the project is
  structured in such a way that there are multiple (and potentially unbound) opportunities to earn scores
  via the project tasks.
- **Project Design Warm-up**: The Design Warm-up is divided into two parts. You will receive feedback on
  the first part before the second part is due, but you will also have a chance to submit a revised version
  after the second part is returned to you.
- **Peer Feedback**: There are two rounds of peer feedback, and only the second round will affect your
  final grade. If there are any concerns with the quality of your first round of feedback, you will get
  the highest score possible in the second round as long as those concerns are addressed.


Late Submissions
----------------

Late submissions will not be accepted in this class, except under extraordinary circumstances. Please bear in mind
that, given that you can resubmit most of the work in the class, it is ok to submit a less-than-ideal piece of work by the
deadline, as you will have an opportunity to revise it later on.

That said, to be clear: **if you encounter some sort of emergency (medical, family, etc.) please reach out to us as soon as you are able to do so**. We are more than happy to find ways to provide additional flexibility in these situations. Ideally, you should notify us of these circumstances before the work is due so we can discuss options with you.

In other words, our late submission policy applies to *ordinary* circumstances: if you are having a busy week, if your RSO has an event that overlaps with a deadline, etc., then you should rely on the resubmission policy to give you some extra flexibility: instead of trying to argue for a few extra days to work on an assignment, you should just submit the work you have completed by the deadline, so you can get feedback on that work and use that feedback to improve your work.


Final Grade
-----------

Your final grade will be computed based on the following scores:

- 8 ESNU scores from the homeworks.
- 1 ESNU score from the Project Design Warm-up
- 1 SNU score from the Peer Feedback
- 1 ESNU score from the Final Presentation
- The "Project Points" you accrue in the course project.

In other words, there are 11 ESNU scores (of which, at most 10 can be an E).

You should avoid thinking of these scores as making up some percent of your grade.
For example, the fact that there are 8 scores for the homeworks, and 3 scores related
to the project, does not mean that the homeworks are worth 72% of your grade.

Instead, your grade will be determined based on the table below, where each row
specifies the minimum number of scores that you must achieve to earn that grade. You
will earn the highest grade for which you meet *all* requirements.

.. cssclass:: table-bordered

+----+----------------+-------+-----+---+
|    | Project Points | N+S+E | S+E | E |
+====+================+=======+=====+===+
| A  | 200+           | 11    | 10  | 8 |
+----+----------------+-------+-----+---+
| A- | 150+           | 11    | 10  | 5 |
+----+----------------+-------+-----+---+
| B+ | 100+           | 11    | 8   | 0 |
+----+----------------+-------+-----+---+
| B  | < 100          | 9     | 7   | 0 |
+----+                +-------+-----+---+
| B- |                | 9     | 5   | 0 |
+----+----------------+-------+-----+---+

In this table, the project columns represent the following:

- **Project Points**: The points you can accrue in the course project by completing issues and pull requests.
  Please see the `Project Policies <project/policies.html>`__ page for more details on this.
- **N + S + E**: The minimum number of non-Ungradeable scores (i.e., N's, S's, and E's) achieved by the student. This represents the amount of work the student has done in good faith.
- **S + E**: The minimum number of scores that are, at least, Satisfactory. This represents the amount of work that the student has done in good faith, and which has room for only moderate/minor improvement.
- **E**: The minimum number of Excellent scores. This represents the amount of work done by the student that is of superior quality.

Please note that anyone below the B- requirements will be dealt with on a case-by-case basis.

Grading Disputes
----------------

Except in very specific cases (described below), you cannot dispute the score assigned to you on a piece of work. The score you receive on a piece of work is meant to convey feedback on your level of mastery, and you should take it as an opportunity to understand the areas of improvement in your work. You are more than welcome to ask us for concrete advice on how to improve your work, and we are always more than happy to have those kind of conversations with students, including going over your code. On the other hand, we will not entertain requests to change your score just because you feel your work deserved a higher score.

There is one exception to this: if a grader made a factual mistake in your grading.
Please note that this only includes cases where a grader makes an erroneous
statement about your work in their feedback. It does not include cases where
you simply disagree with whether something deserves to be flagged as incorrect.

For example, suppose you receive a piece of feedback that says
"Incorrect: Function X did not check that parameter Y is greater than zero".
If function X in your code *did* perform this check, and the grader
missed this fact (and erroneously gave you that feedback), you can ask
us to review this decision. Please note that, even
if the feedback is amended, it may not affect your actual ESNU score.

We ask that you keep
these requests brief and to the point: no more than a few sentences identifying
the exact statement that the grader made and the reasons you believe the statement was mistaken, including
references to specific parts of your code (e.g., "I did check the value of the
parameter in line 107"). Focus on laying out the facts, and nothing else.

Finally, it is also your responsibility to make
these requests in a timely manner. Requests to review grading mistakes must be submitted
no later than **one week** after a graded piece of work is returned to you.
After that time, we will not consider any such requests,
*regardless of whether the request is reasonable and justified*.