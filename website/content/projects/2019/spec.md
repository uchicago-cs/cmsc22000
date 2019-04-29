---
title: "Project"
date: 2018-02-17T08:47:20-06:00
---


```
You wake up to find yourself in a strange hall. You have no idea how you got here. The last thing you remember is a blinding flash of light. You look at the tapestries lining the walls for any clues on your whereabouts. The tapestries depict valiant knights, fire-breathing wyverns, armies of goblins, and fearsome rulers sitting in their gilded thrones. Wherever you are, it must be in a different world from your own. 

No, not just a different world, but a different time altogether. 

A time of wizards and warlords and all manner of magical creatures, a time to fight back the forces of Throxar the Terrible and to heed the counsel of Wilfrax the Wise... 

It is a time of adventure. 

It is the time of...
```


[![chiventure](/cmsc22000/img/chiventure.jpg "chiventure")](https://www.youtube.com/watch?v=DGSXURPvRxY)


In this project, you will be implementing a _text adventure game engine_. This means that you won’t be implementing an individual game but, rather, a platform that allows game authors (with little or no knowledge of computer programming) to develop text adventure games.


# Text Adventure Games

An [adventure game](https://en.wikipedia.org/wiki/Adventure_game) is a type of video game where the player is the protagonist of an interactive story. Broadly speaking, the protagonist inhabits a world that they can interact with: exploring their surroundings (e.g., reading a sign on the wall), going from one part of the world to another (e.g., going from one room to an adjacent room), manipulating objects in the world (e.g., using a crowbar to open a door), or conversing with non-player characters to gain knowledge that may prove useful later on. The game will have some sort of objective (like finding a treasure), which will mark the conclusion of the game (and the story).

In the early days of video games, adventure games were _text-based_, and players would specify actions using a command-line interface. For example, here is a screenshot of the classic adventure game [Zork](https://en.wikipedia.org/wiki/Zork) (note how commands are entered after the `>` prompt)


![Zork](/cmsc22000/img/zork.png "Zork")


Over time, adventure games became more sophisticated, featuring graphical interfaces, like the one in [The Secret of Monkey Island](https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island) (1990):


![The Secret of Monkey Island](/cmsc22000/img/monkey_island.png "The Secret of Monkey Island")

Source: [https://advgamer.blogspot.com/2014/04/game-43-secret-of-monkey-island-herring.html](https://advgamer.blogspot.com/2014/04/game-43-secret-of-monkey-island-herring.html) 

However, notice how this still retains the basic elements of an adventure game. For example, the player still inhabits a world they can interact with except, instead of typing actions, the player can select actions (Open, Close, Push, etc.) with the mouse, and then point to the recipient of that action (e.g, “Walk to pirate”)

Adventure games are rarely implemented entirely from scratch, though (in fact, this is true of most modern games too). Most games are implemented using a [game engine](https://en.wikipedia.org/wiki/Game_engine), a platform that provides game developers with high-level abstractions for writing games, so they don’t have to worry about every single detail of implementing the game.

For example, [LucasArts](https://en.wikipedia.org/wiki/LucasArts) was a prolific publisher of graphic adventure games ([The Secret of Monkey Island](https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island), [Loom](https://en.wikipedia.org/wiki/Loom_(video_game)), [Sam & Max Hit the Road](https://en.wikipedia.org/wiki/Sam_%26_Max_Hit_the_Road), [Indiana Jones and the Fate of Atlantis](https://en.wikipedia.org/wiki/Indiana_Jones_and_the_Fate_of_Atlantis), ...), and most of them were implemented using a game engine called [SCUMM](https://en.wikipedia.org/wiki/SCUMM), which provided  a high-level scripting language for specifying games, allowing game authors to focus on the narrative elements of the game, while the SCUMM developers focused on the low-level details (e.g., parsing the commands from the user, playing sounds, etc.)

For example, here is a simple SCUMM script that describes a “room” in a game (source: [https://monades.roperzh.com/scumm-internals-syntax/](https://monades.roperzh.com/scumm-internals-syntax/); check out that page to learn more about SCUMM) 


```
    room "doorstep" doorstep {
      sounds {
        "SFX/doorclos" door-close
        "SFX/dooropen" door-open
      }

      costumes {
        "costumes\dave" dave-skin
      }

      enter {
        ; Code to set up the room lives here,
        ; you can trigger sounds, animations, etc.
      }

      exit {
        ; Things to do when exiting the room,
        ; cleaning states, stopping sounds, etc
      }

      object Key {
        name is "key"

        verb look-at {
          say-line "it is a key"
        }

        verb pick-up {
          pick-up-object key
        }
      }
    }
```


Similarly, Zork (and several other games from that era) ran on the [Z-machine](https://en.wikipedia.org/wiki/Z-machine) game engine, with games written in a language called Z-code (the Z-machine is, strictly speaking, a virtual machine, but we can think of it as a game engine). While text adventure games are less common nowadays, the text adventure format still thrives in the [interactive fiction](https://en.wikipedia.org/wiki/Interactive_fiction) genre, which can be written in languages like [Inform](https://en.wikipedia.org/wiki/Inform) (which are relatively easy to use by authors without a technical background).


# Project Organization and Timeline

In this project, you will be divided into six teams of five students, and will work collaboratively (both within your team and between teams) to create a complex software system (a text adventure game engine called `chiventure`) that will involve designing and implementing several distinct components. You will be using several tools to support the collaborative aspects of this project and, indeed, your collaborative skills will be as important as your coding skills to be successful in this project. The project will follow an agile process that resembles (but does not exactly follow) [Scrum](https://en.wikipedia.org/wiki/Scrum_(software_development)).

More specifically, chiventure will be divided into six components. Arrows denote the main dependencies between components (if an arrow points from component A to component B, we expect that component A will have to make use of functionality found in component B), although that does not mean that there couldn’t be other dependencies between components.

![Projects Components](/cmsc22000/img/components.png "Project Components")

The components are the following:

*   **WDL**: Our game engine will have a “World Description Language” that provides the specification of a single game. This component is responsible for defining this language, and for parsing it.
*   **Game State**: A game will have some state we need to keep track of: rooms, objects in rooms, players, non-player characters, etc. This component models this state, and provides interfaces for simple manipulations of the state of the game (e.g., placing an object in the player’s inventory)
*   **Action Management**: During the game, a player will be able to perform actions (pushing, pulling, opening, closing, etc.) that will usually affect the state of the game in some way. The processing of these actions can be non-trivial; for example, picking up an object may only be possible if a certain condition is met (e.g., a magical orb can only be taken if you are in possession of a talisman) and may have additional effects (e.g., pushing a brick in a wall may unlock a door in a different room). This component is responsible for processing actions like “take the orb” (and checking whether it is possible to perform that action), and would use the Game State’s interface to actually change the state of the game.
*   **Checkpointing**: As the state of the game changes, we will want to checkpoint the game so we can resume it at a later time (or, more informally, we need the ability to save games and load games). This component is responsible for defining a file format for saving the state of the game, and providing interfaces for saving/loading this state. 
*   **CLI**: This component will be responsible for providing a command prompt, and parsing the commands entered by the user, and using the game state to validate some commands. For example, if a user types “push button”, the CLI would not call Action Management right away. Instead, it would need to check whether there is anything in the room that can be identified by “button”, whether it can be pushed, and may even have to ask the user to clarify what button (if there are multiple buttons in the room).
*   **UI**: Besides the command-line interface, games may have additional UI elements, like visualizing a map of the game or displaying graphics associated with individual rooms. This component would be responsible for any non-CLI elements of the user interface.

Each team will be assigned to work on one component (teams will have a chance to express a preference for certain components, although we can’t guarantee we’ll be able to assign each team to their preferred component). In each team, a TA will act as Senior Developer.

The project will span seven weeks (Weeks 4 - 10), with a final review and team presentations taking place during Finals Week. The seven weeks of the project will be divided into a project kick-off and four sprints, with sprint reviews happening on Mondays.



*   Week 4: Project kick-off. This week will be primarily used for you to familiarize yourself with project and the exact work your team will do.
*   Week 5: Sprint 1
*   Week 6: Sprint 2. A basic prototype should ideally be done by the end of this sprint.
*   Weeks 7-8: Sprint 3
*   Weeks 9-10: Sprint 4



## Suggested initial goals

To get you started, we suggest each team focus on the following set of initial goals, most of which won't require much communication with other teams at first (allowing you to focus on the requirements of your component before you have to start collaborating with other teams)

### WDL

We don't expect you to define a language completely from scratch, and suggest that you use [YAML](https://en.wikipedia.org/wiki/YAML) as the base format for the WDL. We have even provided some sample WDL files to get you started. However, you shouldn't regard these files as normative: they are a suggestion on what a WDL file would look like, but it is up to you to decide the exact format of the files. Furthermore, while YAML files can be parsed in C using the [libyaml](https://github.com/yaml/libyaml) library, we have provided a library called libobj that provides an abstraction over the low-level operations provided by libyaml.

So, the WDL team can initially focus on this:

- Writing a draft specification of the WDL language
- Writing a module for loading WDL files. This module must do some basic validation of the file (ensuring it meets the specification of the WDL language)

After this, you will find you will need to work more closely with the Game State team to figure out how to load the contents of the WDL file into the data structures provided by Game State.


### Game State

This team will be responsible for designing the data structures that will store the state of the game in memory, as well as a module to manipulate those data structures. A good initial goal is to focus on *designing* these modules by writing the modules' header files without yet writing the implementation of the functions promised by the module's interface. This will get you thinking about what data structures to use, how they will relate to other data structures, what operations you want to allow on each data structure.


### Action Management

The Action Management team is responsible for deciding what actions are possible, and how to model the conditions on an action as well as the effects of an action. Our sample WDL files provide examples of how these action conditions/effects could be specified in the WDL file, but that information will then have to be stored in memory in a general-purpose way that makes it easy to process actions during the game.

As such, this team can initially focus on the following:

- Writing a draft specification of what information is necessary to specify an action (you will then be able to use this to convey to the WDL team your exact requirements for specifying actions in the WDL file)
- Designing, but not yet implementing, a module with the data structures that would allow you to model actions and their processing.


### Checkpointing

This component will be responsible for saving and restoring game state data and, as such, the implementation of this component will be tightly coupled to the design decisions made by the Game State team and the Action Management team. However, there are two broad approaches we could follow: dumping the entire game state to a file, or dumping only a log of actions that have taken place since loading the WDL file. 

So, to get started, it can be useful to start looking into how to save this kind of information into a binary file, possibly using existing [serialization](https://en.wikipedia.org/wiki/Serialization) formats. Writing two sample programs, one that saves information from a mock game (not specifically tied to the WDL or Game State we will eventually use), and another that reads that information and prints it out, can be a good way to start figuring out the mechanics of checkpointing, which will make it easier to accommodate the requirements coming from WDL, Game State, and Action Management later on.

### CLI

In this component, you will be essentially implementing a [REPL](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) interpreter (REPL stands for Read-Evaluate-Print Loop) that will get progressively more complex as you start using the interfaces provided by other components. However, to get started, you should try building a simple REPL interpreter that can parse a few basic actions, such as:

- Actions with no parameters: `LOOK`
- Actions with one parameter: `TAKE orb`
- Actions with two parameters (and a preposition): `GIVE talisman TO wizard`

This can be divided into two distinct tasks: writing the REPL interface itself, and the command parsing. For each of them, we encourage you to look into libraries that can facilitate these tasks.

### UI

This component can go in a lot of different directions, including displaying graphics, playing sounds, etc. To get started we suggest you start by looking into how to do the following:

- Building a [Text User Interface](https://en.wikipedia.org/wiki/Text-based_user_interface) that can split the screen in two: an upper portion that could be used to display graphics or a game map, and a lower portion for the CLI.
- Writing a basic map visualizer that uses text characters to render rooms and connections between them (this can be done independently of the above task, but will eventually have to be integrated with it)

Furthermore, any time you spend researching libraries for building text user interfaces, displaying graphics, playing sounds, etc. will be time well spent.

# Project Evaluation

The project is worth 70% of your final grade, and these 70 points are divided as follows:

*   5: Team Design Exercise
*   40: Your individual score on the project
*   15: Your team score (the average of all the individual scores on a team)
*   10: Final presentation during Finals Week.

Unlike a traditional programming assignment or project, the exact final outcome of the project is not known in advance. Of course, we do have high-level goals and requirements (which have been described above) and, while those requirements will help us measure whether the project is “done”, they are not a strict rubric. As we saw in class, this is one of the strengths (and challenges) of agile software development: you can re-evaluate requirements and make design changes quickly, but there is no detailed requirements document that you can use to check whether you’ve contractually fulfilled your obligations to a customer.

As such, your individual score on the project will be based on how well you perform certain tasks that you will do throughout the project (and which you would encounter in any real software project). More specifically, you will be evaluated based on the following:

*   How well you document tasks/issues (and whether you complete the tasks you commit to doing in a given sprint).
*   Whether you get pull requests to master approved
*   How well you do code reviews (on pull requests where you are a reviewer) 
*   How well you do your peer evaluations

Note: no part of your score will be determined by your teammates. So, when you receive a code review or a peer evaluation, we will be evaluating the quality of the code review / peer evaluation itself; we will not be using that review/evaluation to determine your score. Please note that, in a peer evaluation, we will specifically be evaluating the person giving the feedback (by looking at the quality of the feedback they provide).

Each of the above has a point value:

*   Tasks/issues: 10 points
*   Getting a pull request to master approved: 20 points
*   Code reviews: 15 points
*   Peer evaluation: 15 points

Every time you do one of the above, you will be graded on a simple “check minus”, “check”, or “check plus” scale, and you will accrue 70%, 85%, or 100%, respectively, of the point value of the work you completed.

For example, suppose you have completed 3 tasks (graded “check”, “check”, and “check plus”) gotten a pull request to master approved (graded “check”) and done one peer evaluation (graded “check plus”). You will have accrued the following number of points:

$$ (0.8\cdot 10) + (0.8\cdot 10) + (1.0\cdot 10) + (0.8\cdot 20) + (1.0\cdot 15) = 8+8+10+16+15 =57 $$


Your individual score (out of 100) is simply the following:


$$ \frac{\text{accrued points}}{\text{possible points}}\cdot 100 $$


In this example, your possible points would be 65 (the sum of the point value of each piece of work you did). So, your individual score would be 85.07%

The number of points you accrue can be affected in two ways:



* **Not completing a task you committed to doing.** At the start of each sprint, you will take ownership of certain tasks, and will be committing to doing them by the end of the sprint. If you do not complete a task by the end of the sprint, we will deduct 2 points from your score for that task. So, if your task receives a “check”, but it was late, you will accrue 6.5 points instead of 8.5. Please note that there is some flexibility regarding late tasks (see below). Also, take into account that this penalty does not apply to tasks beyond the ones you committed to doing (e.g., if you commit to doing two tasks, finish them earlier than expected, and there are other tasks you could claim, you could do them to potentially increase your score)
* **Too many cooks in the kitchen.** In some occasions, two or more people may agree to share responsibility for completing a task or for shepherding a pull request to master. This is normal and, when a task or pull request is shared by two or more students, then all of those students will accrue the points for that task (e.g., if two students collaborate on a task that receives a “check minus”, each student accrues 7 points out of a possible 10 points).

    However, when a task is shared by four or more students, the task will be worth 7 points (instead of 10) and pull requests to master that are shared by four or more students will be worth 15 points (instead of 20). For example, if four students collaborate on a task, and the task receives a “check”, then all the students will accrue 5.95 points out of a possible 7 points (7·0.85 = 5.95).

As you will find out throughout the project, estimating the time a task will require can be challenging. You could commit to doing a task thinking it will only take 2-3 hours, and then find that it is actually a 10-15 hour task. So, you are allowed to do the following:



*   For tasks that you committed to doing, you are allowed to be late at most twice throughout the quarter (i.e., you will not be penalized for not completing the task by the end of the sprint). This is similar to how a task can be placed back on the Scrum backlog if it is not completed during a given sprint.
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


> libgeometry currently lacks a way to work with circles. We need to design and implement a module that supports, at least, creating circles, computing their area and diameter, and computing intersections between circles. \


**Task  #2**


> libgeometry only supports points in two-dimensional space. We should generalize this design to support points in any dimensions, by having the point_t type look like this: 
> 
> ```
typedef struct {
    double *vals;
    unsigned int ndims;
} point_t;
```
> 
> The segment and polygon modules will need to be updated to use this new type, and their tests will need to be updated. We also need to add additional tests for segments and polygons in, at least, three-dimensional space. \


**Task #3**

> We would like to eventually be able to visualize points, segments, and polygons. Before doing this, we should pick a library that easily allows us to do this. We should find at least three alternatives, and then discuss which one we prefer. If you would like to suggest a library, please make sure to include a link to their documentation, as well as (if possible) a link to code samples for that library.

**Task #4**


> Computing the intersection of identical segments makes `segment_intersects` crash. You can reproduce this by running this program:
>
> ```
#include "segment.h"

int main()
{
    segment_t s1, s2;
    point_t p1, p2;

    point_init(&p1, 2.0, 3.0);
    point_init(&p2, 5.0, 7.0);

    segment_init(&s1, &p1, &p2);
    segment_init(&s2, &p1, &p2);

    segment_intersects(&s1, &s2);
}
```
> This program immediately segfaults without any other output.

And here are example of summaries that would be less helpful:

**Task #1**


> I’m going to add a circle module

It’s not clear why we’re doing this, or how we’ll know when this task is done.

**Task  #2**

> Turn x, y in point_t to an array. Make sure it doesn’t break any other code.

While this describes what will be done in the task and how we’ll know when it’s done (when any code we break by the update to point_t is fixed), this needs to be more concrete. \


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


### Pull Requests to master

Like in many software projects, the master branch of our Git repository should only contain stable code that compiles, runs, and passes all tests. This is enforced by making the master branch a _protected_ branch, meaning that only the instructors and TAs have the ability to directly push to that branch. Everyone else must make a pull request to get code merged into the master branch.

Because the master branch should contain stable code, pull requests to master must be carefully reviewed before they are approved. If you want to merge code into master, your code must be reviewed by (1) someone in your team, (2) someone in another team, and (3) your senior developer. When your code substantially affects or uses code from another component, then the reviewers from another team must specifically be from the team whose code is being used or affected.

A pull request should contain a relatively self-contained piece of work.  In fact, it is not uncommon for a task (or, at most, 2-3 tasks) to result in a pull request. We encourage you to touch base with your senior developer before creating your first pull requests, to determine whether the work you want to merge merits a pull request (or, similarly, whether it needs to be broken up into multiple pull requests).

Like a task, a pull request should have a descriptive title, a descriptive summary, updates on the progress of the pull request (especially since changes may need to be done based on the code reviews), and a closing statement. The assignees for the pull request must be everyone who contributed to the code that is being merged. If a pull request is approved, all assignees and reviewers will receive the points for that pull request.

Take into account that the final outcome of a pull request could be for that pull request to be denied. If this happens, it will not impact your score (but you will also not receive points for that pull request).


### Code Reviews

You are welcome to create pull requests that do not affect the master branch, and to use these as a mechanism to do code reviews. For example, suppose the Game State team has a “game-state” branch where they do most of their work, and you are working on a “room” branch, writing a module to model rooms. Once you’re done, you should do a pull request from “room” to “game-state” instead of directly merging the branch. This would allow you to request a code review from someone else on your team (and to have a record of that code review in the pull request).

These non-master pull requests must meet the same requirements as a pull request to master, except they only require a single code review from someone on your team. Furthermore, it will be up to you whether to ultimately merge the pull request, but a senior developer may opt to not count the pull request towards your score if it is a trivial pull request (i.e., if it represents a trivial amount of effort, like adding someone’s name to a README). As with pull requests to master, we encourage you to touch base with your senior developer before creating your first pull requests.


### Peer evaluations

Peer evaluations will happen at the end of Sprints 2, 3, and 4. In each peer evaluation, each student will have to evaluate two team members. Details on how peer evaluations will be carried out will be posted before the first peer evaluation. 


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
*   Save the game in progress, exit chiventure, and then resume the game where they left off.

The user must be able to do this without chiventure crashing or producing any runtime error/warning messages. While the user will not be affiliated with this class, you may assume the user is tech-savvy and familiar with text adventure games (but not with chiventure specifically).

You will have three tries to unlock these bonus points, and you must notify us when you want us to arrange for a user to test chiventure. If the test succeeds on the first try, the entire class will receive two bonus points. On the second try, you will receive 1.5 bonus points. On the third try, you will receive one point.


<!-- Docs to Markdown version 1.0β17 -->

