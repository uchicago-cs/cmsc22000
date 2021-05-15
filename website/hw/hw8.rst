Homework 8: More CI and Deployment
==================================

**Due:** Wednesday, May 26th, 8pm CDT

In this homework, we will continue to explore concepts related to Continuous
Integration and Deployment. The homework is divided into two main parts: one
where we will see how we can use Docker containers as part of a CI
build, and one where we will expand the deployment pipeline we saw in
our previous homework.

Part I: Using Containers in CI
------------------------------

It is often necessary for a CI build to use a specific software
environment to build code and to run tests. This may be as simple as
needing some set of libraries installed before we can build and run your
code, or as complex as running some sort of server that our code and
tests need to run.

In this homework, we are going to work through an example that requires a
running `Redis <https://redis.io/>`__, a popular data structure store.
In a nutshell, Redis is a server that can store a variety of data
structures (including lists, hash tables, etc.), and which allows you to
manipulate those data structures via an API and a CLI. The API is
typically accessed remotely (i.e., the Redis server runs on one machine,
and client software running on a different machine accesses the API
through a network), which means that testing client software that relies
on Redis requires running a Redis server too.

In Homework #6, we saw how you can install a software dependency (the
Criterion testing library) as part of a GitHub Actions workflow, by
specifying the exact installation commands in one of the steps of the
workflow. In general, most CI systems will allow you to install additional
software to run your CI jobs. However, installing
and configuring a complex piece of software like Redis through this
mechanism can be cumbersome. It can also take a fair amount of time,
even if the installation is automated, so it can pay off to simply have
a software environment that is ready to go with all the software we
need.

One way of doing this is by using *containers*, a sort of lightweight
virtual machine that provides a specific software environment we need.
Unlike virtual machines, containers are typically used to package a
specific piece of software, instead of providing a full OS environment
(although this is also possible with containers).

For example, a Redis container would include a Redis server and, by
default, running the container would immediately start that Redis
server, instead of taking us to a UNIX shell where we have to run the
Redis server ourselves. So, if we wanted to run Redis during a CI build,
all we would need to do is download a Redis *container image*, and run
that container during the CI build. A popular container manager is
`Docker <https://www.docker.com/>`__, which we will be using in this
homework. Make sure to read their `What is a
Container <https://www.docker.com/what-container>`__ page, which
provides a more in-depth explanation of what a container is, and how it
compares to virtual machines.

Creating your homework repository
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Like previous homeworks, we will provide you with an *invitation URL* that
will allow you sign up for the homework assignment on GitHub, and which will
result in the creation of a repository called
``2021-hw8-GITHUB_USERNAME`` inside our ``uchicago-cmsc22000`` organization
on GitHub.

Your repository will be seeded with some files for the homework
and, more specifically, will contain some code that requires a Redis
server to run correctly.

Task 1: Git Submodules
~~~~~~~~~~~~~~~~~~~~~~

[20 points]

Before we setup our CI job to run a Redis server, we're going
to explore a new Git concept: submodules.

Your homework repository contains a simple program that connects
to a Redis server and runs a few simple commands on the Redis
server. You do not need
to understand what these commands do (we'll discuss them in
more detail later in the homework); it is enough to know that this
program will only work if there is a Redis server running on the
same computer as the program.

This program depends on a library called `hiredis <https://github.com/redis/hiredis>`__
that provides an API for C programs to send commands to a Redis server.
In fact, we need the header files from that library to compile the program.
We could, of course, install the library on our computer, but another
approach is to include the library in our repository: that way, our
repository will have everything we need to compile our program.

However, cloning the hiredis repository and copying it into
our repository is usually a bad idea, because it makes it harder
to track updates in the original code. For example, if hiredis releases
a new version, we would have to manually copy over their updated version
into our repository.

In general, the problem we’re facing is that there is some code produced
by a “third party” that we would like to include in our project. In Git,
this is typically handled by using *submodules*, which effectively allow
us to include “third party repositories” in our own repository (in other
version control systems, this is sometimes referred to as “vendor
branches”).

