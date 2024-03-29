Syllabus
========

.. warning::

    CMSC 22000 is undergoing a major redesign in Autumn 2023. The syllabus below already reflects all the changes done for the Autumn 2023 offering, but is still subject to change.

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

Space permitting, in Autumn 2023 we may allow students who took CMSC 15200
or CMSC 16200 to take the class, with the understanding that they may need
to do a large amount of self-guided study to cover the topics we assume
from students coming out of CMSC 14200, including fluency in Python.

Course Organization
-------------------

The class meets in-person three times a week for lectures (MWF 1:30pm - 2:20pm in Ryerson 277).

The content covered in the lectures is divided into two blocks:

- **Weeks 1-4: Software Design and Implementation**

  These lectures will focus on covering several foundational concepts related to the design
  and implementation of web applications, including client/server software, databases,
  data design, and APIs. Bear in mind that, while we will be focusing on web applications,
  these are concepts that show up in many other contexts.

- **Weeks 5-9: Software Validation, Deployment, and Evolution**

  In CMSC 14200, we dealt with applications that ran on a single machine. Now,
  we will deal with applications that run on a server, and may involve invoking
  multiple external APIs. We will cover integration testing in more depth,
  how these kind of applications are deployed to users, and how to monitor
  and maintain such applications.

Additionally, we have time reserved on Mondays 4:30pm-5:50pm for project
teams meetings (this is listed as a “discussion” on the Registrar’s site, but
please note that it is not a traditional discussion session). These project team
meetings will start on Week 3.

A large part of the class will revolve around the development of a
software project where students will be able to apply many of the
concepts covered in the lectures (this project is described in more
detail in the “Course Project” section below). In this project, the
entire class will work on the same code (through a public GitHub
repository visible to the entire class). Students will be divided into
teams of 4-5 students, and each team will work on a specific aspect of
the project. In each team, a TA will act as the senior developer in the
team. Students will be assessed both on their performance as a team, as
well as on their performance on individual tasks assigned to them in
their teams.

Starting in week 4, the Monday lecture will be used to hold an all-hands
meeting for the project, where we will cover some content related to
software project management, and will also ask each team to deliver an
update on their work so far.

Please see the `Course Calendar <calendar.html>`__ for more details.

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

During Weeks 2-4, the teams will work on two warm-up exercises:

- **Warm-up #1: Using Git Collaboratively**. In this exercise, the team
  will create a team repository, and will gain experience with using
  Git collaboratively, as well as using GitHub Issues and Pull Requests,
  which will be an important part of the project.
- **Warm-up #2: Homework Data Design**. The team will work together on
  the data design for the web application developed in the homeworks.

Starting in Week 5, project planning will follow a Scrum-like process,
with weeks 5-9 of the quarter being divided into several sprints.
Starting on Week 3, all teams have an all-hands meeting during Monday
class hours, and each team will have an additional team meeting during
the discussion section of the class. Teams will keep track of their tasks
through GitHub Issues, with grading primarily based on their performance
on these tasks.

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

Please see our `Grading <grading.html>`__ page.


Policies
--------

Code of Conduct for Course Staff
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This class has a `Code of Conduct for Course Staff <code-of-conduct.html>`__.
We share this code of conduct with you (the students) so you know the
expectations we have set for our staff and, while we expect and hope they
will scrupulously follow this code of conduct, you should let us know if
you witness or experience a code of conduct violation. This will allow us
to continue to improve the student experience in this class, and to prevent
any issues from reocurring.

Policy on academic honesty
~~~~~~~~~~~~~~~~~~~~~~~~~~

We take academic honesty very seriously in this class. Please make sure to
read our `Academic Honesty <academic-honesty.html>`__ page. Please note that
this policy applies primarily to the homework assignments,
which must be completed individually. We also have a specific policy on
the use of Generative AI systems, which you can find below.

On the other hand, the project is structured
in such a way that you can collaborate and share code with anyone in the class,
and even use code you find on the Internet. However,
this can lead to a number of gray areas where it may be hard to tell if
your work is academically honest.

