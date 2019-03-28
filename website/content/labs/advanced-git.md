---
title: "Optional Lab: Advanced Git"
date: 2018-01-27
publishdate: 2018-01-27
draft: true
---

In the 150s/160s, as well as in the CS 220 labs, you have used version control systems 
(like Subversion and Git) essentially as a mechanism to store your code and to make it easily accessible to the
course staff. However, in real software projects, version control systems are
one of the most important tools that allow teams to collaborate on a shared
code base.

In this lab, we will explore features of Git that are more directly related to collaborative
software development, and which you will need to use during the course project. While most of
the concepts we will explore are not specific to any one Git platform, we will be using
GitHub exclusively throughout the lab, as that is the platform you will
be using for the course project.

This lab will not be graded, but you must work through it before you can start working on the project.
In particular, it includes one task which we will be checking; if you do not complete it
by the end of fifth week, we may nag you about it.

# Working collaboratively with Git

Suppose you are working with a classmate on a homework assignment that requires
producing a single file called `hw1.c` that includes the implementation of some
functions. If the file is located in a shared filesystem (like the CS filesystem
where the same home directories appear on all the CS machines), the two of you could
edit it at the same time, but you'd have to be careful not to overwrite
each other's work.

For example, suppose you both open the file and it contains the following:

    int foo()
    {
        // Write your code here
    }

You decide to work on function `bar()` and your partner decides to work on function
`baz()`. So, you end up with this file:

    int foo()
    {
        // Write your code here
    }

    int bar()
    {
        // ...
    }

And your partner ends up with this:

    int foo()
    {
        // Write your code here
    }

    int baz()
    {
        // ...
    }

If you save the file, and then your partner saves it after you, their version of
the file will overwrite yours, so all your work on `bar()` will be overwritten.

Ideally, we would like to end up with a consolidated version of the file that looks
like this:

    int foo()
    {
        // Write your code here
    }

    int bar()
    {
        // ...
    }

    int baz()
    {
        // ...
    }

Of course, instead of using a shared filesystem, you could instead decide
that only one person can edit the file at a time, but that would involve
a lot of overhead in coordinating each other's work.

Consider this other scenario: let's say that the `foo()` function involves
implementing two sub-tasks, which you divide amongst yourselves, and you each replace 
the `// Write your code here` with your code (for the sake of simplicity, let's assume
that each sub-task is implemented with a single `printf`). Your code might look
like this:

    int foo()
    {
        printf("Implemented task 1\n");
    }

And your partner's code might look like this:

    int foo()
    {
        printf("Implemented task 2\n");
    }

This actually represents a *conflict* in your code: you each have divergent replacements
for the `// Write your code here` line, and it is not clear which version is
the correct one. In fact, while there may be cases where we simply want to use
one version over another, in this case we would like to *merge* these two versions
together to produce something like this:

    int foo()
    {
        printf("Implemented task 1\n");
        printf("Implemented task 2\n");
    }

Notice how, earlier, there was no conflict when implementing `bar()` and `baz()` because
you were adding code to `hw1.c`, instead of replacing existing code with different versions.

Version control systems like Git are very useful when dealing with scenarios like
the ones above. They will allow two (or more) developers to work concurrently on
the same code and, whenever possible, will automatically merge together changes
that do not conflict. When a conflict does arise, Git provides a specific
mechanism to resolve that conflict.

In the remainder of the lab, we will explore the following concepts:

* Forking: Creating a copy of a repository that you can work on independently
  from the original repository.
* Branches: A mechanism for creating an independent commit history that can
  be manipulated by itself.
* Pull requests: A mechanism for requesting that certain changes (usually
  those on a branch) be merged into a repository.

To explore these concepts, we have created the following repository on GitHub
which contains only a single file in it:

https://github.com/uchicago-cs/cmsc22000-dummy-repo

# Forking a repository

Let's say we want to make some changes to the `cmsc22000-dummy-repo` repository.
You could clone that repository and make some commits in it, but you would be
unable to push those commits to the repository: you are not a developer
in the `cmsc22000-dummy-repo` repository, and thus don't have push privileges
on it.

