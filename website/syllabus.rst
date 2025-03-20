Syllabus
========

..
    .. note::

        If you are registered for CMSC 22000, please bear in mind that all
        the latest course materials can be found in the course's Canvas site.

Course Description
------------------

This class expands on the software development topics introduced
in CMSC 14200 Introduction to Computer Science 2, and uses the
development of web-based applications as a vehicle to explore
several concepts that reoccur frequently in modern software development, such
as client/server software, databases, data modeling, APIs, software
deployment, and software observability. This class also emphasizes
how software development is a highly
collaborative activity, where certain skills, like effective
communication and the ability to give/receive feedback, can be key to
the success of a software project.

More specifically, in this course, students will learn how to…

- … implement and deploy web applications with a database-driven backend.
- … understand basic foundational concepts in databases and computer
  networking that are relevant in many modern software systems, including
  the design of object-relational schemas.
- … follow a software development process/methodology to manage the life
  cycle of a software system, and use tools that support the software
  development process (e.g., testing frameworks, debuggers, linters/formatters,
  logging frameworks, etc.)
- … develop software collaboratively through (a) the use of tools, systems,
  and best practices available to facilitate that collaboration (e.g.,
  version control systems, code reviews, task tracking, etc.), and (b)
  exercising collaborative skills (communication, giving/accepting feedback, etc.)

The class will cover foundational topics in software development in
lectures, and will involve the development of a deployable web application
throughout a series of homeworks. The course also features a
collaborative quarter-long project, where the entire class, divided into
teams with specific responsibilities, will work on developing new
features for an existing software system.

Prerequisites
~~~~~~~~~~~~~

Students must have taken CMSC 14200. We recommend taking the class within
a year of completing CMSC 14200.

Space permitting, in Spring 2025 we may allow students who took CMSC 15200
or CMSC 16200 to take the class, with the understanding that they may need
to do a large amount of self-guided study to cover the topics we assume
from students coming out of CMSC 14200, including fluency in Python.

Course Organization
-------------------

A large part of the class will revolve around the development of a
software project where students will be able to apply many of the
concepts covered in the lectures. In this project, the
entire class will work on the same code (through a public GitHub
repository visible to the entire class). Students will be divided into
teams of 4-5 students, and each team will work on a specific aspect of
the project. In each team, a TA will act as the senior developer in the
team. Students will be assessed both on their performance as a team, as
well as on their performance on individual tasks assigned to them in
their teams.

To practice some of the concepts and skills they will need to apply
in the project, students will also work on a series of individual
homeworks where they will progressively build a small web application.

Both the course project and the homeworks are described in more detail below.

For a complete schedule of lectures and other milestones, please see
the `Course Calendar <calendar.html>`__.

Lectures
~~~~~~~~

The class meets in-person three times a week for lectures (MWF 2:30pm - 3:20pm in Ryerson 251).

During the first three weeks of the quarter, the lectures will focus on
foundational concepts related to the design
and implementation of web applications, including client/server software, databases,
data design, and APIs. Bear in mind that, while we will be focusing on web applications,
these are concepts that show up in many other contexts.

Starting in week 4, the focus of the class will shift towards the
development of the course project, and the lecture sessions
will switch to the following:

* **Mondays**: *Sprint reviews and all-hands meetings*. In these sessions, each team will deliver an update on their work so far, and we will also cover some content related to software project management.
* **Wednesdays**: *Traditional lecture*, supplemented with some readings and pre-recorded lectures.
* **Friday**: *Guest lecture / Panel discussion with outside speakers*

Discussion Sessions
~~~~~~~~~~~~~~~~~~~

The class has a discussion session on Mondays 4:30pm-5:50pm. During weeks 1-3,
this discussion session will be held in Stuart 101, and will be used to hold a
series of supplementary lectures/discussions with the entire class.

- **Monday, March 24th**: *Using AI as a Software Developer*
- **Monday, March 31st**: *Data Modelling Exercise*. Project teams will be formed by this date, and you will work as a team on designing a data model, followed by an all-class discussion on the data model.
- **Monday, April 7th**: *Project Kick-off*. This session will serve to introduce the course project, with time allocated for each team to discuss what components they are most interested in developing.