You can add submodules by using the ``git submodule`` command inside your repository:

.. code:: shell

    $ git submodule add https://github.com/redis/hiredis.git
    Cloning into '/home/studemt/2021-hw8-GITHUB_USERNAME/hiredis'...
    remote: Enumerating objects: 3950, done.
    remote: Counting objects: 100% (20/20), done.
    remote: Compressing objects: 100% (18/18), done.
    remote: Total 3950 (delta 7), reused 9 (delta 2), pack-reused 3930
    Receiving objects: 100% (3950/3950), 1.34 MiB | 14.58 MiB/s, done.
    Resolving deltas: 100% (2484/2484), done.


You’ll notice a new ``hiredis`` directory has appeared in your repository,
containing the files that are in the original hiredis repositories.

Before we continue, we need to commit this submodule. If you run
``git status``, you’ll see that Git is aware that we’ve added a
submodule but it has not yet been committed (besides the submodule
itself, Git has also modified a special file called ``.gitmodules`` that
it uses to keep track of all submodules):

.. code:: shell

    $ git status
    On branch main
    Your branch is up to date with 'origin/main'.

    Changes to be committed:
      (use "git restore --staged <file>..." to unstage)
            new file:   .gitmodules
            new file:   hiredis


So, simply run the following:

.. code:: shell

   $ git commit -m"Added hiredis submodule"
   $ git push

If you go to your repo on the GitHub website, you’ll see that the
submodules are shown in a different way:

.. figure:: submodules.png
   :alt: Submodules in GitHub

Git is aware that, instead of
just copying over the files into your repository, it should simply point
to other repositories.

Now, it will be possible for you to build hiredis, as well as the module
and the tests:

.. code:: shell

   $ make -C hiredis/
   $ make -C sample/

However, if we try to run the sample program, it will fail because it can't
find a Redis server to connect to::

    $ sample/sample-redis
    Connection error: Connection refused

Before we see how to launch a Redis server as part of a CI job in the next task,
make sure you’ve successfully pushed the submodule to your GitHub
repository. You do not need to enter anything on Gradescope.

.. note::

    If you need to clone your repository in a separate location later on,
    take into account that cloning a repository does not automatically clone the
    submodules in that repository, instead showing them as empty
    directories. If you clone your repository somewhere else, you need to
    clone it like this:

    .. code:: shell

       git clone --recursive REPO_URL

    If you forgot to use the ``--recursive`` option, you can also do this
    after the repository has been cloned:

    .. code:: shell

       git submodule update --init --recursive

Task 2: Using a Container-ized Service in a GitHub Actions workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[30 points]

Testing our program requires running Redis, so we will need to set up our
GitHub Actions workflow to run a Redis server. We will do
this by telling GitHub Actions to use a Docker container with Redis installed in
it. Running additional software in a Docker container is such a common operation,
that GitHub Actions makes this very easy. It basically boils down to adding
something like this to our workflow file::

    services:
      redis:
        image: redis
        ports:
          - 6379:6379

That's it! In the next task we'll dig a bit deeper into how this translates
into specific Docker commands. For now, just add a ``.github/workflows/build-and-test.yml``
file to your repository with the following contents:

::

    name: Build and Test Redis program

    on: [push]

    jobs:
      build-and-test:

        runs-on: ubuntu-latest

        services:
          redis-server:
            image: redis
            ports:
              - 6379:6379

        steps:
        - uses: actions/checkout@v2
          with:
            submodules: 'recursive'

        - name: Build hiredis
          working-directory: hiredis/
          run: |
            make clean
            make

        - name: Build sample program
          working-directory: sample/
          run: |
            make clean
            make

        - name: Run sample program
          run: ./sample/sample-redis