This is a very common scenario: there are millions of repositories on GitHub and
the owners of those repositories don't want just anybody pushing changes
to those repositories. However, let's say you find a bug in a GitHub repository,
and know how to fix it. You would ideally like to contribute a fix back to
that repository, but you would be unable to push that fix to the repository.

So, a common first step in this case is to *fork* the repository. This creates
a copy of the repository under your account, on which you *will* have push
privileges. So, let's start by forking the `cmsc22000-dummy-repo` repository:
go to https://github.com/uchicago-cs/cmsc22000-dummy-repo and click on the Fork
button in the top-right of the page:

![fork](/cmsc22000/img/git-lab-fork.png)

If you are prompted to specify "Where should we fork this repository?", make sure
you select our GitHub user account.

Your forked repo will now live here:

https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo

Where `GITHUB_USERNAME` should be replaced by your GitHub username.

Now, clone this repo on your computer:

    git clone https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo.git

Please note that there is also a "Clone or download" button on your repo's page
that you can click to obtain the URL to pass along to `git clone`.

Next, `cd` into `cmsc22000-dummy-repo`. We will be making some changes inside the
repository. However, before we continue, we will reiterate an important point:
any changes you make in `cmsc22000-dummy-repo` will *not* be pushed
to the original `cmsc22000-dummy-repo` repository (the one in https://github.com/uchicago-cs/cmsc22000-dummy-repo).
Instead, they will be pushed to your *fork* of that repository, which lives
inside your GitHub account (https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo).
Later on, we will see how you would be able to contribute changes back
to the original repository.


# Branches

So far, the commits in your lab repository have created a linear sequence of
changes like this:

![branches](/cmsc22000/img/git-lab-branches.png)

You may have heard us talk informally about "branches" or seen that term
in a variety of places (the GitLab/GitHub web interfaces, online
documentation). So what *is* a branch? A branch, loosely, is an **independent commit history** than
can be manipulated in its own right. Every git repository has, at least, one branch:
the `master` branch and, so far, you have been working only with that branch (and, thus,
with a single linear history of commits).

However, Git (and most version control systems) allow you to create *multiple*
branches. These branches are not completely independent of each other as, ordinarily,
a branch must be "branched off" from an existing commit. So, for example, we
could have the following:

![branches2](/cmsc22000/img/git-lab-branches-2.png)

Here, besides the `master` branch, we have an additional `task3` branch which 
could be used to work specifically on Task 3 of a lab. This separate
branch allows us to work on Task 3 independently from the other tasks; this
may seem over-complicated, but suppose you were working on the lab with
a classmate: branches would allow you to work indepedently without having
to step on each other's toes. This is similar to the first example we showed
above (where two developers could be working on separate functions, `bar()`
and `baz()`).

Let's create a new branch in your `cmsc22000-dummy-repo` repository. The branch
will be called `add-author` and you can create it by running this:

    git checkout -b add-author

If you run `git branch`, you can see the list of branches in the repository,
with the current branch highlighted with an asterisk:

    * add-author
      master

The *current branch* of a local repository is the branch where any new commits
will be added to. Remember, a single branch is a linear sequence of commits
and, when we have multiple branches (as shown in the diagram above), a commit
could be placed after the last commit, or *head*, of any branch. The head of
the current branch is referred to as the `HEAD` (in all caps) of the repository.

You can switch the current branch by using the `git checkout` command. For example:

    $ git checkout master
    Switched to branch 'master'
    Your branch is up to date with 'origin/master'.
    $ git branch
      add-author
    * master
    $ git checkout add-author 
    Switched to branch 'add-author'
    $ git branch
    * add-author
      master

Now, let's add a commit to the `add-author` branch. Simply edit the `echo.c`
file and replace `[AUTHOR GOES HERE]` with your name. You can commit the change
but, if you try to push it, you will get an error message like this:

    $ git push
    fatal: The current branch add-author has no upstream branch.
    To push the current branch and set the remote as upstream, use

        git push --set-upstream origin add-author

**This means the push has not been completed**. The reason for this is that
we haven't told Git where to push this new branch (it will not assume that
it has to be pushed to the GitHub repository). Fortunately, you can resolve
this issue simply by running the verbatim command provided in the error message:

    $ git push --set-upstream origin add-author
    Counting objects: 3, done.
    Delta compression using up to 8 threads.
    Compressing objects: 100% (2/2), done.
    Writing objects: 100% (3/3), 292 bytes | 292.00 KiB/s, done.
    Total 3 (delta 1), reused 0 (delta 0)
    remote: Resolving deltas: 100% (1/1), completed with 1 local object.
    To github.com:borjasotomayor/cmsc22000-dummy-repo.git
     * [new branch]      add-author -> add-author
    Branch 'add-author' set up to track remote branch 'add-author' from 'origin'.

