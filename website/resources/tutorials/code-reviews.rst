Tutorial: Code Reviews with Pull Requests
=========================================

In many software projects, the main branch of the source code repository
is *protected*. This means that only a select few individuals can directly
push to that branch. Anyone else who wants to push code to that branch
has to go through a *code review*: any code you want to merge into the
main branch has to be reviewed (typically by more senior developers)
to ensure that there are no issues with your code, and that is can be
safely merged into the main branch. The extent of this review can vary
from one project to another. For example, many
projects won't allow you to contribute code that breaks any of the automated
tests that already exist for that project, and some may withhold approval
if your code doesn't follow a project's style guide.

The way we would do this on GitHub is by creating a new branch from the main
branch, doing our work in that branch, and then submitting a *pull request*,
requesting that the code in our branch be merged into the main branch. In this
tutorial, you will create a simple pull request where you will solicit a cursory
review by another student and by your team's senior developer.

To do this we will use the following repository:

https://github.com/uchicago-cmsc22000/2021-pr-tutorial

This repository has a single ``README.md`` file, and the goal of this tutorial
will be to add your name to that file by using a pull request. Take into
account that we've set up this repository so that the ``main`` branch
will be protected: you can create other branches and push those branches
to the repository, but you cannot directly push or merge to the ``main`` branch.

So, go ahead and clone this repository. You will be creating a branch
to add your name to ``README.md``... but don’t do it yet! Before you do
this, let’s take a minute to talk about naming conventions.

If everyone named their branch something like ``update-readme`` or
``add-name``, we’d have lots of branches with the same name. In large
collaborative projects, it’s common to prefix branch names with your own
first name, to avoid collisions like this. We will adopt a similar
convention in this class, except we will use feature names. So, if you
are working on adding sound support to chiventure, you branches would be
called ``sound/fix-mp3-bug``, ``sound/add-midi-support``, etc.

For this sample repo, we’ll just use your CNetID. So, if your CNetID is
``jdoe``, you should name your branch ``jdoe/add-to-names`` or
``jdoe/update-readme`` or similar. It doesn’t really matter what the
name of the branch is, so long as it starts with ``jdoe/``.

You should now do the following: (if you're unclear on how to perform
some of these steps, you may want to review the sections on branching
from `Homework #1 <../hw/hw1.html>`__)

1. Create and check out a branch called ``CNETID/add-to-names`` (or
   similar, as long as it starts with your CNetID)
2. Edit the ``README.md`` file to add your name, and create a commit
   with that change.
3. Push your branch to GitHub. Git may helpfully provide you with a URL
   to create a pull request; ignore this for now, although you’re
   welcome to use that direct URL in the future.

Now, go to the repository on GitHub
(https://github.com/uchicago-cmsc22000/2021-pr-tutorial). It should actually show
that you’ve pushed a branch recently, and there will be a green “Compare
& pull request” button. Click on this button to create a pull request.
If you don’t see a “Compare & pull request” button, you can also click
on the “New pull request” button that appears next to the pull-down list
of branches; you will then have to manually specify the branch you’re
merging before you can create the pull request (the “base branch” would
be ``main`` and the “compare branch” would be ``CNETID/add-to-names``)

After clicking “Compare & pull request”, or after clicking “New pull
request” and selecting the branch you want to merge, you will be able to
specify a title and a summary for the pull request. For example, in this
case, the title could be “Adding my name to README” and the summary
could be “I am adding my name to the README as part of the Pull Request tutorial”.

As in a regular pull request, we’re going to request that someone else
review your pull request before it can be merged into ``main``. To do
this, select another student on your team under “Reviewers”, as well as
your senior developer.

Finally, click “Create pull request”. You’ve marked your code for
review! Once it has been reviewed, your senior developer will merge
your request into ``main``.

Note: if someone specifies you as a reviewer for this pull request,
this is an opportunity to familiarize yourself with what the interface
looks like from a reviewer's perspective. Leave a comment in the pull
request saying something like "Looks good to me!" and approve the request.

