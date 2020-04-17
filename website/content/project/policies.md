---
title: "Project Policies"
date: 2018-02-17T08:47:20-06:00
---

{{% toc %}}

# Project Organization 

In this project, you will be divided into teams of five students, and will work collaboratively (both within your team and between teams) on a complex software system, [chiventure]({{< ref "/project/chiventure.md" >}}), that will involve improving existing code as well as designing and implementing new functionality. You will be using several tools to support the collaborative aspects of this project and, indeed, your collaborative skills will be as important as your coding skills to be successful in this project. The project will follow an agile process that resembles (but does not exactly follow) [Scrum](https://en.wikipedia.org/wiki/Scrum_(software_development)).

Each team will be assigned to work on [an existing or new feature of chiventure]({{< ref "/project/features.md" >}}) (teams will have a chance to express a preference, although we can’t guarantee we’ll be able to assign each team to their preferred feature). In each team, a TA will act as Senior Developer.


# Project Timeline

The project will span seven weeks (Weeks 3 - 9), with a final review and team presentations taking place during Finals Week. The seven weeks of the project will be divided into a project kick-off and four sprints, with sprint reviews happening on Mondays.

*   Week 3: Project kick-off. This week will be primarily used for you to familiarize yourself with project and the exact work your team will do.
*   Week 4: Sprint 1
*   Week 5: Sprint 2. 
*   Weeks 6-7: Sprint 3
*   Weeks 8-9: Sprint 4


# Project Evaluation

The project is worth 70% of your final grade, and these 70 points are divided as follows:

*   5: Team Design Exercise
*   35: Your individual score on the project
*   15: Your team score (the average of all the individual scores on a team)
*   5: Peer feedback
*   10: Final presentation during Finals Week.

Unlike a traditional programming assignment or project, the exact final outcome of the project is not known in advance. Of course, we will set some high-level goals and requirements and, while those requirements will help us measure whether the project is “done”, they are not a strict rubric. As we saw in class, this is one of the strengths (and challenges) of agile software development: you can re-evaluate requirements and make design changes quickly, but there is no detailed requirements document that you can use to check whether you’ve contractually fulfilled your obligations to a customer.

As such, your individual score on the project will be based on how well you perform certain tasks that you will do throughout the project (and which you would encounter in any real software project). More specifically, you will be evaluated based on the following:

*   How well you document tasks/issues 
*   Whether you complete the tasks you commit to doing in a given sprint
*   Whether you get pull requests approved

Note: no part of your score will be determined by your teammates' reviews/feedback. So, when you receive a code review or peer feedback, we will be evaluating the quality of the code review / peer feedback itself; we will not be using that review/feedback to determine your score. Please note that, in peer feedback, we will specifically be evaluating the person giving the feedback (by looking at the quality of the feedback they provide).

Each of the above has a point value:

*   Adding tasks to the backlog: 5 points
*   Tasks/issues: 10 points
*   Getting a pull request approved: 20 points

We will discuss the "backlog" in class but, in essence, it is a list of pending tasks for the entire project.

Every time you do one of the above, you will be graded on a simple scale:

* "check plus plus": You earn 100% of the point value of the work you completed.
* "check plus": You earn 90% of the points.
* "check": You earn 85% of the points.
* "check minus": You earn 80% of the points.
* "check minus minus": You earn 75% of the points.

For example, suppose you have completed 3 tasks (graded “check”, “check”, and “check plus”) gotten a pull request approved (graded “check”) and added a task to the backlog (graded “check plus plus”). You will have accrued the following number of points:

$$ (0.85\cdot 10) + (0.85\cdot 10) + (0.9\cdot 10) + (0.85\cdot 20) + (1.0\cdot 5) = 8.5+8.5+9+17+5 = 48 $$


Your individual score (out of 100) is simply the following:


$$ \frac{\text{accrued points}}{\text{possible points}}\cdot 100 $$


In this example, your possible points would be 55 (the sum of the point value of each piece of work you did). So, your individual score would be 87.27%

The number of points you accrue can be affected in two ways:



* **Not completing a task you committed to doing.** At the start of each sprint, you will take ownership of certain tasks, and will be committing to doing them by the end of the sprint. If a task is assigned to a sprint, and then is either reassigned to a subsequent sprint or placed on the backlog, we will deduct 2 points from your score for that task. So, if your task receives a “check”, but it was late, you will accrue 6.5 points instead of 8.5.

  Please note that there is some flexibility regarding late tasks (see below). Also, take into account that this penalty does not apply to tasks beyond the ones you committed to doing (e.g., if you commit to doing two tasks, finish them earlier than expected, and there are other tasks you could claim, you could do them to potentially increase your score)
* **Too many cooks in the kitchen.** In some occasions, two or more people may agree to share responsibility for completing a task or for shepherding a pull request to master. This is normal and, when a task or pull request is shared by two or more students, then all of those students will accrue the points for that task (e.g., if two students collaborate on a task that receives a “check minus”, each student accrues 8 points out of a possible 10 points).

    However, when a task is shared by four or more students, the task will be worth 7 points (instead of 10). For example, if four students collaborate on a task, and the task receives a “check”, then all the students will accrue 5.95 points out of a possible 7 points (7·0.85 = 5.95).

As you will find out throughout the project, estimating the time a task will require can be challenging. You could commit to doing a task thinking it will only take 2-3 hours, and then find that it is actually a 10-15 hour task. So, you are allowed to do the following:



*   For tasks that you committed to doing, you are allowed to reassign up to four tasks to future sprints, or place them back on the backlog, without penalty. 
*   For any task, if you realize that it will take longer than you anticipated, you are allowed to close the task and spawn smaller tasks in its place. The closed task will then not contribute to your individual score. \

    Note: The rules are stricter for tasks you have committed to doing. You will need the senior developer’s approval to split such a task (we will likely approve most reasonable splits, but want to avoid anyone arbitrarily splitting a task into many microtasks just to rack up points). You will also not be allowed to split them after a certain point. In 1-week sprints, you cannot split tasks after Thursday. For 2-week sprints, you cannot split tasks after Monday of the second week of the sprint. When you split a task you committed to doing, you must commit to doing at least one of the subtasks; the remaining subtasks can go on the backlog (and you could commit to doing them in a subsequent sprint).


## Requirements for graded work


### Tasks/Issues

We will be using GitHub Issues to keep track of tasks in each sprint. At the team meeting at the start of a sprint, each team member must open a GitHub issue for each task they commit to doing. An issue must include the following:

* A descriptive title
* A descriptive summary
* Updates on the progress of the task
* A closing statement

We describe these in more detail below:

#### A descriptive title

The title should be a single sentence summarizing what will be done in this task.

For example: 

1. “Design and implement a ‘circle’ module”
2. “Add support for higher-dimensional points”
3. “Research libraries for drawing simple geometric shapes”
4. “Fix bug in segment intersection when segments overlap perfectly”

We will be referring back to the above four tasks in other examples, and we will refer to them as “Task #1”, “Task #2”, etc.

For example, here are less-descriptive titles for the above four tasks:

*   Task #1: “Work on circle module” (what work is being done on the module?)
*   Task #2: “Higher-dimensional points” (not a complete sentence, not clear what you’ll be doing)
*   Task #3: “We need drawing libraries” (that’s true, but what is being done about it in this task?)
*   Task #4: “Fix bug” (what bug is being fixed?)


#### A descriptive summary

A descriptive summary of what the task involves. One thing that must be clear from this summary is how you will know whether the task is done. Sometimes this is self-explanatory (e.g., if you are fixing a bug, the task is done when the bug is fixed), but in other cases you should avoid being too open-ended (e.g., when would you know whether you’re done “researching libraries”?) It can also be useful to provide context for why this task has been created.

When a task refers to a bug, the summary should include concrete instructions for reproducing the bug, including the full and unabridged output of the steps that lead to the bug manifesting itself.

Here are some examples of descriptive summaries:

**Task #1**


> libgeometry currently lacks a way to work with circles. We need to design and implement a module that supports, at least, creating circles, computing their area and diameter, and computing intersections between circles.


**Task  #2**


> libgeometry only supports points in two-dimensional space. We should generalize this design to support points in any dimensions, by having the `point_t` type look like this: 
> 
> ```
> typedef struct {
>    double *vals;
>    unsigned int ndims;
>} point_t;
> ```
> 
> The segment and polygon modules will need to be updated to use this new type, and their tests will need to be updated. We also need to add additional tests for segments and polygons in, at least, three-dimensional space.


**Task #3**

> We would like to eventually be able to visualize points, segments, and polygons. Before doing this, we should pick a library that easily allows us to do this. We should find at least three alternatives, and then discuss which one we prefer. If you would like to suggest a library, please make sure to include a link to their documentation, as well as (if possible) a link to code samples for that library.

**Task #4**


> Computing the intersection of identical segments makes `segment_intersects` crash. You can reproduce this by running this program:
>
> ```
> #include "segment.h"
> 
> int main()
> {
>     segment_t s1, s2;
>     point_t p1, p2;
> 
>     point_init(&p1, 2.0, 3.0);
>     point_init(&p2, 5.0, 7.0);
> 
>     segment_init(&s1, &p1, &p2);
>     segment_init(&s2, &p1, &p2);
> 
>     segment_intersects(&s1, &s2);
> }
> ```
> 
> This program immediately segfaults without any other output.

And here are example of summaries that would be less helpful:

**Task #1**


> I’m going to add a circle module

It’s not clear why we’re doing this, or how we’ll know when this task is done.

**Task  #2**

> Turn x, y in point_t to an array. Make sure it doesn’t break any other code.

While this describes what will be done in the task and how we’ll know when it’s done (when any code we break by the update to point_t is fixed), this needs to be more concrete.


**Task #3**

> Ok, so maybe we want to actually draw the points and segments and polygons at some point??? (lol point) Are? There? Libraries? For? This? Maybe someone can look them up? 🤔

Task descriptions should be concise and to the point. Jokes and colorful writing styles can distract from this.

**Task #4**

> If I create two identical segments and check if they intersect, my program crashes.

While this provides some indication of what needs to happen for the bug to manifest itself, the summary should provide concise instructions on how to reproduce the issue. At the very least, the code for the crashing program should be included in the task description.


#### Updates on the progress of the task

If you make any intermediate progress before finishing the task, specially if you have pushed any code related to this task, then it should be documented on the GitHub issue. For example:



*   In Task #1, suppose you implement a struct to represent circles, as well as the new/init/free functions, but have not yet started working on area, perimeter, and intersection. You could commit and push that code, and post a comment in the issue.
*   In Task #3, you could post a comment every time you finish reviewing an individual library (instead of just posting everything together at the end)

Pro tip: If you include an issue number in a commit message, then it will appear automatically in that issue, which will make it easier to keep track of what commits are associated with a given issue.

Note: Some tasks may simply not lend themselves to reporting any intermediate progress, in which case the closing statement (described next) would be enough.


#### A closing statement

When a task is done, you should close the corresponding GitHub issue, and you should include a comment explaining why this task is done. In some cases, this is as simple as stating that the work has been done. For example, in Task #1 you could simply state “Implemented the circle module, including the area, perimeter, and intersection functions”.

This may seem redundant, but take into account that closing an issue may not necessarily mean that the task is done. For example, the following could also be valid closing statements for Task #1:



*   “We ultimately decided we don’t need a circle module after all. I’m closing this issue, but will reopen if we decide to revisit this”
*   “The circle module has been implemented, except for the intersection function, which turned out to be more complex than anticipated. I am closing this issue, and have created a separate task (#5) for implementing circle intersections”


### Pull Requests

Like in many software projects, the `master` branch of our Git repository should only contain stable code that compiles, runs, and passes all tests. This is enforced by making the master branch a _protected_ branch, meaning that only the instructors and TAs have the ability to directly push to that branch. 

On top of that, there is an additional `dev` (short for "development") branch that acts as a "pre-master" branch. The `dev` branch is also protected, and should only contain stable code, but it is used as a staging area to integrate code (and uncover potential integration issues) before publishing code to `master`.

This means that, to get code into chiventure, you must make pull request to get code merged into the `dev` branch (and the instructor and TAs will decide when to merge that code into `master`).

Because the `dev` branch should contain stable code, pull requests to master must be carefully reviewed before they are approved. If you want to merge code into `dev`, your code must be reviewed by (1) someone in your team and (2) your senior developer. When your code affects code owned by another team, you must have an additional reviewer from each team who's code is affected.

A pull request should contain a relatively self-contained piece of work.  In fact, it is not uncommon for a task (or, at most, 2-3 tasks) to result in a pull request. We encourage you to touch base with your senior developer before creating your first pull requests, to determine whether the work you want to merge merits a pull request (or, similarly, whether it needs to be broken up into multiple pull requests).

Like a task, a pull request should have a descriptive title, a descriptive summary, updates on the progress of the pull request (especially since changes may need to be done based on the code reviews), and a closing statement. The assignees for the pull request must be everyone who contributed to the code that is being merged. If a pull request is approved, all assignees and reviewers will receive the points for that pull request.

Take into account that the final outcome of a pull request could be for that pull request to be denied. If this happens, it will not impact your score (but you will also not receive points for that pull request).


### Peer feedback

Twice throughout the project, each student will provide feedback to two other students in their same team. This is similar to a peer evaluation/review (which are fairly common in large software projects), except the feedback you provide will have no effect on the recipient's grade (whereas in a real project, these evaluations/reviews could affect whether you get a raise, a promotion, etc.). Instead, we will be assessing the feedback you provide to others.

At the end of Sprints 2 and 3, you will be assigned two peers who will be providing you with feedback (you will know each other's identities). Before they provide you with feedback, you must think about what you would like to receive feedback on. At the end of Sprint 2, you should think about the following: 

> *What is something I'd like to improve or do better in the next sprints?*

After Sprint 3 (i.e., during the final Sprint 4), you should think about the following:

> *What is something I'd like to improve or do better the next time I work in a complex software project and/or the next time I work in a team?*

Based on this, you should prepare prompts for specific feedback, which can range from organizational/teamwork aspects (e.g., wanting to improve how you communicate with the rest of the team) to technical aspects (e.g., wanting to improve your understanding of some programming concepts), as well as from concrete to high-level. You are also welcome to provide additional prompts that don't originate from the above questions. Once you have your prompt(s), you should convey them to the students who will be providing you with feedback (you can communicate this directly to them, via Slack, e-mail, etc.; you do not need to include the instructor or TAs in this communication)

For example, you could provide prompts like the following (the first two are examples of relatively high-level prompts, while the latter three are more specific):

1. I feel like I'm using Slack and GitHub effectively, but I wonder if there are any ways in which I could be using them more effectively.
2. I always procrastinate on my tasks until the 1-2 days before they are due, and I'd like to make more steady progress throughout the sprint. Do you have any suggestions on how I could do this?
3. Sometimes I feel like I go off and work on one of my tasks, and when I touch base with everyone else after a few days, some of the work I've done turns out to be headed in the wrong direction, and it seems like that could've been avoided if I had known what everyone else was doing. How could I make sure I stay informed of everyone else's progress?
4. I feel like I sometimes derail conversations by getting too lost in the weeds when talking about my work, even though I may have a valuable point to make. Do you also feel like I'm doing this? If so, what other ways do you think I could make this point instead of the way I'm doing it now?
5. I know we create tasks at the start of each sprint, and I know which ones I'm going to be working on but, if I'm working with other people on the task, sometimes I'm not sure what exactly I should be working on. How can I make sure this doesn't happen?
 
After you convey these prompts to the students who will be giving you feedback, they must convey that feedback to you. Please give your feedback givers at least one day to think about your prompts; after that, we encourage you to meet synchronously via Zoom (ideally with both the feedback givers at the same time) to discuss your feedback (if synchronously is hard to arrange, they can also convey their feedback over Slack, e-mail, etc.)

In the end, you must write a brief report (at least 3-4 paragraphs, and ideally no more than 700 words) for each of the two pieces of feedback you provide (each to a separate student). This report must include the following:

- The prompts you were given
- How the feedback was conveyed. If you met in person, please specify when, for how long, and whether it was a one-on-one meeting, or whether the other feedback giver was there.
- A summary of the feedback you conveyed.
- For the second round of peer feedbacks, mention whether there was any follow-up on the feedback you provided in the first round of feedback (e.g., if the feedback recipient acted on some of your feedback, and told you the outcome).

We will provide submission instructions once we are closer to the peer feedback.

### Final Presentation

Details on the requirements for the final presentation will be available closer to the end of the quarter. 

We expect it will involve preparing a pre-recorded presentation, with requirements similar to [last year's presentation requirements]({{< relref "presentation.md" >}}).


## Class-wide bonus points

The entire class can earn up to two points of extra credit if a person (chosen by the instructor/TAs) is able to do the following without any assistance, other than the documentation provided on the chiventure repository:

*   Clone the chiventure repository
*   Build chiventure
*   Load a game
*   Be able to play through the game, and do at least the following:
    *   Explore at least three rooms
    *   Interact with two objects
    *   Place an object in their inventory, and then use it for something
    *   Try some nonsensical actions (putting a door in your inventory, opening something that can’t be opened, etc.) and get reasonable messages from chiventure.
    *   Make use of at least two new features introduced this year.

The user must be able to do this without chiventure crashing or producing any runtime error/warning messages. While the user will not be affiliated with this class, you may assume the user is tech-savvy and familiar with text adventure games (but not with chiventure specifically).

You will have three tries to unlock these bonus points, and you must notify us when you want us to arrange for a user to test chiventure. If the test succeeds on the first try, the entire class will receive two bonus points. On the second try, you will receive 1.5 bonus points. On the third try, you will receive one point.


# Team Composition and Mobility

You will be assigned to teams based on your answers to a team assignment survey. At the start of the project, the composition of these teams will be immovable: please do not ask us to change it.

However, it is not uncommon in software projects for developers to interest themselves in the work done by other teams. So, if you find another team's work to be interesting, we encourage you to look through the code they're writing, poke your head into their Slack channel, etc. You can even offer to help with some of their tasks (especially backlogged tasks), which will also earn you points. Just make sure you're still completing the tasks for your team, and that you discuss with the other team before you do any work on one of their tasks (e.g., "Hey, I saw issue #XXX in your backlog and I may have some extra time to work on that. Is that ok?")

Sometimes, these collaborations result in someone becoming so interested in another team's work that they end up asking to be reassigned to that team. In this class, you will be allowed to switch to a different team after the 2nd sprint, as long as the following conditions are met:

* You must have been doing some work for the other team already, and must be able to point to completed tasks related to that team.
* The switch should be motivated by the work the other team is doing, and because you want to be involved in it. We will not allow you to switch just because you want to be in a team with a particular person from that team.
* Both teams (including the senior developer for each team) must be ok with this switch.
* No team can end up with less than 4 members, or with more than 6 members.