Go ahead and commit and push this file; this should result in a successful
workflow run. The main difference with previous workflow files we've
seen is the ``services`` option::

        services:
          redis-server:
            image: redis
            ports:
              - 6379:6379

In this option we are specifying that we want the ``build-and-test`` job
to run a "service" inside a Docker container for the duration of the job. The service
is named ``redis-server`` (we can choose any name we want here), and
we specify that the Docker container must use the ``redis`` container image
(you can think of the "container image" as the exact software environment
we want to run in the Docker container).

The value of the ``image`` option
has to be an image that is publicly available on `Docker Hub <https://hub.docker.com/>`__,
a public repository of Docker images. If you browse through Docker Hub,
you'll see that we have *a lot* of software environments at our disposal:
web servers, database servers, etc. (and all of these can be easily
launched in our workflow with the ``service`` option). For example,
here is the entry for the ``redis`` image: https://hub.docker.com/_/redis

The ``ports`` option specifies how TCP ports are mapped between the Docker
container and our workflow job. You do not need to understand how TCP ports
work, but this option is required for our program to be able to connect
to the Redis server that is running in the Docker container.

The rest of the workflow file should be pretty self-explanatory:
we build hiredis and the sample program, and then we run the sample
program.

Now, fetch the URL of the workflow run, and paste it into Gradescope
(under "Task 2: Using a Container-ized Service in a GitHub Actions workflow"). Remember it will look something like this::

    https://github.com/uchicago-cmsc22000/2021-hw8-GITHUB_USERNAME/actions/runs/XXXXXXXXXX

Where ``XXXXXXXXXX`` will be a number.

Before continuing to the next task, take a look at the job steps in
your workflow run on GitHub: you'll
see there is a new "Initialize containers" step, where GitHub Actions
launches a Docker container with a Redis server. The "Run sample program"
step should be able to connect to the Redis server, and you'll see this
output in that step:

.. code:: shell

   PING: PONG
   HSET: (null)
   HGET: Random J. Redisuser

If the build fails or you do not see this output, make sure to ask for
help.


Task 3: Running Docker in the CS VM
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[0 Points]

.. note::

    This is an optional task, and you will be able to complete
    the homework even if you don’t do this task. However, even if you do not
    perform the steps in this task, you should still read through the task,
    as it provides some additional details on how Docker and Redis work.

In the previous task, we saw that GitHub Actions abstracts away all the
details of running a Docker container. In this task, we will see how
to actually run a Docker container ourselves. However, using Docker requires `root
privileges <https://en.wikipedia.org/wiki/Superuser>`__, which you do
not have on the CS machines. So, we will use the `UChicago CS Virtual
Machine <https://howto.cs.uchicago.edu/vm:index>`__, where you do have
the ability to run commands with root privileges.

Completing this task requires running the VM on your own machine,
so this task is optional and ungraded, but strongly
recommended, specially if you’ve already installed the UChicago CS VM.

Once you’ve started the UChicago CS VM, open a terminal. We will first
need to install Redis and Docker on the virtual machine. You can install
Redis by running the following commands (these instructions are based on
the official Redis `installation
documentation <https://redis.io/download>`__):

.. code:: shell

   wget http://download.redis.io/redis-stable.tar.gz
   tar xzf redis-stable.tar.gz
   cd redis-stable/
   make
   sudo make install

Notice how that last command is run with ``sudo``. This basically
instructs the operating system to run the command (``make install``)
with root privileges. You will be asked to enter your password which, on
the CS VM, is ``uccs`` by default. The reason we need to run this
command with ``sudo`` is because it involves installing the Redis
libraries and binaries in system-wide locations, which require root
privileges to modify.

Now, run the following commands (these are
based on the official Docker `installation
documentation <https://docs.docker.com/install/linux/docker-ce/ubuntu/>`__):

.. code:: shell

   sudo apt update
   sudo apt install -y apt-transport-https ca-certificates curl gnupg lsb-release
   curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
   echo "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
   sudo apt-get update
   sudo apt-get install -y docker-ce docker-ce-cli containerd.io