If you now go to https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo, and click
on the "Branch" pull-down list, you will see `add-author` in the list of branches
(you will also see some additional branches besides the `master` branch; we will
see these soon).

# Merging

The `master` branch is, by convention, the "stable" branch of the repository,
in the sense that it should only contain stable (not broken) code. So,
it is very common to create separate branches to implement specific tasks,
features, etc. and to then *merge* them back to the `master` branch once
that work is finished. This keeps the `master` branch much cleaner, as
it only contains the "final" version of our code at any point, instead
of lots of commits that may represent work in progress.

When we merge a branch with another branch, we basically take all the changes
done in all the commits in the origin branch, and add them to the destination branch.
This is done by creating a new commit, called a *merge commit*, to merge together
the heads of the two branches. For example, in this diagram, commit `854bff54` merges
`task3` into `master`:

![branches3](/cmsc22000/img/git-lab-branches-3.png)

Our repository actually has two other branches: `change_author1` and
`change_author2`. Go to https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo
and browse those branches. Remember you can use the "Branches" pull-down list
to switch between branches on GitHub; once you're on a specific branch, you can
click on "commits" to see the list of commits for that branch specifically. You
should be able to see a commit that updates `[AUTHOR GOES HERE]` in `echo.c`
to `Created by John Doe`.

You should also explore these branches from the command-line using `git checkout`.

Now, let's say we want to merge the changes from `change_author1` into the `master` branch.
We first need to switch to the `master` branch:

    git checkout master

Then, we use `git merge` to specify that we want to merge `change_author1` into
the current branch (`master`):

    git merge change_author1

If you get an error saying `change_author1 - not something we can merge`, make sure you've
switched to the `change_author1` branch at least once using `git checkout`. Otherwise,
Git will not have a local copy of the `change_author1` branch to make the merge.

If the merge works, you should see the following:

    Updating 92a20af..e44f03a
    Fast-forward
     echo.c | 2 +-
     1 file changed, 1 insertion(+), 1 deletion(-)

You should open `echo.c` to verify that the merge was completed successfully.

However, if you run `git log`, you won't see any special "merge commit" in the log history:

    commit e44f03a501fc380ef84e53bb8c0f8e978bc8ffed
    Author: Isha Mehrotra <imehrotra@cs.uchicago.edu>
    Date:   Fri Mar 23 18:52:31 2018 -0400

        updated author to John Doe

    commit 92a20afcbfdd4ac7e174b47afc9a53bfeaf9b300
    Author: Isha Mehrotra <imehrotra@cs.uchicago.edu>
    Date:   Fri Mar 23 18:48:56 2018 -0400

        wrote echo.c program

The reason for this is that this was a fairly trivial merge which could be *fast-forwarded*,
because the commit in `change_author1` (`updated author to John Doe`) 
descends directly from the `wrote echo.c program` commit in `master`, 
so we can simply take that commit and add it to `master`. 

Things get a bit trickier if we want to merge the `add-author` branch we created. That branch
was also branched off the original `wrote echo.c program` commit in `master`, but now `master`
has a new commit (`updated author to John Doe`). This means that `master` and `add-author`
have *diverged*, and a fast-forward commit will not be possible.

So, let's try merging in `add-author`:

    $ git merge add-author 
    Auto-merging echo.c
    CONFLICT (content): Merge conflict in echo.c
    Automatic merge failed; fix conflicts and then commit the result.

