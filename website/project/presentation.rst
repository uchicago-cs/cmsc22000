Final Report and Demo
=====================

The final component of this course will be a final report, where each
team will summarize the work they have done throughout the quarter,
as well as a live demo during the "final exam" slot for the class
(Wednesday, December 6th, 12:30pm-2:30pm).

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
with the rest of ChiGame.

Please note that this section of the report should **not** be a comprehensive description
of every single file and function of your code. Instead, you should focus
on describing **at a high level** the features you added or improved in ChiGame,
including any models, views, etc. you implemented.

A good way
to think about this section is to imagine that it will be read
by students in following years who will continue working on
your feature. When writing this part of the report, ask yourself what information
would be useful to future students, and assume that they have
the technical skills to read through the code and fill in
all the lower-level details of your work (but that they
need a good sense of the "big picture" before doing so).

Along those lines, you should not need to include any code
in this section of the report, although it can be
appropriate to show the code for any models you have added,
as well as very short examples (3-4 lines) of how your code
might be called from other components. It is also appropriate
to link to specific parts of the ChiGame code.

There is no specific length requirement for this section, but we
expect any sufficiently-detailed section to be around 800-1200 words long.

Next Steps
~~~~~~~~~~

Again, imagine that this report will be read by students who will
continue your work in following years. Describe at least four
tasks that those students could work on to continue the work
you did this quarter. These can include the following:

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

- In most cases, you must run the ChiGame website on your computer.
  In some components (particularly the more experimental ones),
  where there is no expectation that your code
  will be fully integrated with ChiGame by the end of the quarter,
  it is acceptable to show run those components by themselves (and
  not as part of the ChiGame website)..
- Your demo must involve running code you have written this quarter,
  and that code *must* be in the ``dev`` branch of the repository.
  You cannot demo code that is still in one of your branches and has
  not gone through a code review. Note: The code doesn’t necessarily
  have to be in the head of the ``dev`` branch. If someone breaks
  your code in ``dev``, you can “rewind” to a previous commit in ``dev``
  if you prefer.
- To ensure there is enough time for all the teams to showcase their
  work, your demo should be no more than ~15 minutes long.

We recommend that you think carefully about what you want to show
in your demo, and that you plan ahead of time the exact steps you
will take during the demo (as opposed to doing a more improvised demo).

Finally, please note that we may ask you questions after your demo,
but your answers to these questions will not factor into your score.

Live Demo Tips
~~~~~~~~~~~~~~

Doing a live demo may feel like a daunting task, particularly
because of the stress of something going wrong during the demo.
Here are a few tips on preparing/delivering the demo that
may be helpful:

- Make sure you carefully plan what you're going to say and
  show at the demo, and rehearse it carefully. A live demo
  is not something you want to improvise on-the-fly.
- When it's your time to demo, you should use a single laptop,
  and that laptop must be ready to show the demo right away.
  i.e., you must have a terminal open
  that is ready to run your demo, and you should need to do
  no setup other than connecting your laptop to the projector.
- If you're unsure whether your laptop will work with the projector,
  get to the room before 12:30pm and do a quick test.
- Always have a contingency plan. Sometimes demos don't work and,
  while that is not ideal, you will not cause a bad impression
  if you fall back on a contingency plan. For example, you could have
  screenshots ready to show if the demo doesn't work (note:
  if that happens, we may ask you to show us the demo at a later
  time so we can verify that it works)
- If something does fail, do not try to fix it on the spot. Move on
  with the rest of the demo and, if that is not possible, give up
  on the demo gracefully (ideally by switching to your contingency plan)


Submission Instructions
-----------------------

You will be uploading your report to the same repository you used for the
project warm-up exercises. We will provide a simple Markdown template
for the report, but you are also welcome to use other formats
as long as they are text-based (e.g., plain text or HTML are fine;
PDF, Word, etc. are not acceptable)


Scoring
-------

You will receive a single ESNU score for the final report
and demo (i.e., not one score for each, but one score overall).
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
- Writing a clearly low-quality/low-effort report. In other words,
  you should worry less about whether you're writing an exceptional report
  (although doing so never hurts), and more about making sure
  you don't write a report that is too informal, not useful, etc.
  Examples of this could include:

  - Writing the Design and Implementation section as a list
    of bullet points.
  - Pervasive lack of complete sentences, or pervasive bad
    grammar.
  - Leaving TODOs or other notes in your report.

- Not doing a live demo at all
- Doing a live demo that does not fulfill the requirements listed
  for the live demo.

Note: Having your demo fail during the live demo will not necessarily
affect your score. If you are able to deal with that failure gracefully
(see the Live Demo Tips above), this will not affect your score.

Code Freezes
------------

Please note that, leading up to the demos, there will
be two freezes on the ``dev`` branch. Remember that your demo **must**
run code that is in the ``dev`` branch.

- **Soft Freeze**: Friday, December 1st at 11:59pm CST

  - Only issues/PRs that are open at this time will be reviewed and graded.
  - Issues/PRs can still be opened after the soft freeze (under a new milestone, “2023/Wrap-up”) but they will not be graded.
  - We cannot guarantee that PRs opened after the soft freeze will be reviewed/merged.
  - In general, we will not approve PRs that introduce a completely new feature, or that modify the core models of ChiGame.

- **Code Freeze**: Tuesday, December 5th at 5pm CST

  - No code will be merged after this time.
  - Exceptions may be made for very minor bugfixes and documentation updates, but we cannot guarantee they will be reviewed in a timely fashion.
