---
title: "Lab 4.5: Advanced Git"
date: 2018-01-27
publishdate: 2018-01-27
draft: true
---

**Due:** Monday, April 23rd, 9:30am (start of class)

As you know, the class project will involve large-scale, realistic collaboration
between teams of developers. Collaborating efficiently on a shared codebase is
by no means a trivial task; we need to cultivate a common workflow to ensure
collaboration goes smoothly, so we can focus on development. This lab will
extend the skills you learned in the first git lab to make you an effective
collaborator.

{{% warning %}}
**Note:** This lab doesn't have any evaluation component, but we are still expecting you
to complete it by the start of this coming Monday's class, as it will teach you
skills critical to the the project.
{{% /warning %}}

This lab will be mostly informational - it shouldn't take more than an hour to
get through. It will guide you through the task of creating a pull request
adding yourself to the `AUTHORS.md` file for your team's repository on a new
branch, making a pull request, and having that pull request accepted.

# The development process
We will (roughly) follow this simplified development model during the project:

![dev-process](/cmsc22000/img/dev-process-lab45.png)

This lab will focus on the development and review phases.

# Development phase: branches
So what *is* a branch? You've probably heard us mention branches offhand
during class or office hours. You might also have seen branches disucssed in the
`git` man pages. A branch, loosely, is an **independent commit history** than
can be manipulated in its own right. Branches are, unsurprisingly, created using
the `git branch` command.

Let's set up a branch in your team's repository for adding yourself to
`AUTHORS.md`. Clone your team's repository like so:

```
$ git clone https://github.com/cmsc22000-project-2018/YOURTEAM.git
```

(replacing `YOURTEAM` with your actual team name, one of `redis-tries`,
`spellcheck`, `fulltext`, `support-tools`, `api`, or `autocomplete`. You should
all have your team assignments by now - if not, check your email.)

Now, from inside the repository, you can run `git branch BRANCHNAME` to create a
new branch, replacing `BRANCHNAME` with your desired branch name. But don't do
it yet! Before you do this, let's take a minute to talk about naming
conventions.

If everyone named their branch something like `authors` or `add-authors`, we'd
have 5 branches with the same name. In large collaborative projects, it's common
to prefix branch names with your own first name, to avoid collisions like this.
We will adopt this convention in this class. If your name is Ike, you should
name your branch `ike/add-to-authors` or `ike/authors` or similar. It doesn't
really matter what the name of the branch is, so long as it starts with `ike/`.

Let's also take a minute to discuss exactly what `git branch` does. After you
run `git branch YOURNAME/BRANCHNAME`, `git` creates a new branch called
`YOURNAME/BRANCHNAME`. You can then **check out** this branch using

```
$ git checkout YOURNAME/BRANCHNAME`.
```

Ok, that wasn't super helpful - what does `git checkout` do? Now we're to the
interesting stuff. Let's say we have a given repository state (which just means
a particular arrangement of files) on the `master` branch, and another state on
the `YOURNAME/BRANCHNAME` branch. *Checking out* either branch will
intelligently swap out one repository state for the other. You won't lose any
files this way - they're still tracked by git.

That's all quite opaque, so let's see it in action. Inside your team's repo,
run:

```
$ git branch YOURNAME/BRANCHNAME

$ git checkout YOURNAME/BRANCHNAME
```

Then, edit the AUTHORS.md file to add your name. Make a commit, but **don't**
push. Once you commit, if you run `git status`, you'll see that you have a
*clean* repository state. Now, run `git checkout master`. If you open up
`AUTHORS.md`, you'll see your name is not there! Why? Because, as you can see
from `git log`, the commit you just made **doesn't live on the `master`
branch**. Run
```
$ git checkout YOURNAME/BRANCHNAME
```
and you'll see that `AUTHORS.md` has the change you made once again.

This is the key concept to branching: isolating changes from each other. Why is
this important? It allows us to maintain the `master` branch as the *canonical*
version of our code - that is, code on `master` should always build correctly
and work as intended. When we want to make changes, we do so on a different
branch (colloquially called a *feature branch*), so that our changes are
isolated from the `master` branch until the feature is complete.

Now that your development phase is complete, you should run:
```
$ git push origin YOURNAME/BRANCHNAME
```

# Review phase: pull requests & code review
We will be implementing a process of code review in this class very similar to
what we saw in class today. Before merging any feature branch, we will require
review by:

1. Someone else on your team; and
2. Your senior developer (Mark or Lydia)

To initiate a pull request, head to your team's GitHub page. You can find a list
of all the team pages [here](https://github.com/cmsc22000-project-2018). You
should see a big green button that says "Compare & pull request". Click it.
You'll be taken to a screen that asks you to give a title to your pull request,
and summarize the changes you made. Under "Reviewers", select another student on
your team, and your senior developer. Click "Create pull request". You've marked
your code for review!

Ok, so what's actually going on here? When you create a pull request, you
signify to the maintainers of the repository that the feature on your branch is
complete, and is ready to be **merged** into the `master` branch. A **merge**
takes two branches, combines the changes made on both branches, and creates a
new commit that is the successor of *both* of the most recent commits on the two
branches. Your senior developers will do all merging throughout this project -
they are the guardians of the `master` branch, as it were.

# Summary
Borja? Halp?
