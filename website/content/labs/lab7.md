---
title: "Lab 7: Deployment"
date: 2018-01-26
publishdate: 2018-01-26
draft: false
---

**Due:** Thursday, May 23rd, 2:30pm

Last week, you learned about Continuous Integration, which deals with how application code makes it to the master branch. But how do our applications make it to the *real world*, where other people can use them?

Deployment refers to the processes by which software systems are made available for use (a related term, *delivery*, refers to making software available specifically to end-users). The exact deployment pipeline can vary from one project to another. For example, in a large financial company, deploying business management software might require system architects to come and physically upload software on the machines. On the other hand, if you're deploying a small web application, you just need a way to get your application from your computer to a server where other users can access it.

In this lab, you will deploy an application to [Heroku](https://www.heroku.com/), one of the most popular services for hosting web apps. You can see what your app *should* look like at https://cs220-helloapp.herokuapp.com/


# Task 0: Setup
[0 Points]

You should already have the “upstream” remote set up in your repository. If you do, simply run

    $ git pull upstream master

to get the files for this lab. If you don’t have the “upstream” remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).

Once you've pulled from upstream, there should be a `labs/lab7` directory in your local repository with a `tasks.txt` file. In this lab, you will just have to copy-paste a few URLs that we will use to verify that you've done the work in this lab.

Next, in this lab we'll be working with the small [Flask](http://flask.pocoo.org/) web application we demonstrated in class. Don't worry: while the app is implemented in Python, no Python knowledge is necessary for this lab. First, you'll make a **fork** of the app. We covered forking in the [Advanced Git Lab]({{< relref "advanced-git.md" >}}), so you may want to review that lab if you're not 100% clear on what a fork is. In a nutshell, a fork is a new copy of a project under your own username. Forking a repository allows you to freely experiment with changes without affecting the original project (unless you choose to contribute back to the original project and the owners accept your contribution). Forking and then submitting pull requests across a fork is a very common practice in open source software development.

