# Final Presentations

The final component of this course will be a series of final presentations, where each team will present the work they have done throughout the quarter. This presentation will be divided into two components:

- A pre-recorded presentation that must be submitted by **Tuesday, June 9, at 12pm CDT**.
- A 5-10 minute Q&A session with the instructor and TAs during the "final exam" slot for the class: **Tuesday, June 9, from 4pm to 6pm CDT**

Once all presentations have been submitted, they will be shared with the entire class, so that other teams can learn about the work that other teams have done (similar to how, in live presentations, you would be able to attend the presentations for all the teams).

## Presentation Contents

Each presentation must be divided into three portions: a high-level discussion of how you designed and implemented your component, a demo, and reflections.

### Design and Implementation

You must explain, at a high-level, the design of your component, and any non-trivial implementation details (like the use of external libraries). You should also take care to explain the main dependencies your code has with the rest of chiventure.

### Demo

You must run a demo of your work meeting the following requirements:

- You must show a program in execution.
- The code you run *must* be in the `dev` branch of the repository. You cannot demo code that is still in one of your branches and has not gone through a code review.

Ideally, you should run the main `chiventure` executable, in a way that highlights the work you've done. However, if your feature is not yet accessible from the main executable, you are allowed to create an example program inside the `examples/` directory of your feature. 

Please note that this is not "sandbox" code: this should be code that integrates, as much as possible, with the rest of chiventure. A good way to think about this is to write an example program that showcases the work you were able to do, and that future developers can look at as an example of how your code works.

### Reflections

You must discuss at least three (and no more than five) aspects of the software development process which you found challenging and/or rewarding. We encourage you to decouple these as much as possible from the structure of this particular class. In other words, reflect upon what aspects of developing software as part of a team (and with other teams), and using the tools that facilitate this process (GitHub, Slack, Travis, etc.) proved to be more challenging (and/or rewarding) than simply working individually.

You must also discuss at least one thing that you would've done differently with the benefit of hindsight.

## Presentation Format

We do not expect your recorded presentation to be super-polished, with fancy editing, etc. Instead, we suggest you approach this in a manner similar to an in-person presentation: develop your slides and demo collaboratively, and then deliver your presentation using no more than 15 minutes, but do so over Zoom (with one of you recording the meeting).

To reiterate: please do not spend time doing multiple retakes, editing your video (beyond trimming the start and end of the video), etc. If you would like to ensure that your presentation is minimally polished, we instead suggest you do the following:

1. Do a very brief dry run (2-3 minutes) with one or two other team members, where one of you is sharing their screen, etc. to verify that you understand how to run the Zoom meeting and record it. We suggest you follow the steps for creating a [local recording in Zoom](https://support.zoom.us/hc/en-us/articles/201362473), and that you have everyone in the meeting say something to verify that they are being correctly recorded. *You should do this well in advance of the deadline* so we can sort out any technical issues beforehand.
2. Allocate 15 minutes to deliver your presentation, and ask students in other teams whether they would be willing to attend the meeting. This will make your presentation less awkward, because you'll actually be presenting to other people, and you will feel more obligated to stay within the 15 minute limit (as opposed to getting into a "let's do a retake" mentality). Plus, the people from the other teams may give you some valuable feedback at the end of the meeting (and will themselves benefit from seeing how another team approaches giving a presentation; you should also volunteer to attend other presentations precisely for this reason!)
3. If feasible, deliver the presentation again at a later time, incorporating the feedback you received from the other students.

All that said, you are allowed to record your presentation in other ways if you feel that will work better for you. However, if you've never prepared a pre-recorded presentation before, we suggest you use Zoom as described above.

We suggest you allocate roughly 5 minutes for each portion of the presentation. Please note that the design/implementation and demo portions can be interwoven together, as opposed to treating them as completely distinct portions.

Take into account that the presentation itself doesn't have to be delivered by all team members. In fact, for a 15 minute presentation, you probably want no more than 2-3 people speaking in total. If you feel comfortable doing so, please make sure your camera is turned on when you speak during the presentation. 

## Submission Instructions

Submission instructions will be posted closer to the deadline, but we expect you will be able to upload your video through Panopto.

## Q&A

During the Q&A meeting, you will be asked some questions based on your presentation (this is meant to emulate the Q&A that typically happens after a live presentation; the instructor and TAs will watch your presentation before the Q&A portion). We expect to spend 5-10 minutes per team.

While the entire team does not have to be present at the Q&A meeting, as many team members as possible should plan to attend. Take into account that you may be asked questions that one or two specific people in your team are best suited to answer (because they were more involved in the part of your code that a question relates to).

Teams in a non-North American timezone who are unable to send a few team members to the Q&A meeting should contact the instructor in advance to schedule an alternate time for their Q&A.

## Scoring

The presentation will be worth 10 points of your final grade, broken down as follows:
 
- 5 points for content/structure of the presentation
- 3 points for the demo
- 2 points for the Q&A
 
The instructor/TAs will use the following rubric, with discretion to add/subtract half a point.

### Content and structure

- 5 points: Perfectly structured, clear from beginning to end
- 4 points: Overall well structured. Only a few minor hiccups and/or aspects that were not entirely clear.
- 2.5 points: Needs improvement. Presentation was poorly structured with multiple aspects that were not clear.
- 1 point: Poorly structured. Presentation does not substantially address the content we requested.
- 0: No presentation was delivered.

For avoidance of doubt, this score is based solely on the content and structure of the presentation, and whether it addresses all the requirements described earlier. Producing a slick video with fancy editing (or not) has no bearing on this score.


### Demo

- 3 points: Flawless demo that highlights the team's work.
- 2 points: Smooth demo with only a few small hiccups.
- 1.5 points: Needs improvement. Demo worked but with major issues.
- 1 point: Very incomplete demo. Demo hints at the work the team did, but doesn't directly showcase their work.
- 0: No demo was done.

### Q&A

- 2 points: All questions were answered
- 1.5 points: Most questions were answered, but the team was stumped on some of them.
- 1 points: The team was stumped on most of the questions they were asked.
- 0.5 point: The team was stumped on all questions.
- 0 points: The team did not answer any of the questions they were asked.


## Presentation and demo tips

- You should declare the `dev` branch to be frozen at some point before the presentations (and after you have run through a successful demo with the code in that branch). We suggest aiming to freeze the `dev` branch at least 24 hours before the presentation, and only allowing changes that do not affect your code (e.g., documentation changes, READMEs, etc.) or, at most, very small hotfixes.
- When you have a limited amount of time, don't improvise your demo. Think about what you will show exactly, and stick to your script. Make sure to rehearse your demo thoroughly before you actually record it.