Git has detected a merge conflict! The `master` branch contains a change for the
`[AUTHOR GOES HERE]` line in `echo.c`, but so does the `add_author` branch. A
merge conflict is basically Git telling us "I see two conflicting changes on these
two branches, and I don't know how to resolve them automatically; you need to tell me
how to do it". 

Merge conflicts will also be shown on `git status`:

    $ git status
    On branch master
    Your branch is ahead of 'origin/master' by 1 commit.
      (use "git push" to publish your local commits)

    You have unmerged paths.
      (fix conflicts and run "git commit")
      (use "git merge --abort" to abort the merge)

    Unmerged paths:
      (use "git add <file>..." to mark resolution)

	    both modified:   echo.c

    no changes added to commit (use "git add" and/or "git commit -a")


If you open `echo.c`, you will see something like this:

    /* echo.c - echo user input */
    <<<<<<< HEAD
    /* Created by John Doe */
    =======
    /* YOUR NAME */
    >>>>>>> add-author
    /* Last updated: 3/23/18 */

(where `YOUR NAME` will be the name you entered when you created the `add-author` branch)

In general, any time you see something like this:

    <<<<<<< branch1

    =======

    >>>>>>> branch2

This is Git telling you "this is the version of the code in branch `branch1` and
the version of the code in `branch2`; tell me which one to use". In this case, the
current branch (`HEAD`) contains this line:

    /* Created by John Doe */

And the branch you're trying to merge, `add-author`, contains this:

    /* YOUR NAME */

In this case, we simply want to choose one version over another, so you should replace this:

    <<<<<<< HEAD
    /* Created by John Doe */
    =======
    /* YOUR NAME */
    >>>>>>> add-author

with this:

    /* YOUR NAME */

i.e., the top of echo.c should look like this:

    /* echo.c - echo user input */
    /* YOUR NAME */
    /* Last updated: 3/23/18 */

Now, we need to tell Git that we've resolved the merge conflict. We do this by using `git add`:

    git add echo.c

Note how now `git status` recognizes that the merge conflict has been resolved, but has yet
to be committed:

    $ git status
    On branch master
    Your branch is ahead of 'origin/master' by 1 commit.
      (use "git push" to publish your local commits)

    All conflicts fixed but you are still merging.
      (use "git commit" to conclude merge)

    Changes to be committed:

	    modified:   echo.c

So, all we need to do is to run this:

    git commit

This will open up an editor with a default commit message like `Merge branch 'add-author'`. Simply
save that commit message, and the merge will be completed and you will see something like this:

    [master 9f74d3f] Merge branch 'add-author'

That is the *merge commit* for this merge; if you run `git log`, you will see that the commit 
history now includes the commit from `add-author`, as well as the merge commit. Notice how
includes a line telling us which two commits were merged:

    commit 9f74d3fc4c3b84bf80c0a4adc9ac7a862b382289
    Merge: e44f03a a6f8642
    Author: Borja Sotomayor <borja@cs.uchicago.edu>
    Date:   Sun Apr 22 12:37:40 2018 -0500

        Merge branch 'add-author'

    commit a6f8642bed35e2778f97f27b55e1aab8697afe61
    Author: Borja Sotomayor <borja@cs.uchicago.edu>
    Date:   Sun Apr 22 11:57:48 2018 -0500

        Added author

    commit e44f03a501fc380ef84e53bb8c0f8e978bc8ffed
    Author: Isha Mehrotra <imehrotra@cs.uchicago.edu>
    Date:   Fri Mar 23 18:52:31 2018 -0400

        updated author to John Doe

    commit 92a20afcbfdd4ac7e174b47afc9a53bfeaf9b300
    Author: Isha Mehrotra <imehrotra@cs.uchicago.edu>
    Date:   Fri Mar 23 18:48:56 2018 -0400

        wrote echo.c program

Before continuing with the rest of the lab, make sure to push all these commits by
running `git push`.

# Pull requests

So far, we've made some changes to a fork of the following repository:

https://github.com/uchicago-cs/cmsc22000-dummy-repo

Remember that we don't have push access on that repository, but we do have
push access on our fork. In fact, a common reason for creating a fork of
a repository is so we can make some changes to that fork, and then contribute
our changes back to the original repository.

