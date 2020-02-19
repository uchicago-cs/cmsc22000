---
title: "Lab 2: Software Design"
date: 2018-01-28
publishdate: 2018-01-28
draft: true
---

**Due:** Thursday, April 18th, 2:30pm

In this lab, you will carry out some basic software design tasks individually, and will also start working with your project team on a design warmup exercise. The individual portion of this lab will be shorter than in other labs, because we expect you to spend part of your time working on the design warmup exercise. In fact, we encourage you to spend most of the lab session working on the team exercise.

Before we get to the individual tasks, we need you to perform an additional (ungraded but necessary) Git-related task so you can fetch the files necessary for this lab.

## Task 0: Pulling from upstream

In the previous lab, you set up your local repo, which is set up by default to pull/push from/to a repository in our GitLab server. The repository on your machine is called a *local repository* while the one on the GitLab server is a *remote repository*. You can actually see the remote repositories associated with your local repository by running this:

    git remote -v

This should show something like this:

    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-19/username.git (fetch)
    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-19/username.git (push)

This actually means you have one remote repository called origin (with the same URL for pulling/fetching and pushing)

In Git, you can actually associate your local repository with multiple remote repositories. This may seem odd, but it is very useful! In particular, we have a repository on the GitLab server where we store the files we want to distribute to you for the labs: https://mit.cs.uchicago.edu/cmsc22000-spr-19/cmsc22000-spr-19

If you visit that page, you’ll see it contains a `libgeometry` folder. These are the files we want you to use in the lab. However, instead of cloning our repository somewhere else and copying those files into your repository, you can simply add this repository as an additional remote repository: 

    git remote add upstream https://mit.cs.uchicago.edu/cmsc22000-spr-19/cmsc22000-spr-19.git

We’ve called this additional remote repository “upstream”. You can verify it was added by running `git remote -v`, which should show the following:

    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-19/username.git (fetch)
    origin	https://mit.cs.uchicago.edu/cmsc22000-spr-19/username.git (push)
    upstream	https://mit.cs.uchicago.edu/cmsc22000-spr-19/cmsc22000-spr-19.git (fetch)
    upstream	https://mit.cs.uchicago.edu/cmsc22000-spr-19/cmsc22000-spr-19.git (push)

Now, to incorporate the files from the upstream repository into our repository, we just need to run the following:

    git pull upstream master

This command is just like the `git pull` you’ve run previously, except we’re saying “pull from the `upstream` repository’s master branch”. Once you run this command, your default editor will open up and will ask you to edit a commit, and will include the following text by default:

    Merge branch 'master' of https://mit.cs.uchicago.edu/cmsc22000-spr-19/cmsc22000-spr-19

    # Please enter a commit message to explain why this merge is necessary,
    # especially if it merges an updated upstream into a topic branch.
    #
    # Lines starting with '#' will be ignored, and an empty message aborts
    # the commit.

Just save the commit without making any modifications, and exit the editor. Your repository will now have a `libgeometry` directory! This is a copy of the files in the upstream repository, and the changes you make will be saved to your repository, not to the upstream repository (in theory, it would be possible for you to push changes to the upstream repository, but you don’t actually have sufficient privileges to push to that repository)

Before you continue with the lab, make sure to push your changes to your repository on GitLab:

    git push

## Refactoring libgeometry

When we discussed the libgeometry library in class, we pointed out (ha!) that the Point module provides the following function:

    bool segment_intersect(point_t *p1, point_t *q1, point_t *p2, point_t *q2)

While this function operates on points, what it really does is operate on line segments (i.e., a finite-length line in two-dimensional space, delimited by two points). That said, placing the `segment_intersect` function inside `point.c` / `point.h` is arguably a valid design choice: if segment intersection is the only operation for which we have to work with segments, it would be potentially wasteful to spend the time to define a Segment module just to compute segment intersections.

However, as we continue to develop libgeometry, we realize that we need to perform segment operations in a variety of other places. So, it now makes sense to refactor our code to add a Segment module.

In this task, you must do the following:

* **Task 1** (30 points) Add `segment.c` / `segment.h` files with the implementation and interface of a new Segment data type. Make sure to include new/init/free functions (like the ones for Point and Polygon). You will also need to update the Makefile to make sure this new file is compiled and included in the libgeometry library. Just update the `SRCS` variable in the Makefile to include your new `segment.c` file.
* **Task 2** (20 points) Take `segment_intersect` (and associated helper functions) out of `point.c` / `point.h` and make them a part of the Segment module. Take into account that this will involve changing the parameters of the function, since it now has to operate on Segments, not on Points.
* **Task 3** (20 points) Update the Polygon implementation so it uses this updated `segment_intersect` function. At this point, you should be able to build the entire library by running `make`
* **Task 4** (30 points) Uh oh, the libgeometry library may build correctly, but not the tests! (try this by running `make tests`) This is because they still depend on the old version of the `segment_intersect` function. This is an example of how things can break if dependencies are not properly managed.

    In the `test_point.c` file, update the intersection tests to make sure they use the new version of the file (you don’t need to know exactly how these tests work, and you can keep these tests inside the `test_point.c`; in a future lab, we will see a cleaner way of updating the tests). Once you have fixed this, you should be able to run `make tests` followed by `tests/test-libgeometry`.

## Project Team Exercise: Design Warm-up

You can find the specification of the team exercise [here]({{< relref "../projects/2019/design-1.md" >}})

Please note that this exercise is not part of your Lab #2 grade. Instead, it will be part of your Project grade for the class (see the [syllabus]({{< relref "syllabus.md" >}}) for more details) You should nonetheless use the lab time to get to know your team, and to start discussing the team exercise.


## Submitting your lab

Before submitting, make sure you've added, committed and pushed all your work in the `lab2` directory (remember you can run `git status` to check this). Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab2
    chisubmit student assignment submit lab2

