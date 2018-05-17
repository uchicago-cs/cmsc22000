---
title: "Lab 8: More CI and Deployment"
date: 2018-01-26
publishdate: 2018-01-26
---

**Due:** Thursday, May 24th, 4pm

In this lab, we will continue to explore concepts related to Continuous Integration and Deployment. The lab is divided into two main parts: one where we will see how we can use Docker containers as part of a CI build, and one where we will expand the deployment pipeline we saw in our previous lab.


# Part I: Using Containers in CI

It is often necessary for a CI build to use a specific software environment to run a series of tests. For example, we may need some libraries installed before we can run the tests or, in the case of the class project, we may need a Redis server that we can run some of our tests on.

Most CI systems allow you to install software before the CI jobs are run. For example, Travis includes an explicit [install step](https://docs.travis-ci.com/user/customizing-the-build#The-Build-Lifecycle). However, installing and configuring a complex piece of software like Redis through this mechanism can be cumbersome.

An alternative approach is to use _containers_, a sort of lightweight virtual machine that provides a specific software environment we need. Unlike virtual machines, containers are typically used to package a specific piece of software, instead of providing a full OS environment (although this is also possible with containers)

For example, a Redis container would include a Redis server and, by default, running the container would immediately start that Redis server, instead of taking us to a UNIX shell where we have to run the Redis serve ourselves. So, if we wanted to run Redis during a CI build, all we would need to do is download a Redis _container image_, and run that container during the CI build. A popular container manager is Docker, which we will be using in this lab. Make sure to read their [What is a Container](https://www.docker.com/what-container) page, which provides a more in-depth explanation of what a container is, and how it compares to virtual machines.

## Task 0: Setup
[0 Points]

You should already have the "upstream" remote set up in your repository. If you do, simply run

    $ git pull upstream master

to get the files for this lab. If you don’t have the "upstream" remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).

Next, like we did in the previous lab, you will be forking an existing GitHub repository. We covered forking in the [Advanced Git Lab]({{< relref "advanced-git.md" >}}), so you may want to review that lab if you’re not 100% clear on what a fork is. 

The repository we will be forking is this one: https://github.com/uchicago-cs/cs220-redis-example. Remember that you can fork it by clicking "Fork" in the upper right hand corner.

Once the fork has completed, you can clone it and begin your work. Remember to do this outside of your individual GitLab repository! (i.e., do not run the following command in the same directory that contains your lab1, lab2, etc. directories, or inside the lab8 directory).

    $ git clone https://github.com/[yourusername]/cs220-redis-example.git

Edit your tasks.txt file and include the URL of your forked cs220-redis-example repository on GitHub.

Careful! Remember that your tasks.txt is in your personal repository on GitLab (with all your other lab files). You will only be using that repository to edit your tasks.txt file. The rest of your work will happen on the forked cs220-redis-example repository you just created.

## Task 1: Running Docker in the CS VM [Optional]
[0 Points]

Using Docker requires [root privileges](https://en.wikipedia.org/wiki/Superuser), which you do not have on the CSIL machines. Fortunately, as we’ll see later on, that won’t stop us from running Docker on Travis, but it does mean that you won’t get to use Docker yourself (you’ll simply be instructing Travis to use Docker)

However, it can be helpful to learn the basics of how to use Docker, and you can do so using the [UChicago CS Virtual Machine](https://howto.cs.uchicago.edu/vm:index), where you do have the ability to run commands with root privileges.

Completing this task requires running the VM on your own machine (not on a CSIL machine), so this task is optional and ungraded, but strongly recommended, specially if you’ve already installed the UChicago CS VM.

Once you’ve started the UChicago CS VM, open a terminal. We will first need to install Redis and Docker on the virtual machine. You can install Redis by running the following commands (these instructions are based on the official Redis [installation documentation](https://redis.io/download):

    $ wget http://download.redis.io/redis-stable.tar.gz
    $ tar xzf redis-stable.tar.gz 
    $ cd redis-stable/
    $ make
    $ sudo make install

Notice how that last command is run with "sudo". This basically instructs the operating system to run the command ("make install") with root privileges. You will be asked to enter your password which, on the CS VM, is "uccs" by default. The reason we need to run this command with "sudo" is because it involves installing the Redis libraries and binaries in system-wide locations, which require root privileges to modify.

Next, before installing Docker, we need to make a few minor changes to Ubuntu’s configuration. Click on the Ubuntu icon on the top-left of the screen, and type "Software" in the "Seach your computer" field. One of the applications that will appear is "Software & Updates". Click on it. Then, click on the "Updates" tab and, under "Install updates from:" make sure the following are selected:

* Important security updates
* Recommended updates

Now, go back to the terminal and run the following commands (these are based on the official Docker [installation documentation](https://docs.docker.com/install/linux/docker-ce/ubuntu/):

    $ sudo apt-get update
    $ sudo apt-get install -y apt-transport-https ca-certificates curl software-properties-common
    $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
    $ sudo apt-key fingerprint 0EBFCD88
    $ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
    $ sudo apt-get update
    $ sudo apt-get install -y docker-ce

You can verify that Docker is correctly installed by running this:

    sudo docker run hello-world

This will run a container whose sole purpose is to print out a welcome message. If you do not see a message that starts with "Hello from Docker!", please ask for help.

We can run a Redis container simply by running the following:

    sudo docker run --name redis-server -p 6379:6379 redis

Docker will first download the Redis container image from the [Docker Hub](https://hub.docker.com/_/redis/), and then run it. You should see some output that ends with something like this:

    1:M 17 May 14:04:54.269 * Ready to accept connections

Now, open another terminal and run this:

    redis-cli

This should open up a prompt like this:

    127.0.0.1:6379>

This means that the Redis CLI tool running on your VM has successfully connected to the Redis server running inside the Docker container. However, notice how we’re not running Redis directly on the VM (we installed Redis so we could use the "redis-cli" tool, but we never ran the "redis-server" command on the VM).

You can now try running a few Redis commands from the Redis CLI:

    127.0.0.1:6379> SET foo 42
    OK
    127.0.0.1:6379> GET foo
    "42"
    127.0.0.1:6379> HSET myhash name "Borja"
    (integer) 1
    127.0.0.1:6379> HGET myhash name
    "Borja"
    127.0.0.1:6379> HSET myhash email "borja@cs.uchicago.edu"
    (integer) 1
    127.0.0.1:6379> HKEYS myhash
    1) "name"
    2) "email"

Caveat: We’re running Redis inside a Docker container to demonstrate how Docker works, and because that will be the only way of running Redis on Travis. However, if you plan to use Redis on your VM (e.g., when testing your project), you should just run "redis-server" directly on the VM.

On a separate terminal, you can also try running a few Docker commands:

* To see the list of container images: `sudo docker image list`
* To see the list of running containers: `sudo docker container list`
* To stop the Redis container: `sudo docker container stop redis-server`
* To start the Redis container again: `sudo docker container start -a redis-server`


## Task 2: Git Submodules
[20 points]

Your `cs220-redis-example` has two directories:

* `module/` - This directory contains a Redis module that adds a few extra commands. We will be using just one of them: EXAMPLE.HGETSET, which does an HGET operation followed by an HSET operation. In other words, it gets the value of a key in a hash table (which will be returned by the command), and then sets the value of that key to a new value. Note: this example module is the same example module provided by Redis.
* `tests/` - This directory contains a simple program that uses the hiredis library to connect to a Redis server to test the HGETSET operation.

However, to compile the module we need some files included in the Redis Module SDK (Software Development Kit) available in the following repo: https://github.com/RedisLabs/RedisModulesSDK. To compile the example program, we also need hiredis, which is available in this repository: https://github.com/redis/hiredis

We could, of course, just clone those repositories and copy them into our repository. This is usually a bad idea, because it makes it harder to track updates in the original code. For example, if hiredis releases a new version, we would have to manually copy over their updated version into our repository.

In general, the problem we’re facing is that there is some code produced by a "third party" that we would like to include in our project. In Git this is typically handled by using submodules, which effectively allow us to include "third party repositories" in our own repository (in other version control systems, this is sometimes referred to as "vendor branches").

We can add submodules by using the git submodule command:

    $ git submodule add https://github.com/RedisLabs/RedisModulesSDK.git
    Cloning into '/tmp/cs220-redis-example/RedisModulesSDK'...
    remote: Counting objects: 439, done.
    remote: Total 439 (delta 0), reused 0 (delta 0), pack-reused 439
    Receiving objects: 100% (439/439), 187.79 KiB | 1.59 MiB/s, done.
    Resolving deltas: 100% (258/258), done.

    $ git submodule add https://github.com/redis/hiredis.git
    Cloning into '/tmp/cs220-redis-example/hiredis'...
    remote: Counting objects: 2909, done.
    remote: Compressing objects: 100% (13/13), done.
    remote: Total 2909 (delta 9), reused 19 (delta 9), pack-reused 2887
    Receiving objects: 100% (2909/2909), 866.09 KiB | 5.16 MiB/s, done.
    Resolving deltas: 100% (1791/1791), done.

You’ll notice that two new directories have appeared in your repository, containing the files that are in the original RedisModulesSDK and hiredis repositories.

Before we continue, we need to commit these submodules. If you run git status, you’ll see that GIt is aware that we’ve added two submodules (they are tracked in a special file called `.gitsubmodules`) but they have not yet been committed:

    $ git status
    On branch master
    Your branch is up to date with 'origin/master'.

    Changes to be committed:
      (use "git reset HEAD <file>..." to unstage)

	    new file:   .gitmodules
	    new file:   RedisModulesSDK
	    new file:   hiredis

So, simply run the following:

    $ git commit -m"Added submodules"
    $ git push

If you go to your repo on the GitHub website (https://github.com/[yourusername]/cs220-redis-example) you’ll see that the submodules are shown in a different way: Git is aware that, instead of just copying over the files into your repository, it should simply point to other repositories. 

Now, it will be possible for you to build hiredis, as well as the module and the tests:

$ make -C hiredis/
$ make -C module/
$ make -C tests/

{{% warning %}}
TODO: Warning about cloning a repo with submodules.

    git clone --recursive REPO_URL
    git submodule update --init --recursive

{{% /warning %}}



## Task 3: Using Docker in a Travis build

TODO: The commands below are valid, but this task still needs to be fleshed out.

Testing this module requires running Redis and, specifically, with this new module.

If you setup Docker on the VM, you can run this:

    $ git clone --recursive https://github.com/[yourusername]/cs220-redis-example
    $ cd cs220-redis-example
    $ sudo docker build -t redis-example . 
    $ sudo docker run -d -p 6379:6379 redis-example
    $ sudo docker container list



    $ ./tests/test-hgetset 
    PING: PONG
    HSET: (null)
    HGETSET: Random J. Redisuser
    HGET: Alan T. Foobar


Otherwise, add this .travis.yml file to the repo:

    language: c

    sudo: required

    services:
      - docker

    before_install:
      - docker build -t redis-example . 
      - docker run -d -p 6379:6379 redis-example
      - docker container list

    script:
     - make -C hiredis/
     - make -C tests/
     - ./tests/test-hgetset


# Part II: A complete deployment pipeline

In class, we have discussed that software is rarely deployed directly into production but, instead, follows a _deployment pipeline_. In our previous lab we saw a very basic deployment pipeline: we set up our HelloApp to deploy to Heroku, but only if the CI tests passed. In this lab, we are going to see a more complete deployment pipeline.

As we saw in class, a common pipeline is as follows:

* *Development*, where you are the only one making changes to your codebase.
* *Staging*, where all developers can see your changes, but you have time to catch errors before showing the end-users.
* *Production*, where your app is available to the real world. Usually, the staging app will be promoted to production when it is ready.

In this lab, you’ll create a more complete Heroku pipeline for last week's HelloApp. If you did not successfully complete Lab 7, please ask for help so we can ensure that you're all set up for this week's lab.

Heroku already provides support for creating pipelines, and ours will have three stages:

* *Review*: Similar to a development stage. In Heroku, we can automatically link this stage to our pull requests on GitHub, so we can easily test any changes we are proposing in a pull request.
* *Staging*: We will be using the app you created in Lab 7 as our staging app.
* *Production*: A new production app that is only available if we are satisfied with our staging app.

## Task 1: Create a Pipeline

In this task, you’ll create a new Heroku Pipeline, with your `cnetid-cs220-lab7` application as the staging application. Note that a common convention is for staging applications to have `-staging` as a suffix, but it won't be necessary for you to rename your app in this lab.

To create the pipeline, log into Heroku, and select the app you created in Lab 7. Under the deploy tab, select "Choose a pipeline" and then "Create new pipeline". Name your pipeline `CNETID-pipeline` (where `CNETID` should be replaced with your CNetID). You will also be asked to specify "Choose a stage to add this app to". Make sure that "staging" is selected. Finally, click on "Create pipeline".

You will now be shown the pipeline's configuration (you will also be able to access this page through your dashboard, which will now include a `CNETID-pipeline` pipeline). Notice how there is no production application in your pipeline. In the real world, this would mean that your end users don’t see anything!!!

##  Task 2: Add a production application

In this task, you’ll add a production application to your pipeline. Unlike the app in staging, your production app won't be associated with any specific repo. Instead, once your staging application is good to go, you can *promote* it to be the production application. That means the production application will just take whatever is in the staging app, and will run that in production. Later in the lab you may see Heroku messages that talk about "slugs"; in Heroku parlance, a "slug" is a pre-compiled version of your app that is ready to run. So, when we promote to production, we don't actually rebuild the application; we just take the "slug" that is in staging, and copy it to production.

To add a production application, all you have to do is go to your pipeline and, under "Production", click on "Add app" and then "Create new app". Name the application `CNETID-cs220-prod` (where `CNETID` should be replaced with your CNetID). Notice how, if you try to access your app on Heroku (just go to http://CNETID-cs220-prod.herokuapp.com/), you'll just see a placeholder page, not HelloApp. That's because we haven't promoted our staging app to production yet.


## Task 3: Promoting from staging to production

First, let's make a change to our HelloApp: it's time to upgrade to HelloApp 2.0!
 
* In your forked `cs220-helloapp` repository (which you created in Lab 7), edit `hello/templates/base.html` and change "Helloapp" to "Helloapp 2.0".
* Commit and push this change with the message "Update to 2.0"
* It should not break the tests, so Travis CI should succeed, and from the past lab, your app will automatically deploy.

Now, notice that if you navigate to your staging website (CNETID-cs220-lab7.herokuapp.com) you’ll see your change. But if you navigate to your production website (CNETID-cs220-prod.herokuapp.com), you'll still see a placeholder page. Why is this? 

Changes from staging are *not* automatically deployed to production. This is intentional: we often don’t want things to automatically deploy to production, since we might risk breaking the public-facing version of our app. Pushing code that is broken is known as "breaking the build", and you absolutely don't want that to propagate to production (by the way, if you know anyone who has done a software development internship or works in software development, ask them if they've ever "broken the build"; We guarantee you'll hear some entertaning stories) By having a pipeline, we can ensure that users continuously see our production, without mistakes, and we only update it when we’re absolutely sure. 

So, let's go ahead and promote our staging application to production. You can do this simply by pressing the "Promote to production..." button in the staging app of your pipeline. Once you do this, your staging app (CNETID-cs220-lab7.herokuapp.com) and your production app (CNETID-cs220-prod.herokuapp.com) should look exactly the same.

## Task 4: Create Review Apps - Helloapp 3.0

Currently, in order to make changes to staging, you have to directly modify the master branch of your repo. Can you imagine why this is a bad idea?

In order to show your changes to anyone, you’d have to directly change staging, which isn’t as bad as directly modifying production, but could be embarrassing if you’re trying to get a small change approved and then break everything for every other developer in your team!

The last thing you’ll do is create a review app stage for your pipeline. This way, every pull request submitted to GitHub can be its own app. This lets developers see changes per-pull request. 

To test this, first enable review apps.

* On your pipeline dashboard, select "Enable Review Apps"
* When asked to select a "parent app", just select your CNETID-cs220-lab7 app and click on "Create an app.json file".
* You will be taken to a form. Don't change anything, and just scroll down to the bottom and press "Commit to repo". This will actually add a configuration file called `app.json` to your forked `cs220-helloapp` repository.
* Enable "Create new review apps for new pull requests automatically"
* Enable "Destroy stale review apps automatically"
* Don't worry about the "Review apps may incur dyno and add-on charges." message. We are using the free tier of Heroku, so we won't be charged for anything. If you want to be extra sure, go to https://dashboard.heroku.com/account/billing and make sure there is no credit card on file for your account, and that you have free hours available under "Free Dyno Usage".
* After you enable review apps, you will need to `git pull` on your master branch to make sure it is up to date with the app.json

Now, you’ll create a pull request:

* Create a new branch called `create-version-3` in your forked `cs220-helloapp` repository.
* Edit `hello/templates/base.html` and change "Helloapp 2.0" to "Helloapp 3.0".
* Commit and push the changes with the message "Update to 3.0"
* Notice how the change won't show up on CNETID-cs220-lab7.herokuapp.com, because we haven't pushed the changes to `master`.
* Now, on GitHub, create a new pull request. Make sure your pull request is to merge the `create-version-3` branch to master branch of your forked repo, not the original cs220-helloapp repository you forked from. This means the "base fork" should NOT be "uchicago-cs/cs220-helloapp" (if it is, select "[username]/cs220-helloapp" instead)
* On your heroku Dashboard, you should see your branch show up under "Review Apps"

The build should succeed, so the pull request app should automatically deploy. If it does not, simply click on "Create Review App".

Now, you can check `[cnetid]-cs220-lab7-pr-1.herokuapp.com` and see your pull request app! 

If everything checks out, merge your PR. This should push the changes to staging, since you set up automatic deploys for your app last time (please note that it may take a few minutes for this to happen). Once this succeeds, you can promote your final app to production. 

### Submitting your lab

Before submitting your lab, make sure you update your `lab8/tasks.txt` file with the URLs for the following:

* Your forked `cs220-redis-example` repository on GitHub.
* Your successful build of `cs220-redis-example` on Travis.
* The pull request you created in your forked `cs220-helloapp` repository.
* Your staging HelloApp
* Your production HelloApp

Don't forget to commit and push your changes to the `lab8/tasks.txt` file (remember you can run `git status` to check this). 

Finally, Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab8
    chisubmit student assignment submit lab8