You can verify that Docker is correctly installed by running this:

.. code:: shell

   sudo docker run hello-world

This will run a container whose sole purpose is to print out a welcome
message. If you do not see a message that starts with “Hello from
Docker!”, please ask for help.

We can run a Redis container simply by running the following:

.. code:: shell

   sudo docker run --name redis-server -p 6379:6379 redis

Docker will first download the Redis container image from `Docker
Hub <https://hub.docker.com/_/redis/>`__, and then run it. You should
see some output that ends with something like this:

.. code:: shell

   1:M 11 May 2021 14:16:09.584 * Ready to accept connections

Now, open another terminal in the VM and run this:

.. code:: shell

   redis-cli

This should open up a prompt like this:

.. code:: shell

   127.0.0.1:6379>

This means that the Redis CLI tool running on your VM has successfully
connected to the Redis server running inside the Docker container.
However, notice how we’re not running Redis directly on the VM (we
installed Redis so we could use the ``redis-cli`` tool, but we never ran
the ``redis-server`` command on the VM).

You can now try running a few Redis commands from the Redis CLI:

.. code:: shell

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

The above commands basically set and get the value of a variable called
``foo`` (using the ``SET`` and ``GET``) commands, and also create a
hash table called ``myhash`` where we set values for two keys, ``name`` and ``email``,
using the ``HSET`` command. We can then get values from the hash table using
the ``HGET`` command, or list all the keys in the hash table using the ``HKEYS`` command.

On a separate terminal, you can also try running a few Docker commands:

-  To see the list of container images: ``sudo docker image list``
-  To see the list of running containers: ``sudo docker container list``
-  To stop the Redis container:
   ``sudo docker container stop redis-server``
-  To start the Redis container again:
   ``sudo docker container start -a redis-server``

.. note::

   Before continuing with the rest of the task, make sure to stop
   the Docker container you've just launched. Otherwise, it will
   interfere with the rest of the task.

So far, we've been using pre-existing container images found on `Docker
Hub <https://hub.docker.com/_/redis/>`__, but we also have the ability
to define our own container images. Your homework repository includes
a ``Dockerfile`` file that includes the specification of a custom Redis
image. To give it a try, start by cloning your repository inside the VM
(if you are still inside the `redis-stable` directory, make sure to `cd`
back to your home directory before running the following command):

.. code:: shell

   $ git clone --recursive https://github.com/uchicago-cmsc22000/2021-hw8-GITHUB_USERNAME.git

Then, go into the repository directory:

.. code:: shell

   $ cd 2021-hw8-GITHUB_USERNAME

Take a look at the ``Dockerfile`` file. This file instructs Docker
on how to build a new container image. The first line
tells Docker to use the ``gcc`` image on Docker Hub as a starting
point (since we're building Redis from scratch, we need access to
a software environment with a compiler)::

    FROM gcc:9.3

The next lines are essentially the same commands we ran earlier
to build Redis in the VM::

    # Download Redis
    WORKDIR /tmp
    RUN wget http://download.redis.io/redis-stable.tar.gz
    RUN tar xzf redis-stable.tar.gz

    # Build and install Redis
    WORKDIR /tmp/redis-stable/
    RUN make
    RUN make install

    # Clean up
    RUN rm -rf /tmp/redis-stable/ /tmp/redis-stable.tar.gz

Finally, we need to specify the command that will be run
whenever we launch a container with this image::

    # Command to run when container is launched
    CMD ["redis-server", "--bind", "0.0.0.0"]

To be clear, the ``RUN`` commands are run only once, when the container
image is first built, not every time we launch the container.

To build our custom container, run this command:

.. code:: shell

   $ sudo docker build -t custom-redis .

The ``.`` refers to the current directory (which contains the ``Dockerfile``
that Docker needs to build the container image).

This may take a while, as Docker has to download a number of other
container images to build ours *and* it has to build Redis from
scratch. Once it finishes building the image, you can run the container like this:

