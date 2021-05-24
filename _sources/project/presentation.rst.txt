Final Presentations
===================

The final component of this course will be a series of final
presentations, where each team will present the work they have done
throughout the quarter. This presentation will be divided into two
components:

-  A pre-recorded presentation due **Thursday, June 3rd at 8pm CDT**
-  A 5-10 minute Q&A session with the instructor and TAs during the
   “final exam” slot for the class on **Friday, June 4th, 4pm-6pm CDT**

Once all presentations have been submitted, they will be shared with the
entire class, so that everyone in the class can learn about the work
that all the teams have done (similar to how, in live presentations, you
would be able to attend the presentations for all the teams).

Presentation Contents
---------------------

Each presentation must be divided into three portions: a high-level
discussion of how you designed and implemented your component, a demo,
and reflections.

Design and Implementation
~~~~~~~~~~~~~~~~~~~~~~~~~

You must explain, at a high-level, the design of your component, and any
non-trivial implementation details (like the use of external libraries).
You should also take care to explain the main dependencies your code has
with the rest of chiventure.

Please note that you should not need to show any of your code during
your presentation: you should instead focus on describing at a high level
the features you added or improved in chiventure, including any modules, data
structures, etc. you implemented. That said, it can be
appropriate to show very short examples (3-4 lines) of how your code
might be called from other components.

Demo
~~~~

You must run a demo of your work meeting the following requirements:

-  You must show a program in execution.
-  The code you run *must* be in the ``dev`` branch of the repository.
   You cannot demo code that is still in one of your branches and has
   not gone through a code review.

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

Presentation Format
-------------------

We do not expect your recorded presentation to be super-polished, with
fancy editing, etc. Instead, we suggest you approach this in a manner
similar to an in-person presentation: develop your slides and demo
collaboratively, and then deliver your presentation using no more than
15 minutes, but do so over Zoom (with one of you recording the meeting).

To reiterate: please do not spend time doing multiple retakes, editing
your video (beyond trimming the start and end of the video), etc. If you
would like to ensure that your presentation is minimally polished, we
instead suggest you do the following:

1. Do a very brief dry run (2-3 minutes) with one or two other team
   members, where one of you is sharing their screen, etc. to verify
   that you understand how to run the Zoom meeting and record it. We
   suggest you follow the steps for creating a `local recording in
   Zoom <https://support.zoom.us/hc/en-us/articles/201362473>`__, and
   that you have everyone in the meeting say something to verify that
   they are being correctly recorded. *You should do this well in
   advance of the deadline* so we can sort out any technical issues
   beforehand.
2. Allocate 15 minutes to deliver your presentation, and ask students in
   other teams whether they would be willing to attend the meeting. This
   will make your presentation less awkward, because you’ll actually be
   presenting to other people, and you will feel more obligated to stay
   within the 15 minute limit (as opposed to getting into a “let’s do a
   retake” mentality). Plus, the people from the other teams may give
   you some valuable feedback at the end of the meeting (and will
   themselves benefit from seeing how another team approaches giving a
   presentation; you should also volunteer to attend other presentations
   precisely for this reason!)
3. If feasible, deliver the presentation again at a later time,
   incorporating the feedback you received from the other students.

All that said, you are allowed to record your presentation in other ways
if you feel that will work better for you. However, if you’ve never
prepared a pre-recorded presentation before, we suggest you use Zoom as
described above.

We suggest you allocate roughly 5 minutes for each portion of the
presentation. Please note that the design/implementation and demo
portions can be interwoven together, as opposed to treating them as
completely distinct portions.

Take into account that the presentation itself doesn’t have to be
delivered by all team members. In fact, for a 15 minute presentation,
you probably want no more than 2-3 people speaking in total. If you feel
comfortable doing so, please make sure your camera is turned on when you
speak during the presentation.

Submission Instructions
-----------------------