You can fork the `cs220-helloapp-2019` repository by going [here](https://github.com/uchicago-cs/cs220-helloapp-2019) and clicking "Fork" in the upper right hand corner.

Once the fork has completed, you can clone it and begin your work. Remember to do this *outside* of your individual GitLab repository! (i.e., do _not_ run the following command in the same directory that contains your `labs/`, `libgeometry/`, etc. directories, or inside the `labs/lab7` directory). 

```
$ git clone https://github.com/[yourusername]/cs220-helloapp-2019.git

```

Edit your `tasks.txt` file and include the URL of your forked `cs220-helloapp-2019` repository on GitHub. 

Careful! Remember that your `tasks.txt` is in your personal repository on GitLab (with all your other lab files). You will _only_ be using that repository to edit your `tasks.txt` file. The rest of your work will happen on the forked `cs220-helloapp` repository you just created.

# Task 1: Create a Heroku App
[20 points]

Heroku is a common service used to host web applications. For this task you'll sign up for a (free) account and use it to deploy an app with an Internet-reachable URL.

1. Go to https://signup.heroku.com/login
2. Sign up and mark your "role" as "student". You will need to confirm your account, and then create a password.

Once you've created your account, you're ready to create a Heroku app.

1. Go to your dashboard, https://dashboard.heroku.com/apps
2. Click the big button that says "Create new app"
3. Under "app-name" title your app "[cnetID]-cs220-lab7". This means that the url for your app will be "https://[cnetID]-cs220-lab7.herokuapp.com"

You've created your app! But navigate to "https://[cnetID]-cs220-lab7.herokuapp.com". As you can see, there's nothing there. In the coming tasks we will get the helloapp up and running on this URL.

Before continuing, edit your `tasks.txt` file and include the URL of your app on Heroku. 

# Task 2: Deploy using Heroku CLI
[20 points]

In class, we saw that we can deploy an app to Heroku simply by pushing to their Git repository. Your local `cs220-helloapp-2019` repository is currently configured to push only to GitHub, so we need to set it up to also push to Heroku. We can do this using a command-line tool provided by Heroku.

First, you'll need to log into Heroku like this:

```
$ cd cs220-helloapp-2019
$ heroku login
```

{{% warning %}}
{{% md %}}
Techstaff has set up the `heroku` command on the CSIL machines and the `linux.cs` servers.

If you are running inside the CS VM, then you will need to install Flask and the `heroku` command by running the following:

```
$ sudo -H pip3 install flask
$ sudo snap install --classic heroku
```

If you are using the Headless VM setup, take into account that the `heroku login` command will attempt to open a browser to log you into Heroku, which is not possible from headless mode. Instead, the command will print out a URL, which you will have to manually copy/paste into a browser in your computer.
{{% /md %}}
{{% /warning %}}

The instructions for deploying using the CLI are located at https://dashboard.heroku.com/apps/[cnetID]-cs220-lab7/deploy/heroku-git. We already have a git repository, so we'll follow the instructions for *Existing Git Repository*.

```
heroku git:remote -a [your app name]

```

So, we've set up Heroku for this app, but we haven't deployed it yet... Navigate to your app's webpage, and you'll see nothing is there.

In order to deploy, you should use:

```
$ git push heroku master
```

The `heroku git:remote` command you ran above added the `heroku` remote to your local repository, and pushing to it means that Heroku's servers will receive your code for the first time.

The version you just deployed happens to be a correct version of the app. We actually have a few tests that will run some basic checks to make sure the app is behaving as intended. You can run this tests simply by running this:

```
pytest
```

This should produce an output like this:

```
====================================== test session starts =======================================
platform linux -- Python 3.5.2, pytest-3.5.1, py-1.5.3, pluggy-0.6.0
rootdir: /var/tmp/borja/cs220-helloapp-2019, inifile:
plugins: metadata-1.7.0, json-0.4.0, html-1.17.0
collected 2 items

tests/test_greeting.py ..                                                                  [100%]

==================================== 2 passed in 0.02 seconds ====================================
```

Now, let's break our app. Edit the files `hello/templates/index.html` and replace `Hello` with `Howdy`. If you re-run the tests, one test will pass, but another will fail:

```
====================================== test session starts =======================================
platform linux -- Python 3.5.2, pytest-3.5.1, py-1.5.3, pluggy-0.6.0
rootdir: /var/tmp/borja/cs220-helloapp-2019, inifile:
plugins: metadata-1.7.0, json-0.4.0, html-1.17.0
collected 2 items

tests/test_greeting.py .F                                                                  [100%]

============================================ FAILURES ============================================
_________________________________________ test_greeting __________________________________________

client = <FlaskClient <Flask 'hello.main'>>

    def test_greeting(client):
        """
        Test that we get the correct greeting
        if we submit the form.
        """

        name = b"Random J. Hacker"
        greeting = GREETING + b", " + name + b"!"

        rv = client.post("/", data={"name": name})

        # Test that the resulting page contains the app name
        # and the correct greeting.
        assert APPNAME in rv.data
>       assert greeting in rv.data
E       assert b'Hello, Random J. Hacker!' in b'<!doctype html>\n<title>HelloApp</title>\n<link rel="stylesheet" href="/static/style.css">\n<nav>\n  <h1>HelloApp</h...h1>\n\n  </header>\n  \n\n<p>\n  Howdy, Random J. Hacker!\n</p>\n<p>\n  <a href="/">Again!</a>\n</p>\n\n\n\n</section>'
E        +  where b'<!doctype html>\n<title>HelloApp</title>\n<link rel="stylesheet" href="/static/style.css">\n<nav>\n  <h1>HelloApp</h...h1>\n\n  </header>\n  \n\n<p>\n  Howdy, Random J. Hacker!\n</p>\n<p>\n  <a href="/">Again!</a>\n</p>\n\n\n\n</section>' = <Response 294 bytes [200 OK]>.data

tests/test_greeting.py:33: AssertionError
=============================== 1 failed, 1 passed in 0.03 seconds ===============================
```

You don't need to understand everything that's going on here but, in a nutshell, the tests verified that the index page of our application works correctly, but one of the tests fail because the greeting we're receiving is "Howdy" instead of "Hello".

It's a good thing we have the tests to tell us this but, unfortunately, nothing is preventing us from deploying this broken app. In fact, go ahead and deploy the broken code:

```
$ git add hello/templates/index.html
$ git commit -m "Broke the Internet!"
$ git push heroku master
```

As you'll notice, you're still able to deploy your app. But it's now returning the wrong greeting, and millions of users are upset because they were expecting a polite "Hello" from the app, and now they're getting a much more folksy "Howdy", which seems to rub some of our users the wrong way.

Is there a way we could prevent this, without manually checking every time? It would be nice if we could just deploy automatically from our GitHub repo, and only after CI tests pass.

Before continuing, make sure that you also push to your GitHub repository:

```
$ git push
```

That way, we can check that you've followed the steps described in this task.


# Task 3: Create .travis.yml for cs220-helloapp-2019
[40 points]

As you remember from our [previous lab]({{< relref "lab6.md" >}}), we have a way to make sure our app passes all the tests every time we push.

For this, you should create a `.travis.yml` file in your `cs220-helloapp-2019` repo. With python, there's no need to build, so you should just define a test phase which runs the command `pytest` as its test script.

In the last task, you made the tests fail. You should ensure the CI job fails when the tests are failing.

Now, go back and fix the app so that they all pass. Before continuing, make sure you push your fixed app to both GitHub and to Heroku.

# Task 4: Deploy using Github Integration with Travis CI
[20 points]

Wouldn't it be convenient if we could deploy continuously, as soon as tests pass? You might think "well, what if we had a deploy phase in our Travis CI"? This is possible (see https://docs.travis-ci.com/user/deployment/heroku/), but it turns out Heroku makes it *even easier* than that. On your Heroku app dashboard, in the "Deploy" tab, select "GitHub - connect to GitHub" instead of "Heroku Git - Use Heroku CLI".

Then, you should be able to connect to GitHub using your GitHub account and repo name. Once you connect the repo, you should see an option that says "Automatic deploys" with a checkbox "Wait for CI to pass before deploy".

Make the tests fail again and push to GitHub with a simple `git push`. The CI tests should fail and, if you navigate to your URL, you'll see that the broken version has not been deployed.

{{% warning %}}
{{% md %}}
**Caution:** In the above `git push` step, *don't* push to Heroku as you did in previous tasks. What's happening here is that the Heroku service will now wait for tests to pass CI, and then automagically pull your code and deploy it. No need to manually push to Heroku.
{{% /md %}}
{{% /warning %}}

Before continuing, fix the tests and make sure your CI tests are passing again.

Now, we're going to make a change that doesn't make the tests fail, to verify the change is correctly deployed just by pushing to GitHub. If you look at the app, you'll see that the main page shows the title "What is your name?" followed by a form with a field titled "Name". That "Name" title seems a bit redundant, so we're going to remove it. Edit `hello/templates/index.html` and remove this line:

```
    <label for="name">Name</label>
```

Now, commit your changes and push to GitHub. Once the CI tests pass, your updated app should be available on Heroku, and you will be done with this lab! If your updated app doesn't deploy, check the "Activity" tab on your Heroku app dashboard, and see what the issue is: if it seems like it deployed correctly, you may simply need to wait a few minutes to see the website updated.

### Submitting your lab

Before submitting, make sure you've committed your changes to the `lab7/tasks.txt` file (remember you can run `git status` to check this). Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab7
    chisubmit student assignment submit lab7