.. code:: shell

   $ sudo docker run -p 6379:6379 custom-redis

.. note::

   If you get a ``port is already allocated`` error, make sure the container
   you launched previously has been stopped::

        sudo docker container stop redis-server

In a separate terminal, build hiredis and the sample program:

.. code:: shell

   $ make -C hiredis/
   $ make -C sample/

You should now be able to run the test program:

.. code:: shell

    $ ./sample/sample-redis
    PING: PONG
    HSET: (null)
    HGET: Random J. Redisuser


Task 4: Using a Custom Dockerfile in our Workflow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[10 points]

Now that we've seen how to specify a custom container, let's try using it
in our CI workflow. Please note that you don't need to complete this
task on the CS VM. You can follow all the necessary steps while logged
into a CS machine.

Update the ``.github/workflows/build-and-test.yml`` file in your repository so
it will contain the following::

    name: Build and Test Redis program

    on: [push]

    jobs:
      build-and-test:

        runs-on: ubuntu-latest

        steps:
        - uses: actions/checkout@v2
          with:
            submodules: 'recursive'

        - name: Build and run Docker container
          run: |
            sudo docker build -t custom-redis .
            sudo docker run -d -p 6379:6379 custom-redis
            sudo docker container list

        - name: Build hiredis
          working-directory: hiredis/
          run: |
            make clean
            make

        - name: Build sample program
          working-directory: sample/
          run: |
            make clean
            make

        - name: Run sample program
          run: ./sample/sample-redis

Notice how we've removed the ``services`` option, and instead added a new
step that manually builds and runs our custom container. We’ve also included
``docker container list`` to double-check that our container is running.

You'll notice that this workflow takes considerably longer to run than previous
workflow, because building the custom container involves building Redis from
scratch. In practice, we would not build this container from scratch in
every workflow run and, instead, we would either upload our container image
to Docker Hub so we can easily reuse it, or we would make use of GitHub Actions'
`caching features <https://docs.github.com/en/actions/guides/caching-dependencies-to-speed-up-workflows>`__
to reuse the container image across multiple workflow runs.

Before continuing, take the URL of your successful workflow run, and paste it into Gradescope
(under "Task 4: Using a Custom Dockerfile in our Workflow").


Part II: A Complete Deployment Pipeline
---------------------------------------

In class, we have discussed that software is rarely deployed directly
into production but, instead, follows a *deployment pipeline*. In our
previous homework we saw a very basic deployment pipeline: we set up our
HelloApp to deploy to Heroku, but only if the CI tests passed. In this
homework, we are going to see a more complete deployment pipeline.

As we saw in the deployment lecture, a common pipeline is as follows:

-  *Local*, where you are the only one making changes to your codebase.
-  *Staging*, where all developers can see your changes, but you have
   time to catch errors before showing the end-users.
-  *Production*, where your app is available to the real world. Usually,
   the staging app will be promoted to production when it is ready.

In this homework, you’ll create a more complete Heroku pipeline for last
week’s HelloApp. If you did not successfully complete Homework #7, please ask
for help so we can ensure that you’re all set up for this week’s homework.

Heroku already provides support for creating pipelines, and ours will
have three stages:

-  *Review*: Similar to a development stage. In Heroku, we can
   automatically link this stage to our pull requests on GitHub, so we
   can easily test any changes we are proposing in a pull request.
-  *Staging*: We will be using the app you created in Homework #7 as our
   staging app.
-  *Production*: A new production app that is only available if we are
   satisfied with our staging app.

Task 1: Create a Pipeline
~~~~~~~~~~~~~~~~~~~~~~~~~

[0 points]

In this task, you’ll create a new Heroku Pipeline, using the
``CNETID-cs220-hw7`` app(from last week’s homework) as the staging
app. Note that a common convention is for staging apps
to have ``-staging`` as a suffix, but it won’t be necessary for you to
rename your app in this homework.

