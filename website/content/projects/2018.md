---
title: "Project - Spring 2018"
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

{{% note %}}
This is the grading scheme used in Spring 2018, which is likely to change in Spring 2019. See additional note below.
{{% /note %}}

Unlike a traditional programming assignment or project, the exact final outcome of the project is not known in advance. Of course, we do have high-level goals and requirements (which have been described above) and, while those requirements will help us measure whether the project is “done”, they are not a strict rubric. As we saw in class, this is one of the strengths (and challenges) of agile software development: you can re-evaluate requirements and make design changes quickly, but there is no detailed requirements document that you can use to check whether you’ve contractually fulfilled your obligations to a customer.

As such, the primary mechanism to evaluate your work will be via the tasks (in the Scrum sense of the work) that you complete, as well as your pull requests to the `master` branch of your repository (which will be reviewed by a senior developer). 


Determining your individual score on the project is done in three steps:

1. Adding up your issue points

2. Adding up your pull request points

3. Normalizing your total score

### Step 1: Issue Points

You will keep track of your tasks using GitHub issues. You must make sure that any effort you put into the project is properly documented via a GitHub issue; otherwise, we will not be aware of this work and it won't be considered when determining your individual score!

Once you complete an issue, you will self-report the amount of effort it required:

- Short: Less than one hour
- Medium: Between one hour and three hours
- Long: Between three hours and five hours

Your senior developer may ask you to justify why you assigned a specific effort to a task, if it is not clear from the description (and follow-up comments) of the issue.

Each issue is worth a fixed number of points:

- Short: 1 point
- Medium: 3 points
- Long: 5 points

We further apply a multiplier based on the issue's sprint:

- Sprint 1: ×1
- Sprint 2: ×2
- Sprint 3: ×3
- Sprint 4: ×3
 

Finally, if three or more people worked on an issue, we apply a reduction to that issue’s points:

- 3 people: -20%
- 4 people: -40%
- 5 people: -60%
- 6+ people: -80%

So, for example, a long issue (5 points) in Sprint 4 (multiply by 3) is worth 15 points but, if it was done between three people, then each person gets 12 points (80% of 15)
 

We will refer to your total issue points as *IP*.

 
### Step 2: Pull Request Points

You get 15 points for each successful pull request to master, with the following limitations:

- If three or more people are assignees on a pull request (i.e., if three or more people contributed code to the pull request), the points for that individual pull request are reduced in the same way as with tasks.
- The total amount of pull request points is capped at *IP*.

Your pull request points are re-computed any time your IP changes. This means that, if you completed a pull request to master, but your IP is just 6 points, you would only get 6 additional points from that pull request. However, as soon as you completed more issues, you would be able to “unlock” the remaining 9 points you earned from that pull request.

 
### Step 3: Normalizing your Score

An individual’s total score is the sum of their issue points and their pull request points. We normalize this score by assigning the lower quartile a score of 80, and a standard deviation a score of 10 points (e.g., someone who is one standard deviation above the lower quartile would get 90 points). 


### Total Score

The project is worth 70% of your final grade. These 70 points are divided as follows:

* 40: Your individual score
* 20: Your team score (this will be the average of the individual scores in a team)
* 10: Final presentation during Finals Week.



