---
title: "Project"
menu: main
date: 2018-02-17T08:47:20-06:00
---

In this project, you will be divided into six teams of five students, and will work collaboratively (both within your team and between teams) to create a complex software system that will involve not just designing and implementing a number of components, but also extending an existing software system. You will be using several tools to support the collaborative aspects of this project and, indeed, your collaborative skills will be as important as your coding skills to be successful in this project.

The project will revolve around extending the [Redis](https://redis.io/) data store, and developing a number of applications around our extended version of Redis. Redis is often described as a “data structure server”. What does this mean? When you write software, you often need to use data structures like linked lists, hash tables, etc., and in many cases you can simply use a data structure library (e.g., simclist, utlist, uthash, etc. in C) or the data structures included in the standard library of your language of choice (e.g., the [Hashtable](https://docs.oracle.com/javase/8/docs/api/java/util/Hashtable.html) class in Java, the [queue](https://docs.python.org/3.6/library/queue.html) module in Python, etc.). When you use these data structures, they are created and manipulated in the memory of the computer where you are running your program.

With Redis, these data structures live in a server that you access through the network. This may seem wasteful (why incur the cost of accessing the data structure via the network when you could just access it directly on your computer?) but this architecture has several distinct advantages:

* Multiple computers could share a data structure stored in the server.
* Redis provides well-tested, highly-optimized implementation of the data structures.
* Redis handles a number of other aspects, such as reliability, availability, etc.

Redis supports many data structures you are already familiar with, like lists and hash tables, but does not support prefix trees and suffix trees (which are typically implemented using a special tree data structure called a trie). In this project, you will be adding support for these data structures, and will develop three command-line applications that use these data structures:

* Autocomplete: A tool which, as you type, will either automatically complete words or, when pressing the tab key, will suggest all possible completions for a given prefix.
* Spell checker: A tool which, given a text, will search for misspelled words and will suggest alternative spellings.
* Large text search: A tool which, given a text of arbitrary size, can efficiently find occurrences of a word (or one of several words) in that text.

Redis provides a remote API that applications can use to create and access data structures and, while there exist a number of C libraries that facilitate interacting with that API, they are fairly low-level. So, we will also implement a library that provides a higher-level API to interact with the tries in Redis.

Finally, we will also implement a series of support tools and libraries to facilitate the work of all the teams. At the very least, we will produce a tool to interactively experiment with tries (through the higher-level API), although we may end up producing other tools.

## Project Organization and Timeline

The project will follow an agile process that resembles (but does not exactly follow) [Scrum](https://en.wikipedia.org/wiki/Scrum_(software_development)).

Students in the class will be divided into six teams:

* Tries: Responsible for adding support for tries in Redis
* API: Responsible for creating the higher-level API
* Support Tools: Responsible for implementing support tools
* Autocomplete team: Responsible for implementing the autocomplete tool
* Spell Checker team: Responsible for implementing the spell checker tool
* Full Text Search team: Responsible for implementing the full text search tool

You will be placed into different teams based on a survey you will be asked to fill out. In each team, a TA will act as Senior Developer

The project will span seven weeks (Weeks 4 - 10), with a final review and team presentations taking place during Finals Week. The seven weeks of the project will be divided into a project kick-off and four sprints, with sprint reviews happening on Mondays.

* Week 4: Project kick-off. This week will be primarily used for you to familiarize yourself with project and the exact work your team will do.
* Week 5: Sprint 1
* Week 6: Sprint 2. A basic prototype should ideally be done by the end of this sprint.
* Weeks 7-8: Sprint 3
* Weeks 9-10: Sprint 4

## Application Requirements
The project will be driven largely by the requirements of the three applications we will be developing. All three applications have the following requirements in common:

* The application must use tries in Redis.
* The application must be a command-line tool. 
* The tool must work both interactively and in batch mode (this is described below in more detail). The default is for each tool to run in interactive mode, with command-line parameters controlling whether it instead will run in batch mode.

The autocomplete and spellcheck tools specifically require that a collection of words (typically “all” the words in the English language) are pre-loaded into the Redis server. However, these tools must also allow these words to be loaded from scratch when the tool starts running (this will be necessary for testing purposes)

The **autocomplete** tool must allow a user to type text interactively. As the user types, the following can happen:

* If the user enters a word prefix that can only be completed in one way (e.g., “if a user types “alibii”, the only possible completion is “alibiing”), the tool must automatically complete the word.
* If a user enters a prefix and presses the Tab key, the tool must show all the possible completions of that prefix (if there are more than 10 possible completions, the tool should indicate in some way that there are “too many” possibilities). It there are 10 or lest completions, it must allow the user to easily select one (or to keep typing).

The tool must also work in batch mode: it must be able to take a file containing a list of prefixes and, for each prefix, provide the number of completions for that prefix. It must also be possible to produce all the possible completions for each prefix, up to a configurable maximum.

The **spell checker** tool must allow a user to open a text file, and to interactively correct any misspelled words. The spell checker must highlight in some way one misspelled word at a time, and suggest possible corrections to the user (the user can accept one of the corrections, leave the word as-is, or provide an alternate spelling). The spell checker must save the file with the corrections (or save it to an alternate file, if specified by the user)

When run in batch mode, the spell checker can operate in one of two ways:
* It will take a text file and will replace all misspelled words with the best possible replacement.
* It will take a text file containing a list of words, and will produce a list of all the misspelled words with the suggested corrections for each word.

The **full text search** tool must allow a user to open a text file, to specify a word or words, and to interactively navigate the text file, skipping from matched word to matched word. When run in batch mode, this tool must take a text file and count the occurrences of a word (or words) specified as command-line parameters. It must also be able to produce (either on standard output or in another file) all the lines containing the specified word(s) with zero or more lines before/after the line with the word(s) (where this number of lines must be configurable)

## Project Evaluation

Unlike a traditional programming assignment or project, the exact final outcome of the project is not known in advance. Of course, we do have high-level goals and requirements (which have been described above) and, while those requirements will help us measure whether the project is “done”, they are not a strict rubric. As we saw in class, this is one of the strengths (and challenges) of agile software development: you can re-evaluate requirements and make design changes quickly, but there is no detailed requirements document that you can use to check whether you’ve contractually fulfilled your obligations to a customer.

As such, the primary mechanism to evaluate your work will be via the tasks (in the Scrum sense of the work) that you complete. At each sprint review, the team as a whole decides what tasks must be completed by the next sprint review, and individual developers will claim tasks, and you will be evaluated, as a team and individually, on the outcome of those tasks. For the purposes of evaluation, the following rules will apply.

### Claiming Tasks
**The Most Important Rule To Remember**: *If you claim a task, you are agreeing to be evaluated on the outcome of that task*. 

Tasks are not assigned by a manager: the tasks are decided as a team, and individual developers claim them. You should claim tasks willingly, and knowing that you are going to be evaluated on your work on that task.

### Task Scoring
Tasks are categorized by difficulty: Trivial, Easy, Medium, Hard, Challenging. Your Senior Developer will determine the difficulty of each task (either at the sprint review, or shortly afterwards). Trivial tasks are worth 1 point, Easy tasks are worth 2 points, etc. 

Your Senior Developer may reclassify the difficulty of a task if it turns out to be more challenging than expected. They will never reclassify a task so it will be worth less points than you originally signed up for.

You get the points for a task if it passes a code review, and is merged into the master branch.

### Code Reviews
Once a developer finishes their work on a task, it must undergo a review by another developer and then by the Senior Developer.
If the Senior Developer signs off on a task without requesting any changes, you get full points for the task. However, if the Senior Developer requests changes, the following penalties will apply:

* -5% if the Senior Developer signs off on your task after those changes have been completed (this penalty will be only 2% if the changes are only style-related)
* -15% if you go through more than one round of changes requested by the Senior Developer. 

Take into account that you can go through as many rounds of changes as you want with the other developer that reviews your code (so it is in your best interest to get as much out of that review before you ask your Senior Developer to review your task)

### Individual Sprint Score
Your individual score at the end of a sprint is the sum of the points of the tasks you completed, divided by the total possible points of the tasks you claimed responsibility for. 

For example, if you claimed two Easy tasks and a Medium task, your total possible score is 2 + 2 + 3 = 7. If you completed the Easy tasks with a -5% adjustment and the Medium task with a -15% adjustment, the sum of the points is 1.9 + 1.9 + 2.55 = 6.35. So, your individual score would be 6.35 / 7 = 90.7%

**Backlog exception**: It is normal, and even expected, that some tasks will remain undone by the end of the sprint (and will simply be placed back in the backlog). These tasks will not factor into your individual score unless you complete less than 80% of the points assigned to you. The first time this happens, you will only receive a warning. The second time this happens, you will receive a 10% penalty in that sprint. If it happens a third time, you will no longer benefit from the backlog exception.

Another way of thinking about this is that, in a given sprint, you have the flexibility to return 20% of your points to the backlog without being penalized for it.

### Team Sprint Score
Your team score at the end of a sprint is the sum of the points of all the tasks that were completed by the team, divided by the total possible points of all the tasks that were not returned to the backlog.


### Lazy Developer Penalty
If a team completes 100 points of work in a sprint, it will be rare for the work to be divided exactly evenly (20 points per developer). However, we also want to avoid situations where three developers do most of the work, while the rest just work through some trivial tasks. So, in a given sprint, each developer must complete at least (T / N) * 0.8 points of work, where T is the total number of points earned by the team in that sprint, and N is the number of developers.

The first time a developer falls under this threshold, they will receive a warning. The second time this happens, they will get a 10% penalty in their individual score. After that, the penalty rises to 20%.

A more positive way of framing this penalty is that, if a developer is really busy with other work during a given sprint, it gives them the flexibility to take on less work in that sprint without being penalized for it. However, it is expected that the developer would make their team aware of this when the tasks for a given sprint are being assigned.


### Total Score
Your total project score will be divided into three parts:
* The average of your individual scores in each sprint accounts for 50% of your project score.
* Your team’s score accounts for 40% of your project score.
* The remaining 10% will be determined by a final presentation that your team will give during Finals Week. Details about these presentations will be posted at a later time.

### Adjustments to Evaluation Scheme

Since this is the first time we offer this class, we may need to adjust this evaluation scheme. We reserve the right to adjust the evaluation scheme in the following ways:

* At the end of Sprint 2, we may change the evaluation scheme partially or fully, but all the work done in Sprints 1 and 2 will be evaluated using the original evaluation scheme.
* We may change the evaluation scheme entirely and retroactively at any time but only if it does not reduce anyone’s scores.