The way we do this is by doing a *pull request*. In other words, we submit a request
to the original repository to pull our changes. You are going to create a pull request
with the changes you made in your fork. To do this, go to your forked repository on GitHub:

https://github.com/GITHUB_USERNAME/cmsc22000-dummy-repo

You will see a "New pull request" button above the file listing. Click it. The next
page will summarize the commits you are going to include in the pull request. If
you see anything that looks amiss, please ask on Piazza. Otherwise, click on the
green "Create pull request" button. You will now be able to specify a title and
a summary for the pull request. For example, in this case, the title could be "Adding author
to echo.c" and the summary could be "I am the author of this file". Finally, click
"Create pull request" again, and this will create the pull request. You can verify
that your pull request was submitted to the original repository here:

https://github.com/uchicago-cs/cmsc22000-dummy-repo/pulls

Now, once we receive your pull request, we will actually deny it (you're not the author of echo.c!),
but you will have a chance to submit a successful pull request in the next section.

# Code reviews with pull requests

In the example we have seen so far, you forked a repository so you could make
changes to it and submit those changes back to the original repository. This
is a very common collaboration pattern, specially in open source software.
If you spot a bug in your favorite software project, and their code is hosted
on GitHub, you can create a fork of that repository, create a bugfix, and
submit it back to the original repository using a pull request.

In the class project, however, you will not need to create a fork of your
team's repository, because you *do* have push access in that repository,
but with an important restriction: you are allowed to create additional
branches and push to them, but you are *not* allowed to push to the `master`
branch (in this case, we say that `master` is a *protected branch*). 
Only the senior developers (i.e., the instructor and the TAs)
are allowed to push to `master`, which means that all changes to the `master` 
branch by a junior developer (i.e., you) must be reviewed and approved by a senior developer.

This is another common collaboration pattern, which allows a team to work
in the same repository (without having to create multiple forks), but making
it less likely that broken code will enter the `master` branch.

We are going to follow this pattern to add yourself to the `AUTHORS.md` file
of your team repository. First, clone your team's repository like so:

```
$ git clone https://github.com/cmsc22000-project-2018/YOURTEAM.git
```

(replacing `YOURTEAM` with your actual team name, one of `redis-tries`,
`spellcheck`, `fulltext`, `support-tools`, `api`, or `autocomplete`. You should
all have your team assignments by now - if not, check your email)

Now, from inside the repository, you will create a branch to make your
change to `AUTHORS.md`. But don't do it yet! Before you do this, let's 
take a minute to talk about naming conventions.

If everyone named their branch something like `authors` or `add-authors`, we'd
have 5 branches with the same name. In large collaborative projects, it's common
to prefix branch names with your own first name, to avoid collisions like this.
We will adopt this convention in this class. If your name is Ike, you should
name your branch `ike/add-to-authors` or `ike/authors` or similar. It doesn't
really matter what the name of the branch is, so long as it starts with `ike/`.

So, go ahead and create a new branch and check it out:

```
$ git branch YOURNAME/add-to-authors

$ git checkout YOURNAME/add-to-authors
```

Then, edit the AUTHORS.md file to add your name. Make a commit and push the
new branch:

```
$ git push origin YOURNAME/add-to-authors
```

To initiate a pull request, head to your team's GitHub page. You can find a list
of all the team pages [here](https://github.com/cmsc22000-project-2018). You
should see a big green button that says "Compare & pull request". After you click
it, you will be presented with a page like the one you were shown when creating
the pull request for the `cmsc22000-dummy-repo` repository. However, besides
entering a title and summary, you will also specify the following:

* Under "Reviewers", select another student on your team, and your senior developer. 
* Under "Projects", select "Project Board" (we will discuss Project Boards in class)
* Under "Milestone", select "Project Kick-off"

Click "Create pull request". You've marked your code for review!

Note: if someone specifies you as a reviewer for this pull request, simply go ahead
and mark the pull request as reviewed. For the project, you won't arbitrarily get
selected by teammates to review code; you will have to agree to review someone's code
before it is assigned to you.

