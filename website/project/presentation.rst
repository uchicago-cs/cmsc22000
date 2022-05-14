Final Report and Demo
=====================

The final component of this course will be a final report, where each
team will summarize the work they have done throughout the quarter,
as well as a live demo during the "final exam" slot for the class
(Wednesday, June 1st, 10am-12pm).

Final Report
------------

The report will be divided into three portions: a high-level
discussion of how you designed and implemented your feature,
a list of possible next steps in your feature,
and a series of reflections.

Design and Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~

You must explain, at a high-level, the design of your component, and any
non-trivial implementation details (like the use of external libraries).
You should also take care to explain the main dependencies your code has
with the rest of chiventure.

Please note that this section of the report should **not** be a comprehensive description
of every single file and function of your code. Instead, you should focus
on describing **at a high level** the features you added or improved in chiventure,
including any modules, data structures, etc. you implemented.

A good way
to think about this section is to imagine that it will be read
by students in following years who will continue working on
your feature. When writing this part of the report, ask yourself what information
would be useful to future students, and assume that they have
the technical skills to read through the code and fill in
all the lower-level details of your work (but that they
need a good sense of the "big picture" before doing so).

For example, if you added a new data structure called
``foo_t``, it would be appropriate to mention that you
did so, and to describe the purpose of that data structure,
as well as any dependencies related to that data structure.
On the other hand, you would not include the full declaration
of that data structure, nor would you describe each individual
field. Instead, the goal is to convey that ``foo_t`` is a data
structure relevant to your feature, and that anyone working
on that feature in the future will need to familiarize themselves
in it (and the assumption is that those students will just look
at the code to learn more about the specifics of that data structure).

Along those lines, you should not need to include any code
in this section of the report, although it can be
appropriate to show very short examples (3-4 lines) of how your code
might be called from other components.

There is no specific length requirement for this section, but we
expect any sufficiently-detailed section to be around 800-1200 words long.

Next Steps
~~~~~~~~~~

Again, imagine that this report will be read by students who will
continue your work in following years. Describe at lest four
tasks that those students could work on to continue the work
you did this quarter. These can include the following

- Tasks that you started working on this quarter, but were unable
  to finish.
- Improvements or fixes you identified this quarter, but did
  not work on.
- General interesting directions that the feature could go in.

Please note that you can complete this section of the report
by simply pointing to specific GitHub issues (particularly Backlog issues)
that future students may want to focus on. If you do so, make sure
to include the issue number and issue title for each issue, along with
a 2-3 sentence summary of the issue.


Reflections
~~~~~~~~~~~

You must discuss at least three (and no more than five) aspects of the
software development process which you found challenging and/or
rewarding. We encourage you to decouple these as much as possible from
the structure of this particular class. In other words, reflect upon
what aspects of developing software as part of a team (and with other
teams), and using the tools that facilitate this process (GitHub, Slack, etc.)
proved to be more challenging (and/or rewarding) than
simply working individually.

You must also discuss at least one thing that you would’ve done
differently with the benefit of hindsight.

Live Demo
---------

During the final exam slot for the class, you must run a demo of your
work meeting the following requirements:

- You must show a program in execution.
- The program *must* use code you have written this quarter.
- The code you run *must* be in the ``dev`` branch of the repository.
  You cannot demo code that is still in one of your branches and has
  not gone through a code review.
- To ensure there is enough time for all the teams to showcase their
  work, your demo should be around 5 minutes long, and never more
  than 10 minutes long.

We recommend that you think carefully about what you want to show
in your demo, and that you plan ahead of time the exact steps you
will take during the demo (as opposed to doing a more improvised demo).

Ideally, you should run the main ``chiventure`` executable, in a way
that highlights the work you’ve done. However, if your feature is not
yet accessible from the main executable, you are allowed to create an
example program inside the ``examples/`` directory of your feature.

Please note that this is not “sandbox” code: this should be code that
integrates, as much as possible, with the rest of chiventure. A good way
to think about this is to write an example program that showcases the
work you were able to do, and that future developers can look at as an
example of how your code works.

Finally, time-permitting, we may ask you questions after your demo,
but your answers to these questions will not factor into your score.


Submission Instructions
-----------------------

As in the project design warm-up, your team will get a repository
shared by everyone in the team, and you must upload your report
to this repository. We will provide a simple Markdown template
for the report, but you are also welcome to use other formats
as long as they are text-based (e.g., plain text or HTML are fine;
PDF, Word, etc. are not acceptable)



Scoring
-------

Since you only have one shot at the report and demo, the scoring
is largely based on the completeness of your final report and demo.
i.e., we will be paying more attention to whether you put in a
good-faith effort to provide the information requested in the report, regardless of
whether there is room for improvement in the report's style,
level of detail, etc. Similarly, we will be looking at whether
you actually wrote a demo that meets the requirements listed above,
regardless of whether the demo could've showcased more aspects
of your work, etc.

The following issues will have an effect on your score in the
final report and demo:

- Not completing any of the sections in the report, or not
  providing the information requested for those sections.
- Writing an excessively informal Design and Implementation
  section (e.g., just providing a series of bullet points)
- Not doing a live demo at all
- Doing a live demo that does not fulfill the requirements listed
  for the live demo.

TODO: More concrete specs?


Code Freezes
------------

Please note that, leading up to the demos, there will
be two freezes on the ``dev`` branch. Remember that your demo **must**
run code that is in the ``dev`` branch.

- **Soft Freeze**: Friday, May 27th at 11:59pm CDT

  - Only issues/PRs that are open at this time will be reviewed and graded.
  - Issues/PRs can still be opened after the soft freeze (under a new milestone, “2022/Wrap-up”) but they will not be graded.
  - We cannot guarantee that PRs opened after the soft freeze will be reviewed/merged.
  - In general, we will not approve PRs that introduce a completely new feature, or that modify the core data structures of chiventure.

- **Code Freeze**: Tuesday, May 31st at 8pm CDT

  - No code will be merged after this time.
  - Exceptions may be made for very minor bugfixes and documentation updates, but we cannot guarantee they will be reviewed in a timely fashion.