Starting in Week 4, the discusison session will be used for project team
meetings. In these meetings, each team will meet with their TA to plan their work for the week, and review progress so far.


Project
~~~~~~~

The course project revolves around developing a complex software system.
The scope and complexity of this project will require that the entire
class work together towards developing a fully-featured software
product.

More specifically, the entire class will be working on the same
codebase. The class will be divided into teams of 4-5 students, with an
undergraduate TA acting as a “senior developer” in each of these teams
(TAs will be students who have previously taken CMSC 22000 and/or who
have prior industry experience via internships). Teams will be arranged
by the instructor/TAs (they will not be self-selecting).

During Weeks 2-3, the teams will work on two warm-up exercises:

- **Warm-up #1: Homework Data Design**. The team will work together on
  the data design for the web application developed in the homeworks.
- **Warm-up #2: Using Git Collaboratively**. In this exercise, the team
  will create a team repository, and will gain experience with using
  Git collaboratively, as well as using GitHub Issues and Pull Requests,
  which will be an important part of the project.

Starting in Week 4, project planning will follow a Scrum-like process,
with weeks 4-9 of the quarter being divided into several sprints.
Starting on Week 4, all teams have an all-hands meeting during Monday
class hours, and each team will have an additional team meeting during
the discussion section of the class. Teams will keep track of their tasks
through GitHub Issues, with grading primarily based on their performance
on these tasks.

Homework
~~~~~~~~

Throughout the quarter, students will individually build a small web
application through a series of weekly homeworks. These homeworks will
allow students to get hands-on exposure to many of the concepts
covered in lectures, and will provide preparation for the course project.

While the homeworks will be done individually, the data design for the
web application will be done collaboratively in the same teams as
the course project.

By the end of the quarter, each student with have a deployable web application
that they are welcome to deploy publicly on a cloud provider, so they can demonstrate
the application to friends, colleagues, prospective employers, etc.

Books
-----

This class does not have a required textbook, and we will provide lecture
notes for the content covered in lectures.

We recommend the following two books for anyone who would like to learn
more about software engineering specifically:

- `A Philosophy of Software Design <https://www.amazon.com/Philosophy-Software-Design-2nd/dp/173210221X>`__, John Ousterhout
- `Software Engineering <http://iansommerville.com/software-engineering-book/>`__, Ian Sommerville


Grading
-------

Like CMSC 14200, we will be using a form of grading known as *specifications grading*.
The goal of specifications grading is to help students focus on their mastery of the
material and to identify areas for improvement as the quarter progresses. You will
get the most out of this scheme if you focus on *skills*, not on scores.

All work in this course will be evaluated using a E/S/N/U scale:

- **Excellent** (E): The work is either perfect, or has only very minor flaws. In some coursework,
  achieving an E will require completing extra work above and beyond what is required to earn an S.
- **Satisfactory** (S): The student has put in a good-faith effort to complete all the work
  and demonstrated sufficient mastery of the material.
- **Needs Improvement** (N): The student has put in a good-faith effort to complete the work,
  but revealed a lack of mastery in the material that can be addressed via concrete feedback.
  The work could become Satisfactory, or even Excellent, with revisions.
- **Unsatisfactory** (U): The student did not make a good-faith effort to complete the work.
  For example, they submitted no work at all, or some token amount of work. *Some coursework
  may specify a specific minimum amount of work to complete to avoid a U.*

This is often referred to as the ESNU scale. All assigned work will include a more precise
specification of what is required for an E, S, N, or U in that particular piece of work.

Your final grade will be determined based on the ESNU scores you will earn in the following
coursework:

- Homeworks
- Project

  - Individual Project Tasks
  - Project Warm-up Exercises
  - Peer Feedback Exercises
  - Final Project Presentation

Homeworks
~~~~~~~~~

