---
title: "Lab 6: Continuous Integration"
date: 2018-01-26
publishdate: 2018-01-26
---

**Due:** Thursday, May 10th, 4pm

Continuous Integration, or CI, is the practice of frequently merging developers’ work into a mainline branch in a version control system like Git. CI almost always involves running an extensive set of test cases every time such a merge happens, or even every time new code is committed to the repository (not just on the mainline branch, but also on other branches). Thus many version control systems facilitate CI by providing mechanisms to trigger certain actions when code is pushed to a repository.

In this lab, we are going to explore the CI features of GitLab, and then you will apply what you’ve learned to see how CI is done on GitHub. Throughout the lab, we will refer to these CI features as the “CI system”.

# Task 0: Pulling from upstream
(0 points)

You should already have the “upstream” remote set up in your repository. If you do, simply run

    $ git pull upstream master

to get the files for this lab. If you don’t have the “upstream” remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).


# Task 1: Building your code with CI

In most CI systems, we will want to specify a series of actions that need to happen automatically whenever any commits are pushed to the repository. For example, we may need to build the code in our repository, and run some tests. These actions are typically referred to as *jobs*, and you can often specify dependencies between jobs (e.g., the tests can be configured to run only if a project is built correctly). A CI system will keep a record of all the jobs it runs, and will typically notify you if a job fails.

When we push new commits to the repository, this may result in some or all of these jobs being run. GitLab refers to these jobs as a *pipeline*, although you will often hear these jobs referred to as  “a build”. This is potentially confusing because, strictly speaking, “building” refers just to building/making your code but, in the context of CI, “a build” usually refers to “all the jobs that are run when you push any new commits to the repository”. The term “pipeline”, although unique to GitLab, is more representative of what happens when you push new commits: a pipeline of jobs is run.

On GitLab, the jobs in a pipeline are specified in a text file named `.gitlab-ci.yml` which is placed in the root of your repository. So even though your repository has several labX subdirectories, the `.gitlab-ci.yml` file will go in the root of the repository, not inside any of your lab directories.

