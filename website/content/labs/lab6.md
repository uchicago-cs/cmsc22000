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

We'll start by looking at a simple Travis CI file:

    os: linux
    
    dist: xenial
    
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

Save this as a `.travis.yml` file in the root of your repository; commit it, but don't push it just yet.

{{% note %}}
Files that start with a period, like `.travis.yml`, are hidden by default on a UNIX system. This means the file won't appear if you use `ls` from the terminal; you will need to include the `-a` option to be able to see it (i.e., `ls -a` instead of `ls`, and `ls -al` instead of `ls -l`). If you are using a graphical file browser, you may need to select a "Show Hidden Files" option somewhere to be able to see the file.
{{% /note %}}

By default, a Travis CI file will specify a single job that is run whenever we push any code to our repository (later on we'll see how to specify multiple jobs). In this file, we specify some options that will affect how the job is run:

- `os: linux` specifies that the job should be run on a Linux environment.
- `dist: xenial` specifies that it will specifically be run on an Ubuntu 16.04 ("Xenial") environment
- `language: c` specifies that we are building a C project, so Travis knows to use an environment that includes a C compiler.

The remaining options specify the *phases* of the job. A job is divided several *phases* that happen in sequence; Travis CI only supports a specific set of phases, and in this example we are only specifying what happens in four of them: `before_install`, `install`, `before_script`, and `script`.

Here is what is happening in each of the phases:

- `before_install`: Because libgeometry depends on the Criterion library, we need to make sure it is installed before we try to build our code. Travis CI uses an Ubuntu build environment by default, and these commands tell Ubuntu where to find the Criterion library.
- `install`: In this phase, we actually install the Criterion libraries.
- `before_script`: In this phase, we run any commands necessary before the actual build. In this case, since Travis runs all commands from the root of your repository, we need to `cd` into `libgeometry` before we can run `make`. We also run `make clean`, which is considered good practice in a build job, as it guarantees that your build starts from a clean slate (and can help you detect whether you’ve inadvertently committed object files or binary files that make your build work only when those files are already present)
- `script`: This is the phase where we actually build our code and run the tests.

{{% note %}}
You can find more information about how to specify a Travis CI build in the [Travis CI Documentation](https://docs.travis-ci.com/), and a specification of their configuration file format in the [Travis CI Build Config Reference](https://config.travis-ci.com/). You don't need to refer to these resources right now, but may need to consult them later in the lab.
{{% /note %}}

Take into account that we could've also run all the commands inside the `script` phase: 

    os: linux
    
    dist: xenial
    
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

Go ahead and push the commit you created previously. GitHub (and Travis CI) will detect that your repository has a `.travis.yml` file, and will trigger a build (following the phases specified in the `.travis.yml` file). You can see the status of the build in the following URL:

      https://travis-ci.com/github/cmsc22000-labs/2020-lab6-GITHUB_USERNAME
      
Where `GITHUB_USERNAME` should be replaced with your GitHub username. If you see a message saying "We couldn't display the repository cmsc22000-labs/2020-lab6-GITHUB_USERNAME", you may need to follow the prompt to sign into Travis with your GitHub credentials (once you do, you should be able to see the build). You can also access the build by going here: https://travis-ci.com/github/cmsc22000-labs/ (and clicking on the entry corresponsing to your repository) 
  
Please note that it can sometimes take a few minutes for the build to start (the page will automatically update as your build progresses). After a while, the "Current" tab should show a successful build like this:
  
   ![build](/cmsc22000/img/build.png)   
   
{{% note %}}
If the build shows up as "errored", with errors that relate specifically to `git clone`, this just means that GitHub is limiting the number of requests from Travis. Wait a minute or two and try pressing the "Restart job" button.
{{% /note %}}   
   
The "#1" in the screenshot is the build number (this number may be different if you had to make multiple attempts to get a successful build). Click on the build number; this will take you to a page with a URL like this:
  
    https://travis-ci.com/github/cmsc22000-labs/2020-lab6-GITHUB_USERNAME/builds/XXXXXXXXX

Where `XXXXXXXXX` will be a number. This is the URL for this particular build; as you make more builds in the lab, we will be asking you to provide the URL of those builds. 

Take into account that you can also access your latest build (even if it's in progress) through GitHub. In your repository, there will be a small icon (a green check mark for a successful build, a yellow circle for a build in progress, and a red X for a failed build) in the top right of your list of files. If you click on it, it will show more information about the build:

   ![github-travis](/cmsc22000/img/github-travis.png)

If you click on "Details", it will take you to a page on GitHub with more details about the build. From that page, you can click on the link "The build", which will take you to the Travis CI page for that build. Make sure to do this so you are familiar with how to navigate through GitHub's and Travis's build pages.

Now, do the following:

* [10 points] Take the URL of the build you just produced, and paste it into Gradescope (under "Task 1: Successful build")

* [10 points] Make a change to the libgeometry code that will prevent it from compiling. Commit and push that change; your build should eventually fail. Paste the URL of the failed build on Gradescope (under "Task 1: Failed build (compiling)")

* [10 points] Fix the change you made, and make another change that will make the tests fail. Commit and push that change; your build should eventually fail. Paste the URL of the failed build on Gradescope (under "Task 1: Failed build (tests)")

Before moving on to the next task, make sure to fix the change you just made. Your build should succeed before moving on to the next tasks.

# Task 2: Multiple jobs

In the previous task we saw that Travis CI can build our code and run the tests, and alert us to any issues when doing so. However, our job was running specifically in an Ubuntu 16.04 environment. What if our code doesn't compile in other environments? CI systems can also help us with this, as they often provide mechanisms to easily build our code in multiple environments. For example, we may want to build our code in multiple Ubuntu versions, or using different compilers.

In Travis CI, we have the ability to specify build options that will automatically generate additional jobs. For example, add the following to your `.travis.yml` file:

    compiler:
      - gcc
      - clang
 
 This tells Travis CI that we want to run the build with two compilers: `gcc` and `clang`. If you commit and push this updated file, this will produce a build with two jobs:
 
   ![compilers-build](/cmsc22000/img/compilers-build.png)
 
 You can click on the individual jobs to see the full job log, showing the exact commands that were run in each job. You'll actually notice that the clang job seems to still be running gcc. Don't worry about this for now (we'll revisit this in Task 3)
 
* [10 points] Take the URL of the build you just produced, and paste it into Gradescope (under "Task 2: Multiple compilers").

Travis CI actually provides two mechanisms to specify multiple jobs:

**Using a "matrix expansion" option**. There are certain options in Travis, such as the `compiler` option that will automatically result in generating multiple jobs. Another such option is the `arch` option (for specifying the processor architecture our build will run on). For example, if we specified the following options:
 
         arch:
           - amd64
           - arm64
         
         compiler:
           - gcc
           - clang
       
 The "build matrix" would include every combination of these options:
   
   - GCC on an AMD64 processor
   - clang on an AMD64 processor
   - GCC on an ARM64 processor
   - clang on an ARM64 processor
    
Modify your `.travis.yml` file to also include the `arch` option as shown above (i.e., you should still keep the `compiler` option you added previously). Commit and push the updated file. Once the build completes, you should see four jobs in the build. By the way, the ARM64 processor architecture is commonly used in smartphones, which means that we have effortlessly verified that libgeometry will build and run correctly on most smartphones!
    
* [10 points] Take the URL of the build you just produced, and paste it into Gradescope (under "Task 2: Matrix expansion").

**Listing individual configurations**: You can also just list the exact configurations you want to use using the `jobs` option. For example, this is how you would specify three jobs that compile your code in three different Ubuntu distributions (18.04 "Bionic", 16.04 "Xenial, and 14.04 "Trusty"), all with GCC:

    jobs:
      include:
      - os: linux
        dist: bionic
        compiler: gcc
      - os: linux
        dist: xenial
        compiler: gcc
      - os: linux
        dist: trusty
        compiler: gcc

Remove the top-level `os`, `dist`, `compiler`, and `arch` options from your `.travis.yml` file, and replace it with the above `jobs` option. Commit and push the file; once the build completes, you should see it has three jobs.

As it turns out, the job that ran on Ubuntu 14.04 will fail. You do not need to fix it, but it's worth noting why it failed: the version of GCC shipped with that version of Ubuntu does not use, by default, the C99 version of the C standard (which later versions of GCC do use by default). To get the code to build on Ubuntu 14.04, we would have to explicitly pass the `-std=c99` option to GCC to make sure it compiles the code using the C99 version of the C standard.

Now imagine that we were developing software that was still required to run on old Ubuntu 14.04 systems (which none of our developers are likely to be using to write and test their code). Using a CI system allows us to uncover these kind of issues early on, by easily testing our code in multiple systems (including old legacy systems) so we can uncover issues like these.

* [10 points] Take the URL of the build you just produced, and paste it into Gradescope (under "Task 2: Individual job configurations"). It's ok if the build contains the failed Ubuntu 14.04 job; you are not expected to fix it.



# Task 3: More build configurations

In the previous tasks, we've given you the exact configurations you had to use (and asked for the build URLs to make sure you actually worked through the instructions in the lab). In this task, it's time for you to figure out how to write certain build configurations on your own by reading the Travis CI documentation. More specifically, you will want to consult the [Travis CI User Documentation](https://docs.travis-ci.com/) and the [Travis CI Build Config Reference](https://config.travis-ci.com/). Travis CI also provides a [Config Explorer](https://config.travis-ci.com/explore) that can allow you to validate that your `.travis.yml` is correct before you commit/push it and trigger a build.

* [10 points] In Task 2, we saw that using the `compiler` option resulted in the `clang` build still using GCC. There is something you will need to fix in your `Makefile` Hint: The Travis CI documentation includes language-specific documentation that explains what certain options, like the `compiler` option, do. You may want to look at that specifically.

  Use the `compiler` option to create a build with two jobs (one with GCC and one with clang), and make sure that the clang one is actually using clang (by looking at the output of the Make commands in the "Job log"). Take the URL of the build you just produced, and paste it into Gradescope (under "Task 3: GCC vs clang"). You must also explain what you did to ensure the clang job used clang.
  
  Note: If you end up with more than two jobs, make sure you've removed any other option that would result in additional jobs being launched.

* [10 + 10 points] Using matrix expansion options *only*, generate a build with four configurations:

  - GCC on Ubuntu 18.04
  - clang on Ubuntu 18.04
  - GCC on Mac OS X
  - clang on Mac OS X
  
  You will get 10 points just for producing the build with the correct four jobs. To get the remaining 10 points, you will need to modify your `.travis.yml` file further to get the code to build correctly in a Mac OS X environment. 

  Hint: as you'll discover fairly quickly, Mac OS X doesn't include the `apt` command used in Ubuntu systems, and which we rely on to install the Criterion library. Installing *dependencies* can be tricky when combining multiple different environment, so you may focus on the part of the Travis CI documentation that focuses on that.
  
   Take the URL of the build you just produced, and paste it into Gradescope (under "Task 3: Ubuntu and Mac OS X"). If you got the code to build in a Mac OS X environment, you must also explain how you accomplished this.
   
 * [10 points] It turns out that, in a Mac environment, running `gcc` just results in a call to clang. So, it seems a bit redundant to run the two Mac jobs in the previous build (which will both end up using clang). Figure out a way to *exclude* the Mac+GCC job from the build. Note: You will not get credit if you simply write out the three job configurations. You must instead continue to use matrix expansion, but figure out a way to exclude one specific configuration.

   Take the URL of the build you just produced, and paste it into Gradescope (under "Task 3: Excluding a job"). 


## Submitting your lab

Please note that you will not be submitting your code through Gradescope. Instead, make sure that you have provided the URLs to your CI builds through Gradescope. That said, we still need you to push your code in case we need to look at any of your code (but we will not be grading the code itself).

