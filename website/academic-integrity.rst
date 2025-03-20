Academic Integrity in CMSC 22000
================================

**(or, how to get the most out of CMSC 22000)**

In this class, we assume that you are an intellectually curious
individual who has an earnest desire to learn. We believe you care about
your education and are committed to getting the most out of this course.
More specifically, our goal is for you to learn how to:

- ... implement and deploy web applications with a database-driven backend.
- ... understand basic foundational concepts in databases and computer
  networking that are relevant in many modern software systems, including
  the design of object-relational schemas.
- ... follow a software development process/methodology to manage the life
  cycle of a software system, and use tools that support the software
  development process (e.g., testing frameworks, debuggers, linters/formatters,
  logging frameworks, etc.)
- ... develop software collaboratively through (a) the use of tools, systems,
  and best practices available to facilitate that collaboration (e.g.,
  version control systems, code reviews, task tracking, etc.), and (b)
  exercising collaborative skills (communication, giving/accepting feedback, etc.)

We trust that you are excited to learn all this and, to that end, we
have designed coursework and policies that will support your learning.

Most notably, because software is often developed in teams, the course
project will involve working in teams of 4-5 students (with teams often
having to collaborate across teams). Similarly, you will have a lot of
latitude to use external resources, including AI tools, because software
developers often depend on these resources/tools to do their job.

That said, there will be situations where we may ask you to limit
your reliance on other resources, because it will be important for
you to first learn a new skill on your own. This will be particularly
important in the homeworks, which must be completed individually.

To that end, this document provides guidance on what activities are
allowed because they will benefit your learning, and which ones will not
be allowed because they will be detrimental to your learning (and, in
some cases, even morally reprehensible). As you read through the rest of
this document, we encourage you to reflect on how your actions in this
course will contribute to your learning, instead of treating these
guidelines as rules to follow “just because the professor said so”.

What is Allowed
---------------

This section describes a number of activities that we allow in this
class, because they align with the learning objectives of this class.
When reading through them, take into account that some of them come with
caveats, and may require providing some sort of citation in your code.

Acceptable Forms of Collaboration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Course Project**

In the course project, all students will work on the same code
repository, which means everyone will be able to see each other's
code. As such, there are no academic integrity concerns with
showing or discussing the project code with other students
in the class.

You are also allowed to collaborate with other students on any
given task, including working on the same code together, but you must
always disclose what students worked on that task (there will be
a specific mechanism for doing this in the course project)

**Homework**

In the homeworks, you will be practicing new skills that are taught
in this class. As such, to make sure you gain sufficient practice
on these topics before relying on other resources, we require you
to complete the homeworks individually, without collaborating
with other students.

That said, you *are* allowed to have *high-level* discussions with other
students in the class, as long as you don’t discuss implementation
details or share any code (except when discussing code we provide to
you). For example, the following would be acceptable questions to ask
other students in the class:

-  *“I am unclear on how to add a new view to a Django project.
   Can we walk through an example together?”*
-  *“I am not sure how the homework web application is supposed to behave
   in this particular page. Do you know what it is supposed to do?”*
-  *“I’m still getting the hang of using virtual environments;
   Do I need to activate it every time I use it?”*

Don’t forget that the course staff are also happy to answer these kinds
of questions on Slack or at office hours. That said, if you do
have these kinds of high-level discussions with a classmate, you must
list their name(s) at the top of any relevant homework files.

Acceptable Uses of Generative AI
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Generative AI (GenAI) tools are becoming an increasingly common part of
a software developer’s toolkit, but you should remember that they are
ultimately just *productivity tools*. They are meant to facilitate and
speed up your work, not replace it entirely.

When talking with developers in industry, we have consistently heard
that these tools are most useful for routine or boilerplate tasks, where
they can significantly speed up work. Even then, developers stress the
importance of carefully reviewing the generated code to catch bugs or
issues that could arise later. A common caveat is that over-reliance on
these tools often results in errors creeping into a codebase, because
developers become too complacent with the GenAI’s output. Thus, many
developers avoid using generative AI for large or complex tasks, where
it’s beneficial for them to think through each line of code.

In this class, you are assumed to have two quarters worth of
programming experience (141 and 142). We assume your programming
foundations are fairly solid,
and that you have reached a point where certain aspects of programming
may start to feel routine and mechanical. We will allow you to use
Generative AI to deal with these kinds of tasks, but not with more
complex tasks.

More specifically, you are allowed to use GenAI tools in the following ways:

-  You can use autocomplete tools like Github Copilot to complete
   individual lines of code, as long as you understand exactly what that
   line of code is producing. You should exercise caution when
   repeatedly using this functionality (i.e., generating several lines
   one after the other)
-  You can use prompt-based tools to generate the code for small utility
   functions, or small self-contained blocks of code.
-  You can take a piece of code we’ve provided to you, and ask a GenAI
   questions about that code.
-  You can provide a piece of code you’ve written to a prompt-based
   tool, and ask for feedback or for help with refactoring or
   documenting that code.
-  When writing testing code, you must design the tests yourself,
   but can rely on GenAI to generate the actual implementation of the test.