(Aside: the `.gitlab-ci.yml` is a YAML file. YAML is a text-based file format that is commonly used for configuration files. We’ll be showing the syntax you need in this lab, but if you are curious there is a ton of documentation out there on it. Fun fact, it’s short for “YAML Ain't Markup Language”)

In this file, we need to create a list of jobs. The contents of the file will look something like this:

    job1:
        option: value
        option: value
        …

    job2:
        option: value
        option: value
        …

    …

There is no limit to the number of jobs you can have. Each job must have a unique name, and you can name it whatever you want (but ideally it is informative for what the job does. So for example, if I have a job that tests libgeometry, you could name it `libgeometry:tests`).

Each job has a number of options you can specify. Let’s explore some of these options by seeing a very simple `.gitlab-ci.yml` file:

    hello:build:
        stage: build
        script:
          - make -C lab6/hello/ clean all
        only: 
          - master

This file defines a single job called `hello:build` that builds the simple “Hello, world!” program in `lab6/hello/`. 

Be careful with the colon after `hello:build`! That is the colon that goes after the name of the job (and is not part of the job name itself).

The options we’ve specified in the job are the following:

`stage` defines the job stage. The possible stages are `build`, `test`, and `deploy`. These are the stages that are part of the software development process! We have already covered building and testing in previous labs, and we will cover deployment next week. Using `stage` lets you group jobs into different stages, and jobs that are part of the same stage are executed in parallel. If `stage` isn’t specified, it is set to `test` by default.

`script` specifies the list of commands that will be run as part of this job. Think of this as the commands you would type into the shell if you had to build this program. Note that, in this case, we’re only running one command, but we could specify multiple commands to run in sequence like this:
  
    script:
       - foo
       - bar
       - baz
  
Take into account that the commands are run from the root of your repository, so we use the `-C lab6/hello/` option to tell `make` to run the Makefile in that directory. We also specified that `make` should run `clean` followed by `all`; this is considered good practice in a build job, as it guarantees that your build starts from a clean slate (and can help you detect whether you’ve inadvertently committed object files or binary files that make your build work only when those files are already present)

`only` specifies the name of the branches where new commits will trigger the running fo the job. In this case, we only want this job to be run if we push anything new to `master`. That means we could create another branch where we allow ourselves to push potentially broken code, and only run the CI jobs when that branch is merged to `master`.

There are actually many other options you can set in `.gitlab-ci.yml`. We will only cover a few others in this lab, but you can see the complete reference here: https://docs.gitlab.com/ee/ci/yaml/

Now, do the following:

* [0 points] Commit the `.gitlab-ci.yml` to your repository and push it.

* [5 points] Go to your repository on the GitLab server (i.e., https://mit.cs.uchicago.edu/cmsc22000-spr-18/CNETID, where CNETID should be replaced by your CNetID). On the left sidebar, click on “Pipelines”. This will show you the pipelines that have been run in your repository. You should see a “passed” pipeline (if you do not, please ask for help). Click on either “passed” or the pipeline number. This will take you to a page with more details about the pipeline. Copy the URL of that page and paste it in the `tasks.txt` file in `lab6/`. This page shows more details about the jobs that ran in that pipeline. In this case, we have only one job: `hello:build`. If you click on it, you’ll be able to see the terminal output from the job (which was run on a special server known as the build server)

* [5 points] Make a change to the `hello.c` file that will make it not build. Commit and push this change to the repository. This will result in a failed pipeline in the “Pipelines” page; copy-paste the URL of the failed pipeline into the `tasks.txt` file. Before moving on to the next task, undo the change and verify that pushing the code results in a “passed” pipeline.

* [15 points] Add a job called `libgeometry:build` to build the libgeometry library contained in `lab6/libgeometry`. Push your updated `.gitlab-ci.yml` file, and copy-paste the URL of the resulting “passed” pipeline into the `tasks.txt` file. Notice how this pipeline now has two jobs in it.

Note: Before committing your `.gitlab-ci.yml` file, you can check that the format of the file is correct by going to https://mit.cs.uchicago.edu/ci/lint. This will allow you to copy-paste your `.gitlab-ci.yml` file and check it for syntax errors.



# Task 2: Adding tests

As we mentioned previously, CI typically involves running tests every time we push changes to the repository. This means that, besides building our code, we also want tests to run automatically. For the simple hello program, we’ve included a very simple test: we simply run the program (using the `tests` target in the Makefile). While this doesn’t guarantee that the program prints the correct output, it will at least verify that the program runs without errors.

So, let’s add a job to the `.gitlab-ci.yml` file to run the tests:

    hello:test:
        stage: test
        script:
          - make -C lab6/hello clean tests
        only: 
          - master

Notice how the stage is `test`. This means that GitLab will not run this job unless all the jobs in the `build` stage succeed.

Now, do the following:

* [5 points] Commit the updated `.gitlab-ci.yml` file, and copy-paste the URL of the resulting “passed” pipeline to the `tasks.txt` file. Notice how GitLab now shows a `hello:test` job that depends on the build jobs. If you click on the `hello:test` job and look at its terminal output, you will see the output of running `hello`.
* [10 points] Edit `hello.c` to force it to crash (e.g., dereference a NULL pointer). This will still allow `hello.c` to compile, but will make the tests fail. Commit and push this change, and copy-paste the URL of the resulting “failed” pipeline to the `tasks.txt` file. Notice how the build jobs ran successfully, but the pipeline failed because one of the jobs (the `hello:test` job) failed. Before moving on to the next test, undo this change and make sure it results in a “passed” pipeline.
* [25 points] Add a `libgeometry:test` job to the `.gitlab-ci.yml` file to build and run the tests. This job should be in the `test` stage, even though it involves building code (in this case, building the tests). Furthermore, your `script` option will now have more than one entry: one for building the tests, and one or more to run them. Once you’re done, copy-paste the URL of the “passed” pipeline to the tasks.txt file.

Careful: *Figuring out the commands for running the libgeometry tests is non-trivial!* Here are two hints: 
* You should first figure out the exact commands you need to run from the root of your repository to successfully run the tests. **DO NOT** figure out the commands by pushing a new commit (and triggering a new pipeline) for every command you try to run. If you figure out the commands from the root of your repository, you should be able to then simply copy/paste those commands into your GitLab CI file.
* Remember that, if you run `tests/test-libgeometry` from inside the `libgeometry` directory, it will work. So, you can take two approaches: either make sure you’re inside the libgeometry directory before running the tests, or tell the tests where they should look for the libgeometry library (this can be done using an environment variable called `LD_LIBRARY_PATH`) 



# Task 3: Artifacts and dependencies

If you look at the terminal output of the `hello:test` and `libgeometry:test` jobs, you’ll notice that these jobs actually repeat the work from the build jobs: they build the `hello` binary and the `libgeometry.so` library from scratch. This seems wasteful, and we would ideally want to simply use the result of the build job in the subsequent test job. We can do this by using *artifacts* and *dependencies*.

By default, all files produced by a job are deleted once the job ends. However, we can tell the CI system to store one or more files for future use. These are called the artifacts of the job, and they can be downloaded after a job runs, or can be passed from one job to another.

For example, we can tell GitLab to keep the `hello` binary after the `hello:build` job runs:

    hello:build:
        stage: build
        script:
          - make -C lab6/hello clean all
        only: 
          - master
        artifacts:
          expire_in: 1 hour
          paths:
            - lab6/hello/hello

Notice how we specify that we want to artifact to expire in one hour, since we’re only going to use it in the subsequent `hello:test` job.

To make sure the `hello:test` job receives that artifact, we need to define a dependency between the jobs:

    hello:test:
        stage: test
        script:
          - lab6/hello/hello
        only: 
          - master
        dependencies:
          - hello:build

Now, do the following:

* [5 points] Commit the updated `.gitlab-ci.yml` file, and copy-paste the URL of the resulting “passed” pipeline to the `tasks.txt` file. Notice how the `hello:test` task no longer builds the `hello` binary from scratch and, instead, downloads the artifact from the `hello:build` job. You should also be able to click on “Pipelines” -> “Jobs” and on a download icon next to the passed `hello:build` job to download the `hello` binary (you don’t need to do anything with it, just check you’re able to download it)
* [20 points] Edit the `libgeometry:build` job so it will build both the libgeometry library and the tests. Next, edit the “libgeometry:tests” job so that it only runs the tests, using both the `libgeometry.so` file and the `tests/test-libgeometry` file from `libgeometry:build`. Copy-paste the URL of the resulting “passed” pipeline to the `tasks.txt` file.


# Task 4: GitHub CI

[10 points]

Most version control systems include or integrate well with CI systems, and GitHub is no exception. It actually works with a number of different [CI systems](https://github.com/marketplace/category/continuous-integration), although a popular option is [Travis CI](https://travis-ci.org/)

In this final task, you will take what you've learned about CI on GitLab, and see how it translates to a different context. So, this task is more about how to familiarize yourself with a new system (and knowing how to read documentation), than about CI specifics. In fact, all we want you to do in this task is the following:

* Create a repository under your personal GitHub account called `cs220-lab6`.
* Add the `hello/` files to the repository.
* Setup Travis CI on your repository to build the `hello` binary and run the `hello` program.

In the `tasks.txt` file, you must provide the following:

* The URL of a successful build of your repository.
* A copy of your `.travis.yml` file.
* Describe three ways in which GitLab CI and Travis CI are different.
* List any resources you consulted (other than the official documentation from GitHub or Travis CI)