There are seven homeworks (HW #0 - HW #6), with each homework building on the previous one.
You will receive one ESNU score per homework, *except* in Homeworks #0 and #1, where the highest
score will be an S.

If you receive an N in a homework, you will be able to address the issues with that homework
(to get your score up to an S or E) no later than two homeworks afterwards. For example,
suppose you receive an N in HW #2. You will be given specific feedback on what needs to be
improved, and will be able to address it in your HW #4 submission.

Please note that, for homeworks #5 and #6, there will be a special homework deadline (the
"Final Homework Submission") where you will be able to address any remaining issues in those homeworks.

Homeworks #2 - #6 will include a series of additional tasks that you will need to complete
to earn an E in those homeworks. As we'll describe below, these E's will be necessary to
earn certain grades.

Individual Project Tasks
~~~~~~~~~~~~~~~~~~~~~~~~

In the course project, you will be largely assessed on how well you follow a software
development process, based on how you manage issues and pull requests in the project.
Each time you complete an issue or a pull request, you will earn an ESNU score and,
depending on the score and the type of task, you will accrue a certain number of points
(the exact scheme will be available once we publish the details of the project).

While these tasks cannot be resubmitted, there are effectively unbounded opportunities
to complete tasks and accrue points. So, a poor performance in one task can be made up
by completing a different task.

The number of points you accrue (i.e., the number of tasks you complete that are of,
at least, a certain quality) will factor into your final grade.

Project Warm-Up Exercises
~~~~~~~~~~~~~~~~~~~~~~~~~

The project has two warm-up exercises, each of which contribute a SNU score to your final grade.
These exercises are done as a team, and the entire team receives the same SNU score based on
the work submitted by the team.

For the first warm-up exercise (coming up with the data model for the homeworks), there will be
an explicit resubmission deadline later in the quarter for any designs that do not earn an S.

For the second warm-up exercise (building familiarity with using GitHub collaboratively), teams
that do not earn an S will be given specific goals to accomplish during Sprint #1 of the project
to demonstrate that they understand how to use GitHub in the context of the project. As long
as those goals are met, the score will be changed to an S.

Peer Feedback Exercises
~~~~~~~~~~~~~~~~~~~~~~~

The peer feedback exercises contribute a single SNU score to your final grade.

There are two rounds of peer feedback, where you will be assessed on the quality
of the feedback you deliver to your peers (you will *not* be assessed based on
the feedback others give you).

If there are any concerns with the quality of
your first round of feedback, you will be told exactly what needs to improve in
the second round of feedback. As long as those issues are addressed,
you will receive an S in your peer feedback.

Final Report and Demo
~~~~~~~~~~~~~~~~~~~~~

The final component of this course will be a final report, where each team will summarize the work they have done throughout the quarter, as well as a live demo. The demos will take place during the “final exam” slot for the class (date/time TBD). The final report is due Friday, May 30th, 8pm.

The final report and demo each contribute one SNU score to your final grade.

Final Grade
~~~~~~~~~~~

Your final grade will be computed based on the following scores:

