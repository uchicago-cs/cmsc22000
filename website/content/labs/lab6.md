---
title: "Lab 6: Continuous Integration"
date: 2018-01-26
publishdate: 2018-01-26
draft: false
---

**Due:** Wednesday, May 20th, 8pm

Continuous Integration, or CI, is the practice of frequently merging developers’ work into a mainline branch in a version control system like Git. CI almost always involves running an extensive set of test cases every time such a merge happens, or even every time new code is committed to the repository (not just on the mainline branch, but also on other branches). Thus many version control systems facilitate CI by providing mechanisms to trigger certain actions when code is pushed to a repository.

In this lab, we are going to explore the CI features available through GitHub and, more specifically, through the [Travis CI](https://travis-ci.org/) platform. Throughout the lab, we will refer to these CI features as the “CI system”.

## Creating your lab repository

Like previous labs, we will provide you with an  *invitation URL* that will allow you sign up for the lab assignment on GitHub, and which will result in the creation of a repository called `2020-lab6-GITHUB_USERNAME` inside our `cmsc22000-labs` organization on GitHub. Your repository will be seeded with some files for the lab and, more specifically, will contain the same files we provided for Lab #5 (an implementation of libgeometry).


# Task 1: Building your code with CI

In most CI systems, we will want to specify a series of actions that need to happen automatically whenever any commits are pushed to the repository. For example, we may need to build the code in our repository, and run some tests. These actions are typically referred to as *jobs*. A CI system will keep a record of all the jobs it runs, and will typically notify you if a job fails.

When we push new commits to the repository, this may result in some or all of these jobs being run, which Travis CI refers to as “a build”. This is potentially confusing because, strictly speaking, “building” refers just to building/making your code but, in the context of CI, “a build” usually refers to “all the jobs that are run when you push any new commits to the repository”. 

On Travis, the jobs are specified in a text file named `.travis.yml` which is placed in the root of your repository. 

{{% note %}}
The `.travis.yml` is a YAML file. YAML is a text-based file format that is commonly used for configuration files. We’ll be showing the syntax you need in this lab, but if you are curious there is a ton of documentation out there on it. Fun fact, it’s short for “YAML Ain't Markup Language”)
{{% /note %}}

You can find a lot of details about the format of the `.travis.yml` in the Travis CI Documentation. We'll start by looking at a simple Travis CI file:

    language: c
    
    before_install:
        - sudo add-apt-repository -y ppa:snaipewastaken/ppa
        - sudo apt-get update
    
    install:
        - sudo apt-get install -y criterion criterion-dev
    
    before_script:
        - cd libgeometry
        - make clean
    
    script: 
        - make all
        - make tests
        - tests/test-libgeometry

By default, a Travis CI file will specify a single job that is run whenever we push any code to our repository (later on we'll see how to specify multiple jobs). This job is divided into several *phases* that happen in sequence; Travis CI only supports a specific set of phases, and in this example we are only specifying what happens in four of them: `before_install`, `install`, `before_script`, and `script` (the `language` option is just a global option that tells Travis this is a C project, which will ensure that Travis builds our code in an environment with a C compiler)

Here is what is happening in each of the phases:

- `before_install`: Because libgeometry depends on the Criterion library, we need to make sure it is installed before we try to build our code. Travis CI uses an Ubuntu build environment by default, and these commands tell Ubuntu where to find the Criterion library.
- `install`: In this phase, we actually install the Criterion libraries.
- `before_script`: In this phase, we run any commands necessary before the actual build. In this case, since Travis runs all commands from the root of your repository, we need to `cd` into `libgeometry` before we can run `make`. We also run `make clean`, which is considered good practice in a build job, as it guarantees that your build starts from a clean slate (and can help you detect whether you’ve inadvertently committed object files or binary files that make your build work only when those files are already present)
- `script`: This is the phase where we actually build our code and run the tests.

Take into account that we could've also run all the commands inside the `script` phase: 

    language: c
    
    script: 
        - sudo add-apt-repository -y ppa:snaipewastaken/ppa
        - sudo apt-get update
        - sudo apt-get install -y criterion criterion-dev
        - cd libgeometry
        - make clean
        - make all
        - make tests
        - tests/test-libgeometry

However, it is considered good practice to separate these commands into their appropriate phases. In more complex builds, it can be useful to know exactly what phase of the build failed.

Now, do the following:

Commit the `.gitlab-ci.yml` to your repository and push it. Now, go to the following URL:

      https://travis-ci.com/github/cmsc22000-labs/2020-lab6-GITHUB_USERNAME
      
Where `GITHUB_USERNAME` should be replaced with your GitHub username. This page will show you the state of your build. You can also access this page by going here: https://travis-ci.com/github/cmsc22000-labs/ (and clicking on the entry corresponsing to your repository)
  
Please note that it can sometimes take a few minutes for the build to start (this page will automatically update as your build progresses). After a while, the "Current" tab should show a successful build like this:
  
   ![build](/cmsc22000/img/build.png)
   
The "#1" in the screenshot is the build number (this number may be different if you had to make multiple attempts to get a successful build). Click on the build number; this will take you to a page with a URL like this:
  
    https://travis-ci.com/github/cmsc22000-labs/2020-lab6-GITHUB_USERNAME/builds/XXXXXXXXX

Where `XXXXXXXXX` will be a number. This is the URL for this particular build; as you make more builds in the lab, we will be asking you to provide the URL of those builds. 

Take into account that you can also access your latest build (even if it's in progress) through GitHub. In your repository, there will be a small icon (a green check mark for a successful build, a yellow circle for a build in progress, and a red X for a failed build) in the top right of your list of files. If you click on it, it will show more information about the build:

   ![github-travis](/cmsc22000/img/github-travis.png)

If you click on "Details", it will take you to a page on GitHub with more details about the build. From that page, you can click on the link "The build", which will take you to the Travis CI page for that build. Make sure to do this so you are familiar with how to navigate through GitHub's and Travis's build pages.

Now, do the following:

* [10 points] Take the URL of the build you just produced, and paste it into Gradescope (under "Task 1: Successful build")

* [10 points] Make a change to the libgeometry code that will prevent it from compiling. Commit that change; your build should eventually fail. Paste the URL of the failed build on Gradescope (under "Task 1: Failed build (compiling)")

* [10 points] Fix the change you made, and make another change that will make the tests fail. Commit that change; your build should eventually fail. Paste the URL of the failed build on Gradescope (under "Task 1: Failed build (tests)")


# Task 2: Adding jobs

As we mentioned previously, CI typically involves running tests every time we push changes to the repository. This means that, besides building our code, we also want tests to run automatically. For the simple hello program, we’ve included a very simple test: we simply run the program (using the `tests` target in the Makefile). While this doesn’t guarantee that the program prints the correct output, it will at least verify that the program runs without errors.

So, let’s add a job to the `.gitlab-ci.yml` file to run the tests:

    hello:test:
        stage: test
        script:
          - make -C labs/lab6/hello clean tests
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



# Task 3: Job matrices

If you look at the terminal output of the `hello:test` and `libgeometry:test` jobs, you’ll notice that these jobs actually repeat the work from the build jobs: they build the `hello` binary and the `libgeometry.so` library from scratch. This seems wasteful, and we would ideally want to simply use the result of the build job in the subsequent test job. We can do this by using *artifacts* and *dependencies*.

By default, all files produced by a job are deleted once the job ends. However, we can tell the CI system to store one or more files for future use. These are called the artifacts of the job, and they can be downloaded after a job runs, or can be passed from one job to another.

For example, we can tell GitLab to keep the `hello` binary after the `hello:build` job runs:

    hello:build:
        stage: build
        script:
          - make -C labs/lab6/hello clean all
        only: 
          - master
        artifacts:
          expire_in: 1 hour
          paths:
            - labs/lab6/hello/hello

Notice how we specify that we want to artifact to expire in one hour, since we’re only going to use it in the subsequent `hello:test` job.

To make sure the `hello:test` job receives that artifact, we need to define a dependency between the jobs:

    hello:test:
        stage: test
        script:
          - labs/lab6/hello/hello
        only: 
          - master
        dependencies:
          - hello:build

Now, do the following:

* [5 points] Commit the updated `.gitlab-ci.yml` file, and copy-paste the URL of the resulting “passed” pipeline to the `tasks.txt` file. Notice how the `hello:test` task no longer builds the `hello` binary from scratch and, instead, downloads the artifact from the `hello:build` job. You should also be able to click on “Pipelines” -> “Jobs” and on a download icon next to the passed `hello:build` job to download the `hello` binary (you don’t need to do anything with it, just check you’re able to download it)
* [20 points] Edit the `libgeometry:build` job so it will build both the libgeometry library and the tests. Next, edit the “libgeometry:tests” job so that it only runs the tests, using both the `libgeometry.so` file and the `tests/test-libgeometry` file from `libgeometry:build`. Copy-paste the URL of the resulting “passed” pipeline to the `tasks.txt` file.





## Submitting your lab

Please note that you will not be submitting your code through Gradescope. Instead, make sure that you have provided the URLs to your CI builds through Gradescope. That said, we still need you to push your code in case we need to look at any of your code (but we will not be grading the code itself).