You will submit your presentation through Panopto. On the CMSC 22000 canvas
site, go to "Panopto Video", and then into the folder "Final Presentations [Submission Folder]".
To upload your video, click on the "Create" button (which appears to the right
of the search bar), and select "Upload media". You will then be prompted
to upload a file. Please make sure the video file includes the name of
your team in it.

Please note that this submission folder is set up so that only the person
who uploads a video can see that video. Your teammates should not be alarmed
if they go to this folder and do not see your team's video there.



Q&A
---

During the Q&A meeting, each team will get approximately 10 minutes for:

1. A **brief** (less than 5 minutes) summary/demo of your team's work.
2. Q&A by the instructor/TAs.

The summary/demo *will not be graded*. The audience of this summary/demo
is not the instructor/TAs (who will have already watched your pre-recorded
presentation), but rather the other teams (who have not watched your
pre-recorded presentation). This will be a chance for everyone in the class
to hear more about what every team did this quarter.

Please note that we will be on a tight schedule during the Q&A meeting so,
if you are going to use slides or demo any running code, your presentation
or demo must be ready to go the moment your team's turn is up.

In the Q&A portion, you will be asked some questions based on your
pre-recorded presentation. While the entire team does not have to be
present for this Q&A, as many team members as possible should plan to
attend. Take into account that you may be asked questions that one or
two specific people in your team are best suited to answer
(because they were more involved in the part of your code that a
question relates to).

Teams in a non-North American timezone who are unable to send a few team
members to the Q&A meeting should contact the instructor in advance to
schedule an alternate time for their Q&A.

Scoring
-------

The presentation will be worth 10 points of your final grade, broken
down as follows:

-  5 points for content/structure of the presentation
-  3 points for the demo
-  2 points for the Q&A

The instructor/TAs will use the following rubric, with discretion to
add/subtract half a point.

Content and structure
~~~~~~~~~~~~~~~~~~~~~

-  5 points: Perfectly structured, clear from beginning to end
-  4 points: Overall well structured. Only a few minor hiccups and/or
   aspects that were not entirely clear.
-  2.5 points: Needs improvement. Presentation was poorly structured
   with multiple aspects that were not clear.
-  1 point: Poorly structured. Presentation does not substantially
   address the content we requested.
-  0: No presentation was delivered.

For avoidance of doubt, this score is based solely on the content and
structure of the presentation, and whether it addresses all the
requirements described earlier. Producing a slick video with fancy
editing (or not) has no bearing on this score.

.. _demo-1:

Demo
~~~~

-  3 points: Flawless demo that highlights the team’s work.
-  2 points: Smooth demo with only a few small hiccups.
-  1.5 points: Needs improvement. Demo worked but with major issues.
-  1 point: Very incomplete demo. Demo hints at the work the team did,
   but doesn’t directly showcase their work.
-  0: No demo was done.

.. _qa-1:

Q&A
~~~

-  2 points: All questions were answered
-  1.5 points: Most questions were answered, but the team was stumped on
   some of them.
-  1 points: The team was stumped on most of the questions they were
   asked.
-  0.5 point: The team was stumped on all questions.
-  0 points: The team did not answer any of the questions they were
   asked.

Code Freezes
------------

Please note that, leading up to the final presentations, there will
be two freezes on the ``dev`` branch. Remember that your demo **must**
run code that is in the ``dev`` branch.

- **Soft Freeze**: Friday, May 28th at 11:59pm CDT

  - Only issues/PRs that are open at this time will be reviewed and graded.
  - Issues/PRs can still be opened after the soft freeze (under a new milestone, “2021/Wrap-up”) but they will not be graded.
  - We cannot guarantee that PRs opened after the soft freeze will be reviewed/merged.
  - In general, we will not approve PRs that introduce a completely new feature, or that modify the core data structures of chiventure.

- **Code Freeze**: Wednesday, June 2nd at 8pm CDT

  - No code will be merged after this time.
  - Exceptions may be made for very minor bugfixes and documentation updates, but we cannot guarantee they will be reviewed in a timely fashion.

