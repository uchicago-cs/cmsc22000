---
title: "Syllabus"
menu: main
date: 2018-02-17T08:47:20-06:00
---

{{% warning %}}
**NOTE**: This syllabus is tentative and subject to change.
{{% /warning %}}


Course Description
------------------

Developing a software system (e.g., an application, a web server, an operating system, etc.) requires much more than just knowing how to program. Software development encompasses multiple activities, such as systems design, implementation, testing, debugging, deployment, documentation, and maintenance, all weaved together by following a specific methodology. Not just that, software development is a highly collaborative activity, where certain soft skills, like effective communication and the ability to give/receive feedback, can be key to the success of a software project.

This class bridges the gap between knowing how to program and knowing how to develop software: it is intended for students who have just completed CMSC 15200 or CMSC 16200, and will cover fundamental concepts and skills in software development, providing a solid foundation before students move on to 200-level classes that require developing complex software systems. The class will cover foundational topics in software development in lectures, but will also include hands-on labs, guest lectures from industry speakers, and a collaborative quarter-long project, where the entire class, divided into teams with specific responsibilities, will work on developing a new feature for an existing software system.

In this course, students will learn how to...

* ... follow a software development process/methodology to manage the life cycle of a software system.
* ... use tools that support the software development process (e.g., build systems, testing frameworks, debuggers, etc.)
* ... develop software collaboratively through (a) the use of tools, systems, and best practices available to facilitate that collaboration (e.g., version control systems, code reviews, task tracking, etc.), and (b) exercising collaborative soft skills (communication, giving/accepting feedback, etc.) 

### Prerequisites

Students must have taken CMSC 15200 or CMSC 16200. 

In Spring 2018, students will have to apply to participate in this class, and only students taking CMSC 15200 or CMSC 16200 in Winter 2018 will be considered (*absolutely no exceptions will be made*)

Please note that CMSC 15400 is *not* a prerequisite for this class. We strongly encourage students taking CMSC 22000 to defer CMSC 15400 until Fall 2018, instead of taking CMSC 22000 and CMSC 15400 concurrently.


Course Organization
-------------------

The class meets three times a week for lectures (MWF 9:30am - 10:20am in Ryerson 277), and once a week for a lab (Thursdays, 5pm-6:20pm in CSIL 3+4).

A large part of the class will revolve around the development of a software project where students will be able to apply many of the concepts covered in the lectures (this project is described in more detail in the “Course Project” section below). In this project, the entire class will work on the same code (i.e., there will be a single code repository shared by the class). Students will be divided into teams of 4-5 students, and each team will work on a specific aspect of the project. In each team, an undergraduate TA (in their 3rd or 4th year) will act as the senior developer in the team. Students will be assessed both on their performance as a team, as well as on their performance on individual tasks assigned to them in their teams.

Labs will supplement the material covered in lectures, and will allow students to learn and practice skills that will be necessary in the course project. At the lab, students will be assigned self-contained exercises that have to be done individually and due before the next lab.

During the first three weeks of the quarter, the lecture sessions will involve lectures by the instructor on core concepts regarding the software development process. Starting in week 4, the focus of the class will shift towards the development of the course project, and the lecture sessions will switch to the following:

* **Mondays**: Project team meetings and all-hands meeting
* **Wednesdays**: Traditional lecture
* **Friday**: Guest lecture from industry speaker


Course Contents
---------------

Please see the [Course Calendar]({{< relref "calendar.md" >}}) page.


Course Project
--------------

The course project revolves around taking an existing software project, and developing new features for that project, including applications that will use those new features. The scope and complexity of this project will require that the entire class work together towards developing those features. 

More specifically, the entire class will be working on the same codebase, using a single Git repository. The class will be divided into teams of 4-5 students, with an undergraduate TA acting as a "senior developer" in each of these teams (TAs will be 3rd/4th year undergraduate students with prior industry experience via internships) Teams will be arranged by the instructor/TAs (they will not be self-selecting).

Starting on Week 4, teams meet at least once a week on Monday, but may elect to meet more often (e.g., for a daily or almost-daily standup meeting). At their weekly meeting, each team must come up with specific tasks to complete within the next 1-2 weeks, with each task assigned to specific people in the team. When a student claims responsibility for a task, they agree to have their performance on that task factor into their course grade. 

Teams will collaborate (within their team and between teams) using tools like GitHub, Slack, etc.

{{% note %}}
The course project is still under development, but we anticipate that it will revolve around implementing a series of new data structures in [Redis](https://redis.io/), (an open source, in-memory data structure store), a series of APIs to interact with those new data structures, and applications that use those APIs.

Please note that the goal of the project isn't to learn about Redis specifically. The goal of the project is for students to apply the concepts they learn in class by developing new features in an existing codebase. Redis was chosen because:

- It is implemented in C, which means that students coming out of CS 152 / 162 will be able to engage with the Redis codebase without having to learn an additional language.
- Redis is a "data structure server", and one of the way of extending Redis is by implementing additional data structures, which will reinforce the data structure concepts that students learned in CS 152 / 162.

We do not expect any of the students' work to be contributed back to Redis (nor will we measure students' performance based on that), although that would definitely be an ideal outcome.
{{% /note %}}


Grading
-------

{{% note %}}
The exact grading structure for this class is still under development, but we expect it to be based on the following factors:

- Graded labs.
- Individual performance on the course project, as measured by the specific tasks that each student claims responsibility for.
- Peer reviews from the team's "senior developer" and from other team members.
- The performance of each team as a whole.
{{% /note %}}


Books
-----

While this class does not have a required textbook, most of the Software Engineering content draws heavily from Ian Sommerville's book, [Software Engineering](http://iansommerville.com/software-engineering-book/). Please see [Additional Resources]({{< relref "resources.md" >}}) for a number of other books and online resources covering much of the material in this class.






