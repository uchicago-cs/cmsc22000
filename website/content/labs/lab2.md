---
title: "Lab 2: Software Design"
date: 2018-01-28
publishdate: 2018-01-28
draft: true
---

**Due:** Thursday, April 12th, 4pm

In this lab, you will carry out some basic software design tasks. Before we get to those tasks, we need you to perform an additional (ungraded but necessary) Git-related task so you can fetch the files necessary for this lab.

## Task 0: Pulling from upstream

In the previous lab, you set up your local repo, which is set up by default to pull/push from/to a repository in our GitLab server. The repository on your machine is called a *local repository* while the one on the GitLab server is a *remote repository*. You can actually see the remote repositories associated with your local repository by running this:

    git remote -v

This should show something like this:

    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-18/username.git (fetch)
    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-18/username.git (push)

This actually means you have one remote repository called origin (with the same URL for pulling/fetching and pushing)

In Git, you can actually associate your local repository with multiple remote repositories. This may seem odd, but it is very useful! In particular, we have a repository on the GitLab server where we store the files we want to distribute to you for the labs: https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

If you visit that page, you’ll see it contains a “lab2” folder. These are the files we want you to use in the lab. However, instead of cloning our repository somewhere else and copying those files into your repository, you can simply add this repository as an additional remote repository: 

    git remote add upstream https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18.git

We’ve called this additional remote repository “upstream”. You can verify it was added by running `git remote -v`, which should show the following:

    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-18/username.git (fetch)
    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-18/username.git (push)
    upstream	https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18.git (fetch)
    upstream	https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18.git (push)

Now, to incorporate the files from the upstream repository into our repository, we just need to run the following:

    git pull upstream master

This command is just like the `git pull` you’ve run previously, except we’re saying “pull from the `upstream` repository’s master branch”. Once you run this command, your default editor will open up and will ask you to edit a commit, and will include the following text by default:

    Merge branch 'master' of https://mit.cs.uchicago.edu/cmsc22000-spr-18/cmsc22000-spr-18

    # Please enter a commit message to explain why this merge is necessary,
    # especially if it merges an updated upstream into a topic branch.
    #
    # Lines starting with '#' will be ignored, and an empty message aborts
    # the commit.

Just save the commit without making any modifications, and exit the editor. Your repository will now have a `lab2` directory! This is a copy of the files in the upstream repository, and the changes you make will be saved to your repository, not to the upstream repository (in theory, it would be possible for you to push changes to the upstream repository, but you don’t actually have sufficient privileges to push to that repository)

Before you continue with the lab, make sure to push your changes to your repository on GitLab:

    git push

## Task 1: Refactoring libgeometry

When we discussed the libgeometry library in class, we pointed out (ha!) that our Point datatype had the following function associated with it:

    bool segment_intersect(point_t *p1, point_t *q1, point_t *p2, point_t *q2)

While this function operates on points, what it really does is operate on line segments (i.e., a finite-length line in two-dimensional space, delimited by two points). That said, placing the `segment_intersect` function inside `point.c` / `point.h` is arguably a valid design choice: if segment intersection is the only operation for which we have to work with segments, it would be potentially wasteful to spend the time to define a Segment datatype only to compute segment intersections.

However, as we continue to develop libgeometry, we realize that we need to perform segment operations in a variety of other places. So, it now makes sense to refactor our code to add a Segment datatype.

In this task, you must do the following:

* (15 points) Add `segment.c` / `segment.h` files with the declaration and implementation of a new Segment data type. Make sure to include new/init/free functions. You will also need to update the Makefile to make sure this new file is compiled and included in the libgeometry library. Just update the `SRCS` variable in the Makefile to include your new `segment.c` file.
* (10 points) Take segment_intersect (and associated helper functions) out of `point.c` / `point.h` and make it a part of the Segment datatype. Take into account that this will involve changing the parameters of the function, since it now has to operate on Segments, not on Points.
* (10 points) Update the Polygon implementation so it uses this updated segment_intersect function. At this point, you should be able to build the entire library by running `make`
* (15 points) Uh oh, the libgeometry library may build correctly, but not the tests! (try this by running `make tests`) This is because they still depend on the old version of the `segment_intersect` function. In the `test_point.c` file, update the intersection tests to make sure they use the new version of the file (you don’t need to know exactly how these tests work, and you can keep these tests inside the `test_point.c`; in a future lab, we will see a cleaner way of updating the tests). Once you have fixed this, you should be able to run `make tests` followed by `tests/test-libgeometry`.

## Task 2: Designing a chat application

In this task, you will prepare a class diagram for an application based on a series of requirements (similar to what we did in class with the Library Management System). We will not be picky about individual details, and will care more about your overall design and your justification for certain design decisions.

You must submit your class diagram as a PDF file called `design.pdf` inside the `lab2` directory. This PDF must contain a digitally produced diagram, not a scanned handwritten one. There are many tools available to prepare UML class diagrams, but we recommend using [draw.io](https://draw.io/), a free online diagram editor with extensive support for UML. That said, we also suggest that you first sketch out your diagram on paper and pencil, and only prepare your final polished version once you’re happy with your design.

The requirements for the application are the following:

> We are going to write a simple chat server that provides a small subset of the functionality offered by Slack and similar chat systems. In this chat server, users will be able to log in with a username and password. We will always refer to users by their username (e.g., “borja”) but users also provide a full name (e.g., “Borja Sotomayor”) when they register for an account.
> 
> The server can support multiple channels, where users can chat with each other. When a user sends a message to a channel, it is relayed to everyone in that channel. Users can also send messages directly to each other without having to be in the same channel (unlike Slack, we will not support sending direct messages to more than one user at once)
> 
> Anyone can create a new channel, and channels can be public or private. Anyone can join a public channel, but you can only join a private channel if you are added to that channel by someone who is already in the private channel.
> 
> The server stores all the messages that are sent to a channel or between two users. There is one exception: when a user messages another user directly, they may choose to have an OTR (Off The Record) conversation. Messages sent as part of that conversation are not stored anywhere.
> 
> Finally, users must have the ability to mark certain messages as “favorites”. For example, someone may post some important information in a channel, and it can be useful to “favorite” that message and access it through your list of favorites, instead of having to scroll back in a channel until you find that message. Users can favorite at most 100 messages; if that limit is reached, the message that was marked as a favorite the earliest is removed to make room for the new message.

For the following sub-tasks, write your answers (except the class diagram) in a file called `tasks.txt` inside the `lab2` directory.

* (20 points) Produce a class diagram that captures the requirements described above. If you need a clarification on any of these requirements, please ask during the lab or on Piazza (we will prepare a pinned post with these clarifications so everyone has access to them)
* For the following, you must write the sequence of function calls that would happen in each scenario. You must specify what instances of each datatype exist prior to the scenario (e.g., “`u1` of type User”), and refer to those instances in the function calls (e.g., `send_message(u1, …)`). You are welcome to prepare a UML sequence diagram if you want, but writing your answer in text form (as a sequence of function calls) is perfectly fine.
  * (5 points) There is an existing channel #foobar with users A, B, and C in it. User A sends a message “Hello, everyone!” to the channel.
  * (5 points) User A sends a direct message “How are you?” to User B.
  * (5 points) User A sends a direct message “Hey, can you keep a secret?” to User B in OTR mode.
* (5 points) What data structure would you use to keep track of the messages that a user has favorited? Why?



### Submitting your lab

Before submitting, make sure you've added, committed and pushed all your work in the `lab2` directory (remember you can run `git status` to check this). Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab2
    chisubmit student assignment submit lab2

