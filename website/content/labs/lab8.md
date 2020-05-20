---
title: "Lab 8: More CI and Deployment"
date: 2018-01-26
publishdate: 2018-01-26
draft: false
---

**Due:** Wednesday, June 3rd, 8pm

In this lab, we will continue to explore concepts related to Continuous Integration and Deployment. The lab is divided into two main parts: one where we will see how we can use Docker containers as part of a CI build, and one where we will expand the deployment pipeline we saw in our previous lab.


# Part I: Using Containers in CI

It is often necessary for a CI build to use a specific software environment to build code and to run tests. This may be as simple as needing some set of libraries installed before we can build and run your code, or as complex as running some sort of server that our code and tests need to run. 

In this lab, we are going to work through an example that requires a running [Redis](https://redis.io/), a popular data structure store. In a nutshell, Redis is a server that can store a variety of data structures (including lists, hash tables, etc.), and which allows you to manipulate those data structures via an API and a CLI. The API is typically accessed remotely (i.e., the Redis server runs on one machine, and client software running on a different machine accesses the API through a network), which means that testing client software that relies on Redis requires running a Redis server too.

Most CI systems allow you to install software before the CI jobs are run. For example, in the previous lab you saw how to install the Criterion testing library as part of a build (specifying the exact steps to do so under the `before_install` and `install` steps, or using the `addons` portion of the `.travis.yml` file). However, installing and configuring a complex piece of software like Redis through this mechanism can be cumbersome. It can also take a fair amount of time, even if the installation is automated, so it can pay off to simply have a software environment that is ready to go with all the software we need.

One way of doing this is by using _containers_, a sort of lightweight virtual machine that provides a specific software environment we need. Unlike virtual machines, containers are typically used to package a specific piece of software, instead of providing a full OS environment (although this is also possible with containers)

For example, a Redis container would include a Redis server and, by default, running the container would immediately start that Redis server, instead of taking us to a UNIX shell where we have to run the Redis server ourselves. So, if we wanted to run Redis during a CI build, all we would need to do is download a Redis _container image_, and run that container during the CI build. A popular container manager is [Docker](https://www.docker.com/), which we will be using in this lab. Make sure to read their [What is a Container](https://www.docker.com/what-container) page, which provides a more in-depth explanation of what a container is, and how it compares to virtual machines.

## Creating your lab repository

Like previous labs, we will provide you with an  *invitation URL* that will allow you sign up for the lab assignment on GitHub, and which will result in the creation of a repository called `2020-lab8-GITHUB_USERNAME` inside our `cmsc22000-labs` organization on GitHub. Your repository will be seeded with some files for the lab and, more specifically, will contain some code that requires a Redis server to run correctly.

## Task 1: Running Docker in the CS VM
[0 Points]

{{% note %}}
This is an optional task, and you will be able to complete the lab even if you don't do this task. However, even if you do not perform the steps in this task, you should still read through the task, as it provides some additional details on how Redis works.
{{% /note %}}

Using Docker requires [root privileges](https://en.wikipedia.org/wiki/Superuser), which you do not have on the CSIL machines. Fortunately, as we’ll see later on, that won’t stop us from running Docker on Travis, but it does mean that you won’t get to use Docker yourself (you’ll simply be instructing Travis to use Docker)

However, it can be helpful to learn the basics of how to use Docker, and you can do so using the [UChicago CS Virtual Machine](https://howto.cs.uchicago.edu/vm:index), where you do have the ability to run commands with root privileges. In particular, we encourage you to use the VM in [Headless Mode](https://howto.cs.uchicago.edu/vm:headless).

Completing this task requires running the VM on your own machine (not on a CSIL machine), so this task is optional and ungraded, but strongly recommended, specially if you’ve already installed the UChicago CS VM.

Once you’ve started the UChicago CS VM, open a terminal. We will first need to install Redis and Docker on the virtual machine. You can install Redis by running the following commands (these instructions are based on the official Redis [installation documentation](https://redis.io/download)):

```shell
$ wget http://download.redis.io/redis-stable.tar.gz
$ tar xzf redis-stable.tar.gz 
$ cd redis-stable/
$ make
$ sudo make install
```

Notice how that last command is run with `sudo`. This basically instructs the operating system to run the command (`make install`) with root privileges. You will be asked to enter your password which, on the CS VM, is `uccs` by default. The reason we need to run this command with `sudo` is because it involves installing the Redis libraries and binaries in system-wide locations, which require root privileges to modify.

Now, go back to the terminal and run the following commands (these are based on the official Docker [installation documentation](https://docs.docker.com/install/linux/docker-ce/ubuntu/)):

```shell
$ sudo apt update
$ sudo apt install -y apt-transport-https ca-certificates curl software-properties-common gnupg-agent
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
$ sudo apt-key fingerprint 0EBFCD88
$ sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
$ sudo apt-get update
$ sudo apt-get install -y docker-ce
```

You can verify that Docker is correctly installed by running this:

```shell
sudo docker run hello-world
```

This will run a container whose sole purpose is to print out a welcome message. If you do not see a message that starts with "Hello from Docker!", please ask for help.

We can run a Redis container simply by running the following:

```shell
sudo docker run --name redis-server -p 6379:6379 redis
```

Docker will first download the Redis container image from the [Docker Hub](https://hub.docker.com/_/redis/), and then run it. You should see some output that ends with something like this:

```shell
1:M 17 May 14:04:54.269 * Ready to accept connections
```

Now, open another terminal and run this:

```shell
redis-cli
```

This should open up a prompt like this:

```shell
127.0.0.1:6379>
```

This means that the Redis CLI tool running on your VM has successfully connected to the Redis server running inside the Docker container. However, notice how we’re not running Redis directly on the VM (we installed Redis so we could use the `redis-cli` tool, but we never ran the `redis-server` command on the VM).

You can now try running a few Redis commands from the Redis CLI:

```shell
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
```

On a separate terminal, you can also try running a few Docker commands:

* To see the list of container images: `sudo docker image list`
* To see the list of running containers: `sudo docker container list`
* To stop the Redis container: `sudo docker container stop redis-server`
* To start the Redis container again: `sudo docker container start -a redis-server`


## Task 2: Git Submodules
[20 points]

Your lab repository contains code that extends the Redis server with some additional commands. We will only be concerned with one of these commands: the `EXAMPLE.HGETSET` command. This commands operates on a hash table and takes two parameters: a key and a value. It will fetch the value currently associated with the given key, and will replace its value with the one provided as a parameter. For example, notice how the example below fetches the current value of the `email` key, while also replacing it with a new value:

```shell
127.0.0.1:6379> HSET myhash name "Borja"
(integer) 1
127.0.0.1:6379> HSET myhash email "borja@cs.uchicago.edu"
(integer) 1
127.0.0.1:6379> EXAMPLE.HGETSET myhash email "borja@uchicago.edu"
"borja@cs.uchicago.edu"
127.0.0.1:6379> HGET myhash email
"borja@uchicago.edu"
```

The repository has two directories:

* `module/` - This directory contains the module that implements the new commands (Note: in Redis, the term "module" has a specific meaning, and it refers to an installable component that extends Redis).
* `tests/` - This directory contains a simple program that uses the hiredis library to connect to a Redis server to test the `HGETSET` operation.

To compile the module code, we will need some files included in the Redis Module SDK (Software Development Kit) available in the following repo: https://github.com/RedisLabs/RedisModulesSDK. To compile the testing program, we also need the hiredis library, which is available in this repository: https://github.com/redis/hiredis.

We could, of course, just clone those repositories and copy them into our repository. This is usually a bad idea, because it makes it harder to track updates in the original code. For example, if hiredis releases a new version, we would have to manually copy over their updated version into our repository.

In general, the problem we’re facing is that there is some code produced by a "third party" that we would like to include in our project. In Git this is typically handled by using *submodules*, which effectively allow us to include "third party repositories" in our own repository (in other version control systems, this is sometimes referred to as "vendor branches").

We can add submodules by using the `git submodule` command:

```shell
$ git submodule add https://github.com/RedisLabs/RedisModulesSDK.git
Cloning into '/tmp/2020-lab8-GITHUB_USERNAME/RedisModulesSDK'...
remote: Counting objects: 439, done.
remote: Total 439 (delta 0), reused 0 (delta 0), pack-reused 439
Receiving objects: 100% (439/439), 187.79 KiB | 1.59 MiB/s, done.
Resolving deltas: 100% (258/258), done.

$ git submodule add https://github.com/redis/hiredis.git
Cloning into '/tmp/2020-lab8-GITHUB_USERNAME/hiredis'...
remote: Counting objects: 2909, done.
remote: Compressing objects: 100% (13/13), done.
remote: Total 2909 (delta 9), reused 19 (delta 9), pack-reused 2887
Receiving objects: 100% (2909/2909), 866.09 KiB | 5.16 MiB/s, done.
Resolving deltas: 100% (1791/1791), done.
```

You’ll notice that two new directories have appeared in your repository, containing the files that are in the original RedisModulesSDK and hiredis repositories.

Before we continue, we need to commit these submodules. If you run `git status`, you’ll see that Git is aware that we’ve added two submodules (they are tracked in a special file called `.gitmodules`) but they have not yet been committed:

```shell
$ git status
On branch master
Your branch is up to date with 'origin/master'.

Changes to be committed:
  (use "git reset HEAD <file>..." to unstage)

    new file:   .gitmodules
    new file:   RedisModulesSDK
    new file:   hiredis
```

So, simply run the following:

```shell
$ git commit -m"Added submodules"
$ git push
```

If you go to your repo on the GitHub website, you’ll see that the submodules are shown in a different way: Git is aware that, instead of just copying over the files into your repository, it should simply point to other repositories. 

Now, it will be possible for you to build hiredis, as well as the module and the tests:

```shell
$ make -C hiredis/
$ make -C module/
$ make -C tests/
```

However, you can't run any of this just yet. We need a Redis server for that!

{{% warning %}}
Cloning a repository does not automatically clone the submodules in that repository, instead showing them as empty directories. If you clone your repository somewhere else, you need to clone it like this:

```shell
git clone --recursive REPO_URL
```

If you forgot to use the `--recursive` option, you can also do this after the repository has been cloned:

```shell
git submodule update --init --recursive
```
{{% /warning %}}

For this task, you won't need to enter anything into Gradescope, but make sure you've successfully pushed the submodules to your GitHub repository.

## Task 3: Using Docker in a Travis build

[30 points]

Testing the module requires running Redis, so we will need to set up our Travis build to run a Redis server while testing our module. We will do this by telling Travis to use a Docker container with Redis installed in it, and to run our module in that container.

Our container is specified using the `Dockerfile` file. You do not need to understand everything in that file, except that we use the `FROM redis` command to tell Docker that our container should simply use the standard Redis container that is available on the Docker Hub. Then, all we need to do is install our module in it, and make sure that we start Redis with the `--loadmodule` option to load our module.

{{% note %}}
If you've set up Docker on your VM, you can also test the module on the VM, essentially running the same commands that Travis will be running. Start by cloning your repository inside the VM:

```shell
$ git clone --recursive https://github.com/cmsc22000-labs/2020-lab8-GITHUB_USERNAME.git
```

Then, go into the repository directory:

```shell
$ cd 2020-lab8-GITHUB_USERNAME
```

And use this command to build a container image with Redis *and* our module:

```shell
$ sudo docker build -t redis-example . 
```

This may take a while, as Docker has to download a number of other container images to build ours.

Finally, you can run the container like this:

```shell
$ sudo docker run -d -p 6379:6379 redis-example
```

In a separate terminal, build hiredis and the tests:

```shell
$ make -C hiredis/
$ make -C tests/
```

You should now be able to run the test program:

```shell
$ ./tests/test-hgetset 
PING: PONG
HSET: (null)
HGETSET: Random J. Redisuser
HGET: Alan T. Foobar
```
{{% /note %}}


Add a `.travis.yml` file to your repository with the following contents:

    dist: xenial

    language: c

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

Go ahead and commit and push this file. The Travis build may take a few minutes; just read ahead before checking the status of your build.

There are a few differences with the Travis files we've seen previously:

* The `services` option tells Travis that we will need access to Docker's tools, which includes the ability to build and run our own containers.
* The `before_install` option includes the Docker commands we need to run our container. Notice how they're the same as the ones you can run insider your VM. We've also included `docker container list` to double-check that our container is running.

Other than that, the `script` portion should be pretty self-explanatory: we build hiredis and the tests, and we run the sample program.

The build on Travis may take a few minutes, as it will need to download the necessary container images before it can build and run our code. If the build succeeds, you should be able to see this towards the end of the build's output:

```shell
$ ./tests/test-hgetset 
PING: PONG
HSET: (null)
HGETSET: Random J. Redisuser
HGET: Alan T. Foobar
```

If the build fails or you do not see this output, make sure to ask for help.

For this task, please enter the URL of your successful Travis build on Gradescope.

# Part II: A complete deployment pipeline

In class, we have discussed that software is rarely deployed directly into production but, instead, follows a _deployment pipeline_. In our previous lab we saw a very basic deployment pipeline: we set up our HelloApp to deploy to Heroku, but only if the CI tests passed. In this lab, we are going to see a more complete deployment pipeline.

As we saw in the deployment lecture, a common pipeline is as follows:

* *Local*, where you are the only one making changes to your codebase.
* *Staging*, where all developers can see your changes, but you have time to catch errors before showing the end-users.
* *Production*, where your app is available to the real world. Usually, the staging app will be promoted to production when it is ready.

In this lab, you’ll create a more complete Heroku pipeline for last week's HelloApp. If you did not successfully complete Lab 7, please ask for help so we can ensure that you're all set up for this week's lab.

Heroku already provides support for creating pipelines, and ours will have three stages:

* *Review*: Similar to a development stage. In Heroku, we can automatically link this stage to our pull requests on GitHub, so we can easily test any changes we are proposing in a pull request.
* *Staging*: We will be using the app you created in Lab 7 as our staging app.
* *Production*: A new production app that is only available if we are satisfied with our staging app.

## Task 1: Create a Pipeline

[0 points]

In this task, you’ll create a new Heroku Pipeline, using the the `CNETID-cs220-lab7` application (from last week's lab) as the staging application. Note that a common convention is for staging applications to have `-staging` as a suffix, but it won't be necessary for you to rename your app in this lab.

To create the pipeline, log into Heroku, and select the app you created in Lab 7. Under the deploy tab, click on "Choose a pipeline" (in the "Add this app to a pipeline" section) and then "Create new pipeline". Name your pipeline `CNETID-pipeline` (where `CNETID` should be replaced with your CNetID). You will also be asked to specify "Choose a stage to add this app to". Make sure that "staging" is selected. Finally, click on "Create pipeline".

You will now be shown the pipeline's configuration (you will also be able to access this page through your dashboard, which will now include a `CNETID-pipeline` pipeline). Notice how there is no production application in your pipeline. In the real world, this would mean that your end users don’t see anything!

Please note that you do not need to enter anything into Gradescope for this task. While it is worth 0 points, you still need to create a pipeline before moving on to the next tasks.

##  Task 2: Add a production application

[10 points]

In this task, you’ll add a production application to your pipeline. Unlike the app in staging, your production app won't be associated with any specific repo. Instead, once your staging application is good to go, you can *promote* it to be the production application. That means the production application will just take the staging app, make a copy of it, and run that copy as the production app. This means that, if you make changes to the staging app, those changes whon't appear in production until you explicitly promote the staging app to production again. 

Later in the lab you may see Heroku messages that talk about "slugs"; in Heroku parlance, a "slug" is a pre-compiled version of your app that is ready to run. So, when we promote to production, we don't actually rebuild the application; we just take the "slug" that is in staging, and copy it to production.

To add a production application, all you have to do is go to your pipeline and, under "Production", click on "Add app" and then "Create new app". Name the application `CNETID-cs220-prod` (where `CNETID` should be replaced with your CNetID). Notice how, if you try to access your app on Heroku (just go to http://CNETID-cs220-prod.herokuapp.com/), you'll just see a placeholder page, not HelloApp. That's because we haven't promoted our staging app to production yet.

On Gradescope, enter the URL of your staging app.

## Task 3: Promoting from staging to production

[20 points]

First, let's make a change to our HelloApp: it's time to upgrade to HelloApp 2.0!
 
* In your repository from Lab 7 (`2020-lab7-GITHUB_USERNAME`), edit `hello/templates/base.html` and change "Helloapp" to "Helloapp 2.0".
* Commit and push this change with the message "Update to 2.0"
* Assuming you completed Lab 7 last week, your updated app will automatically deploy. Remember this may take a few minutes (you can check the progress of the deployment by going to the "Activity" tab in your app)

Now, notice that if you navigate to your staging website (`CNETID-cs220-lab7.herokuapp.com`) you’ll see your change. But if you navigate to your production website (`CNETID-cs220-prod.herokuapp.com`), you'll still see a placeholder page.

Why is this? Changes from staging are *not* automatically deployed to production. This is intentional: we often don’t want things to automatically deploy to production, since we might risk breaking the public-facing version of our app. Pushing code that is broken is known as "breaking the build", and you absolutely don't want that to propagate to production (by the way, if you know anyone who has done a software development internship or works in software development, ask them if they've ever "broken the build"; we guarantee you'll hear some entertaning stories). By having a pipeline, we can ensure that users continuously see our production, without mistakes, and we only update it when we’re absolutely sure. 

So, let's go ahead and promote our staging application to production. You can do this simply by pressing the "Promote to production..." button in the staging app of your pipeline. Once you do this, your staging app (`CNETID-cs220-lab7.herokuapp.com`) and your production app (`CNETID-cs220-prod.herokuapp.com`) should look exactly the same.

On Gradescope, enter the URL of your production app.

## Task 4: Create Review Apps - Helloapp 3.0

[20 points]

Currently, in order to make changes to staging, you have to directly modify the master branch of your repo. Can you imagine why this is a bad idea?

In order to show your changes to anyone, you’d have to directly change staging, which isn’t as bad as directly modifying production, but could be embarrassing if you’re trying to get a small change approved and then break everything for every other developer in your team!

The last thing you’ll do is create a review app stage for your pipeline. This way, every pull request submitted to GitHub can be its own app. This lets developers see changes per-pull request. 

To do this, we first need to connect the pipeline to GitHub:
 
* From the pipeline page on Heroku, click on "Connect to GitHub"
* This will take you to a different page. Under "Search for a repository to connect to", select the "cmsc22000-labs" organization, and then enter your repository's name (`2020-lab7-GITHUB_USERNAME`). Make sure to click on the "Search button"
* Finally, click on the "Connect" button next to your repository's name.

Now, from your pipeline's page, do the following:

* Click on "Enable Review Apps". This will show you a form on the side of the page.
* Enable "Create new review apps for new pull requests automatically"
* Do NOT enable "Wait for CI to pass" (this refers to Heroku's own CI, and we are already using Travis for CI)
* Enable "Destroy stale review apps automatically"
* Don't worry about the "Review apps may incur dyno and add-on charges." message. We are using the free tier of Heroku, so we won't be charged for anything. If you want to be extra sure, go to https://dashboard.heroku.com/account/billing and make sure there is no credit card on file for your account, and that you have free hours available under "Free Dyno Usage".
* Click on "Enable Review Apps"

Now, you’ll create a pull request:

* Create a new branch called `create-version-3` in your `2020-lab7-GITHUB_USERNAME` repository.
* Edit `hello/templates/base.html` and change "Helloapp 2.0" to "Helloapp 3.0".
* Commit and push the changes with the message "Update to 3.0"
* Notice how the change won't show up on `CNETID-cs220-lab7.herokuapp.com`, because we haven't pushed the changes to `master`.
* Now, on GitHub, create a new pull request. Make sure your pull request is to merge the `create-version-3` branch to the `master` branch of your repository. You do not need to assign any reviewers to this pull request, nor do you need to worry about writing a summary, etc.
* On your heroku Dashboard, you should see a new application under "Review Apps" (with the name of the pull request: "Updated to 3.0")

Click on "Open app" to view the review app. This allows you to see what your app would look like if the changes in the pull request were deployed. The review app should show the title "HelloApp 3.0", while both the staging (`CNETID-cs220-lab7.herokuapp.com`) and production (`CNETID-cs220-prod.herokuapp.com`) apps should still show "HelloApp 2.0"

If the review app correctly shows the title "HelloApp 3.0", go ahead and merge your PR (remember, you don't need to wait to get a review; just go ahead and merge the pull request). This should push the changes to staging, since you set up automatic deploys for your app  (please note that it may take a few minutes for this to happen). Once this succeeds, go ahead and promote your final app to production. 

Please note that, once you merge the pull request, the review app will disappear. This is normal.

On Gradescope, enter the URL of the pull request you created on GitHub. 

### Submitting your lab

In this lab, you just need to enter a few URLs into Gradescope (make sure you've done so at the points instructed above). You should also make sure you've pushed your code to GitHub (but you will not be submitting your code through Gradescope; we just need to check that you've made the commits we expected you to make).