To create the pipeline, log into Heroku, and select the app you created
in Homework #7. Under the Deploy tab, click on “Choose a pipeline” (in the
“Add this app to a pipeline” section) and then “Create new pipeline”.
Name your pipeline ``CNETID-pipeline`` (where ``CNETID`` should be
replaced with your CNetID). You will also be asked to specify “Choose a
stage to add this app to”. Make sure that “staging” is selected.
Finally, click on “Create pipeline”.

You will now be shown the pipeline’s configuration (you will also be
able to access this page through your dashboard, which will now include
a ``CNETID-pipeline`` pipeline). Notice how there is no production
app in your pipeline. In the real world, this would mean that
your end users don’t see anything!

Please note that you do not need to enter anything into Gradescope for
this task. While it is worth 0 points, you still need to create a
pipeline before moving on to the next tasks.

Task 2: Add a production app
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[10 points]

In this task, you’ll add a production app to your pipeline.
Unlike the app in staging, your production app won’t be associated with
any specific repo. Instead, once your staging app is good to go,
you can *promote* it to be the production app. That means the
production app will just take the staging app, make a copy of
it, and run that copy as the production app. This means that, if you
make changes to the staging app, those changes won’t appear in
production until you explicitly promote the staging app to production
again.

Later in the homework you may see Heroku messages that talk about “slugs”; in
Heroku parlance, a “slug” is a pre-compiled version of your app that is
ready to run. So, when we promote to production, we don’t actually
rebuild the application; we just take the “slug” that is in staging, and
copy it to production.