- 7 ESNU scores from the homeworks (of which, at most five will be E's)
- 2 SNU scores from the Project Warm-up Exercises
- 1 SNU score from the Peer Feedback
- 2 SNU scores from the final report and demo
- The "Project Points" you accrue in the course project.

In other words, there are 12 ESNU scores (of which, at most five can be an E).

You should avoid thinking of these scores as making up some percent of your grade.
For example, the fact that there are 7 scores for the homeworks, and 5 scores related
to the project, does not mean that the homeworks are worth 58% of your grade.

Instead, your grade will be determined based on the table below, where each row
specifies the minimum number of scores that you must achieve to earn that grade. You
will earn the highest grade for which you meet *all* requirements.

.. cssclass:: table-bordered

+----+----------------+-------+-----+---+
|    | Project Points | N+S+E | S+E | E |
+====+================+=======+=====+===+
| A  | 400+           | 12    | 12  | 4 |
+----+----------------+-------+-----+---+
| A- | 300+           | 12    | 10  | 2 |
+----+----------------+-------+-----+---+
| B+ | 200+           | 12    | 10  | 0 |
+----+----------------+-------+-----+---+
| B  | < 200          | 12    | 10  | 0 |
+----+                +-------+-----+---+
| B- |                | 10    | 10  | 0 |
+----+----------------+-------+-----+---+

In this table, the project columns represent the following:

- **Project Points**: The points you can accrue in the course project by completing issues and pull requests.
- **N + S + E**: The minimum number of non-Unsatisfactory scores (i.e., N's, S's, and E's) achieved by the student. This represents the amount of work the student has done in good faith.
- **S + E**: The minimum number of scores that are, at least, Satisfactory. This represents the amount of work that the student has done in good faith, and which is at least satisfactory.
- **E**: The minimum number of Excellent scores. This represents the amount of work done by the student that is of superior quality.

Please note that anyone below the B- requirements will be dealt with on a case-by-case basis.


Policies
--------

Late Submissions
~~~~~~~~~~~~~~~~

Late submissions will not be accepted in this class, except under extraordinary circumstances. Please bear in mind
that, given that you can resubmit most of the work in the class, it is ok to submit a less-than-ideal piece of work by the
deadline, as you will have an opportunity to revise it later on.

That said, to be clear: **if you encounter some sort of emergency (medical, family, etc.) please reach out to us as soon as you are able to do so**. We are more than happy to find ways to provide additional flexibility in these situations. Ideally, you should notify us of these circumstances before the work is due so we can discuss options with you.

In other words, our late submission policy applies to *ordinary* circumstances: if you are having a busy week, if your RSO has an event that overlaps with a deadline, etc., then you should rely on the resubmission policy to give you some extra flexibility: instead of trying to argue for a few extra days to work on an assignment, you should just submit the work you have completed by the deadline, so you can get feedback on that work and use that feedback to improve your work.


Grading Disputes
~~~~~~~~~~~~~~~~

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

Academic Integrity
~~~~~~~~~~~~~~~~~~

While we take academic integrity seriously, we are also mindful that,
in this class, you will be allowed and encouraged to collaborate heavily
with your classmates, as well as use technologies and resources that might
not be allowed in other contexts.

That said, there **will** be certain constraints on how/when to collaborate with
other students, and when to use certain technologies, particularly
AI tools. Our `Academic Integrity <academic-integrity.html>`__ page provides an
in-depth discussion of what is and isn't allowed in this class.
It is your responsibility to read and understand the contents of
that page.

Code of Conduct for Course Staff
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This class has a `Code of Conduct for Course Staff <code-of-conduct.html>`__.
We share this code of conduct with you (the students) so you know the
expectations we have set for our staff and, while we expect and hope they
will scrupulously follow this code of conduct, you should let us know if
you witness or experience a code of conduct violation. This will allow us
to continue to improve the student experience in this class, and to prevent
any issues from reocurring.


Diversity statement
~~~~~~~~~~~~~~~~~~~

The University of Chicago is committed to diversity and rigorous inquiry that arises from multiple
perspectives. We concur with that commitment and also believe that we have the highest quality
interactions and can creatively solve more problems when we recognize and share our diversity. We thus
expect to maintain a productive learning environment based upon open communication, mutual respect,
and non-discrimination. We view the diversity that students bring to this class as a resource, strength and
benefit. It is our intent to present materials and activities that are respectful of diversity: gender,
sexuality, disability, socioeconomic status, ethnicity, race, religious background, and immigration status.
Any suggestions as to how to further such a positive and open environment in the class will be
appreciated and given serious consideration.

If you have a preferred name different from what appears on the class roster, or preferred gender pronouns
you would like us to use, please let us know.

Accessibility statement
~~~~~~~~~~~~~~~~~~~~~~~

The University of Chicago is committed to ensuring equitable access to our academic
programs and services. Students with disabilities who have been approved for the use of
academic accommodations by `Student Disability Services <https://disabilities.uchicago.edu/>`__ (SDS) and need a reasonable
accommodation(s) to participate fully in this course should follow the procedures
established by SDS for using accommodations. Timely notifications are required in order to
ensure that your accommodations can be implemented. Please meet with me to discuss
your access needs in this class after you have completed the SDS procedures for
requesting accommodations.

Phone: (773) 702-6000
Email: disabilities@uchicago.edu