You are also broadly allowed to use GenAI tools for reference purposes,
such as asking GenAI to explain how to perform certain tasks in Python
or Django (e.g., “How can I validate an e-mail address in a Django web application?”), or
to explain a concept from class in more detail (e.g., “In class, we’ve
focused mostly on web applications with Django. Given that I am mostly
familiar with Python, can you give me a brief summary of how mobile
development differs from web development?”).

**Important caveats about Generative AI**

-  Don’t forget that GenAI systems **have no sense of what is true or
   not**, and will sometimes produce plausible-looking code that contains
   errors, or which may cause issues in the context of the codebase that
   code is being used in. **Always double-check any code produced by
   GenAI**, and make sure that you understand what it does exactly.
-  Even when producing correct code, that code could contradict
   instructions/guidance we provide in this class. It is important that
   you always look at answers from GenAI with a critical eye, and that
   you remember that the content we provide in the class always takes
   precedence.
-  Along these lines, there will be situations where will ask you
   to work on a task by yourself without any assistance from GenAI, because
   we feel you will learn more effectively that way. This will often be
   the case in the homeworks, where it is important that you learn
   the new skills you are applying in that homework, without relying
   on AI tools.

**Citation Requirements**

You do not need to include citations for using autocomplete-based tools
(like GitHub Copilot) unless you used them to generate an entire function/method,
or a substantial block of code. In that case, you must include a docstring
or comment stating that the code was generated with an AI tool (naming the tool
involved)

Please note that, if the autocomplete-based tool generated some code that you
then edited heavily to ensure it worked correctly, you are not required to
include a citation.

You must provide a citation for any code generated by a prompt-based tool
(like ChatGPT or PhoenixAI). If you used these tools to produce a first
draft of the code, which you then modified further, make sure to state
this in the citation. If possible, you should include a link to the
exact conversation with the AI tool. The citation can be included in a
docstring (if it affects just one function/method) or as a comment at the
top of the file.

Acceptable Uses of Other External Resources
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Software developers often rely on many external resources, including
websites like Stack Overflow, that can help them better understand how
to complete a certain task. You are allowed to use these external
resources, with the following caveats:

-  You must provide a citation for that external resource. If it
   affected a specific portion of your code, include a code comment with
   a link to that resource. If you consulted it more broadly, include it
   in the project’s documentation.
-  Reference documentation, as well as Stack Overflow posts, often
   include short snippets of sample code. Exercise caution when relying
   on these snippets of code. Using 2-3 lines of example code is
   typically not problematic, but longer pieces of code could result in
   your work being flagged as plagiarized (e.g., if other students
   relied on that same external resource). Make sure to always include a
   citation in these cases.

Software developers also often rely on third-party libraries to
perform routine tasks, so they can focus on the primary purpose of the
code they are writing. In the course project and homeworks,
you can always use the Python Standard Library and the Django library.
If you consult their official documentation, you do not need to
provide any citations.

If there are other libraries you would like to use, please ask us first. We
will generally be fine with any library that does not provide
any functionality we are asking you to implement yourself.

What is Not Allowed
-------------------

While certain forms of collaboration and uses of Generative AI and
external resources can supplement your learning, an over-reliance on
them can be detrimental to your learning, because they prevent you from
practicing and building the skills you should be taking away from this
class.

As such, we have to draw some lines in the sand:

**Course Project**

Although you have a lot of latitude to collaborate with other students
in the class, you must never take credit for work that someone else in
the class did. Please note that there are many situations
where students will legitimately *share* credit for a piece of work;
what would be unacceptable would be to falsely take sole credit for work you did not do,
as a way to improve your score in the class.

Additionally, you are not allowed to collaborate with anyone **outside** of
the class. All your collaboration must be limited to students in the class.

**Homeworks**

Because the homeworks must be completed individually, you must be more
careful about your reliance on other resources:

-  Remember that you can only have high-level
   discussions with other students about the homeworks.
-  Most of the homeworks will require that you limit your use of AI tools.
   You must make sure to follow those requirements carefully.
-  In general, you *must not* rely on any sources that provide a complete
   (or nearly complete) solution to a given task, regardless of whether
   you provide a citation for that source.

Additionally, until the quarter is over, you must **not post your
code in publicly-accessible websites**, e.g., pastebin, a public GitHub
repository, GitHub gists, etc. At the end of the quarter, we will
provide more guidance on how you can make your code publicly available
as part of a coding portfolio.

Academic Integrity Offenses
---------------------------

If you run afoul of the above guidance, particularly if you actively
plagiarize someone else’s homework code, your code could be flagged as an
academic integrity offense. We take these incidents very seriously in
this class, and will escalate any such cases to the `Office of College
Community
Standards <https://college.uchicago.edu/student-services/office-college-community-standards>`__
for further adjudication. Going through disciplinary proceedings is an
unpleasant experience for everyone involved, and the outcome of these
cases can have an impact on your grade. At minimum, your final course
grade will drop one full step (letter). At maximum, you will receive an
F in the course.

We realize that sometimes students commit plagiarism out of desperation
and as a measure of last resort. If you are in this situation, please
just ask the instructors or other course staff for help. If you are
having a hard time in the class, we will provide as much assistance as
we can. Plus, a poor performance in one assignment is unlikely to wreck
your grade for the class. Plagiarism is never worth it.