To add a production application, all you have to do is go to your
pipeline and, under “Production”, click on “Add app” and then “Create
new app”. Name the application ``CNETID-cs220-prod`` (where ``CNETID``
should be replaced with your CNetID). Notice how, if you try to access
your app on Heroku (just go to http://CNETID-cs220-prod.herokuapp.com/),
you’ll just see a placeholder page, not HelloApp. That’s because we
haven’t promoted our staging app to production yet.

On Gradescope, enter the URL of your staging app (this will be the same
URL as the HelloApp you deployed in Homework #7).

Task 3: Promoting from staging to production
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[20 points]

First, let’s make a change to our HelloApp: it’s time to upgrade to
HelloApp 2.0!

-  In your repository from Homework #7 (``2021-hw7-GITHUB_USERNAME``), edit
   ``hello/templates/base.html`` and change ``<h1>HelloApp</h1>`` to ``<h1>HelloApp 2.0</h1>``
-  Commit and push this change with the message “Update to 2.0”
-  Assuming you completed Homework #7 last week, your updated app will
   automatically deploy. Remember this may take a few minutes (you can
   check the progress of the deployment by going to the “Activity” tab
   in your app)

Now, notice that if you navigate to your staging website
(``CNETID-cs220-hw7.herokuapp.com``) you’ll see your change. But if you
navigate to your production website
(``CNETID-cs220-prod.herokuapp.com``), you’ll still see a placeholder
page.

Why is this? Changes from staging are *not* automatically deployed to
production. This is intentional: we often don’t want things to
automatically deploy to production, since we might risk breaking the
public-facing version of our app. Pushing code that is broken is known
as “breaking the build”, and you absolutely don’t want that to propagate
to production (by the way, if you know anyone who has done a software
development internship or works in software development, ask them if
they’ve ever “broken the build”; we guarantee you’ll hear some
entertaining stories). By having a pipeline, we can ensure that users
continuously see our production app, without mistakes, and we only update it
when we’re absolutely sure.

So, let’s go ahead and promote our staging application to production.
You can do this simply by pressing the “Promote to production…” button
in the staging app of your pipeline. Once you do this, your staging app
(``CNETID-cs220-hw7.herokuapp.com``) and your production app
(``CNETID-cs220-prod.herokuapp.com``) should look exactly the same.

On Gradescope, enter the URL of your production app.

Task 4: Create Review Apps - HelloApp 3.0
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

[20 points]

Currently, in order to make changes to staging, you have to directly
modify the main branch of your repo. Can you imagine why this is a bad
idea?

In order to show your changes to anyone, you’d have to directly change
staging, which isn’t as bad as directly modifying production, but could
be embarrassing if you’re trying to get a small change approved and then
break everything for every other developer in your team!

The last thing you’ll do is create a *review app* stage for your pipeline.
This way, every pull request submitted to GitHub can be its own app.
This lets developers see changes per-pull request.

To do this, we first need to connect the pipeline to GitHub:

-  From the pipeline page on Heroku, click on “Connect to GitHub”
-  This will take you to a different page. Under “Search for a
   repository to connect to”, select the “uchicago-cmsc22000” organization,
   and then enter your repository’s name
   (``2021-hw7-GITHUB_USERNAME``). Make sure to click on the “Search”
   button.
-  Finally, click on the “Connect” button next to your repository’s
   name.

Now, from your pipeline’s page, do the following:

-  Click on “Enable Review Apps" in the "Review Apps” section. This will show you a form on the side
   of the page.
-  Enable “Create new review apps for new pull requests automatically”
-  Do NOT enable “Wait for CI to pass” (this refers to Heroku’s own CI,
   and we are already using GitHub Actions for CI)
-  Enable “Destroy stale review apps automatically”. This will allow you
   to specify a number of days; you can leave the default value ("After 5 days") as-is.
-  Click on “Enable Review Apps”

   Don’t worry about the “Review apps may incur dyno and add-on
   charges.” that appears above the "Enable Review Apps" button.
   We are using the free tier of Heroku, so we won’t
   be charged for anything. If you want to be extra sure, go to
   https://dashboard.heroku.com/account/billing and make sure there is
   no credit card on file for your account, and that you have free hours
   available under “Free Dyno Usage”.

Now, you’ll create a pull request:

-  Create a new branch called ``create-version-3`` in your
   ``2021-hw7-GITHUB_USERNAME`` repository.
-  Edit ``hello/templates/base.html`` and change ``<h1>HelloApp 2.0</h1>`` to ``<h1>HelloApp 3.0</h1>``
-  Commit and push the changes with the message “Update to 3.0”
-  Notice how the change won’t show up on
   ``CNETID-cs220-hw7.herokuapp.com``, because we haven’t pushed the
   changes to ``main``.
-  Now, on GitHub, create a new pull request. Make sure your pull
   request is to merge the ``create-version-3`` branch to the ``main``
   branch of your repository. You do not need to assign any reviewers to
   this pull request, nor do you need to worry about writing a summary,
   etc.
-  On your heroku Dashboard, you should see a new application under
   “Review Apps” (with the name of the pull request: “Updated to 3.0”)

Click on “Open app” to view the review app. This allows you to see what
your app would look like if the changes in the pull request were
deployed. The review app should show the title “HelloApp 3.0”, while
both the staging (``CNETID-cs220-hw7.herokuapp.com``) and production
(``CNETID-cs220-prod.herokuapp.com``) apps should still show “HelloApp
2.0”

If the review app correctly shows the title “HelloApp 3.0”, go ahead and
merge your PR (remember, you don’t need to wait to get a review; just go
ahead and merge the pull request). This should push the changes to
staging, since you set up automatic deploys for your app (please note
that it may take a few minutes for this to happen). Once this succeeds,
go ahead and promote your final app to production.

Please note that, once you merge the pull request, the review app will
disappear. This is normal.

On Gradescope, enter the URL of the pull request you created on GitHub.

Submitting your homework
------------------------

In this homework, you just need to enter a few URLs into Gradescope (make
sure you’ve done so at the points instructed above). You should also
make sure you’ve pushed your code to GitHub, as we need to check
whether you created the ``hiredis`` submodule correctly
(however, you will not be submitting your code through Gradescope).