For example, the following are activities that may be considered academically
dishonest in other contexts, but are acceptable in the project:

- Taking a snippet of code you find on Stack Overflow (as long as you provide attribution)
- Adding a large piece of code not written by yourself (e.g., a third-party library), as long as you
  provide attribution and your use of that code does not violate the terms of a software license.
- Asking someone outside the class for help with writing your code, as long as you credit
  them somewhere.
- Posting on online forums for help with figuring out a issue with your code (we would prefer
  that you ask those questions directly to us but, to be clear, using external forums in this way
  is not forbidden).
- Using Generative AI systems (we expand on this in the section below)

In general, we will not be policing the attribution of small-scale contributions by outside
sources, but it is still important that you include those attributions from a documentation
perspective.

On the other hand, the following are examples of behaviour that would be considered
academically dishonest in the project:

- Having someone outside the class do your assigned tasks in the project (as opposed to
  just getting assistance from them)
- Taking credit for work that someone else in the class did. Please note that there are many situations
  where students will legitimately *share* credit for a piece of work;
  what would be unacceptable would be to falsely take sole credit for work you did not do,
  as a way to improve your score in the class.

If you are ever concerned that you may be doing something that could be considered academically
dishonest, please don't hesitate to ask us for clarification. We are always happy to answer
these kind of questions.

Policy on Generative AI
~~~~~~~~~~~~~~~~~~~~~~~

Software developers are not only allowed but often encouraged to use Generative AI systems
(ChatGPT, Bard, GitHub Copilot) as a productivity tool. As such, we will have a fairly
permissive policy on the use of Generative AI systems. In general, the following uses
of Generative AI systems (GenAI) systems is allowed across all coursework:

- **Reference**: You can use GenAI to answer specific reference questions,
  in the same way you would use Google, Stack Overflow, etc. For example, it would be
  perfectly fine to ask something like "In Django, how do I model a field that can only
  take a limited set of values?"
- **Debugging**: You can use GenAI to make sense of error messages that you are struggling
  with, or to ask GenAI if it can figure out what might be wrong with a specific piece
  of code. This is similar to asking for help on an online forum like Canvas, Ed Discussion, etc.
- **Self-Study**: You can use GenAI to explore topics in more detail, or to ask for
  additional practice problems. For example, it would be acceptable to ask questions like
  "In class, we've focused mostly on web applications with Django. Given that I am mostly
  familiar with Python, can you give me a brief summary of how mobile development differs
  from web development? Would I be able to do it in Python?" or "I think I need more practice
  coming up with Django data models. Could you suggest a few exercises?"

When using GenAI systems, don't forget that these systems **have no sense
of what is true or not**, and will sometimes provide incorrect answers. It is important that you
look at answers from GenAI with a critical eye.

Finally, while GenAI can enhance your work and supplement your learning, it can also hinder
your learning in some cases, or lead to academic honesty concerns. We will provide more specific
guidance in the coursework regarding what activities are not allowed, as certain things that
would be permissible in the project may not be permissible in the homeworks.

Please bear in mind that there will be situations where will ask you to work on a task by yourself
without any assistance from GenAI, because we feel you will learn more effectively that way.
For example, when coming up with the data design for the homeworks, GenAI could certainly suggest
many different designs to choose from, but it will be challenging for you to look at those designs
critically, and assess whether they meet your requirements, if you don't have any experience
coming up with data designs yourselves. Additionally, the goal in that exercise is also for you
to work collaboratively in a team to arrive at a design you are all happy with.

If you are concerned about academic honesty issues, a good heuristic to use in order to figure
out what is or isn’t appropriate is to imagine GenAI systems as a **helpful but fallible classmate**.
For example, it is generally appropriate to review lecture notes with a classmate and ask questions
about concepts you didn't fully understand. So, asking GenAI about this is likely fine. On the other
hand, it is never fine to ask a classmate to write a homework for you. So, unless you've been told
it is ok to do this with GenAI, then this would be an inappropriate use of GenAI.

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

