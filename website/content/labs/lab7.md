---
title: "Lab 7: Deployment"
date: 2018-01-26
publishdate: 2018-01-26
draft: false
---

**Due:** Wednesday, May 27th, 8pm

Last week, you learned about Continuous Integration, which deals with how application code makes it to the master branch. But how do our applications make it to the *real world*, where other people can use them?

Deployment refers to the processes by which software systems are made available for use (a related term, *delivery*, refers to making software available specifically to end-users). The exact deployment pipeline can vary from one project to another. For example, in a large financial company, deploying business management software might require system architects to come and physically upload software on the machines. On the other hand, if you're deploying a small web application, you just need a way to get your application from your computer to a server where other users can access it.

In this lab, you will deploy an application to [Heroku](https://www.heroku.com/), one of the most popular services for hosting web apps. More specifically, you'll be deploying HelloApp, the small [Flask](http://flask.pocoo.org/) web application we demonstrated in this week's lectures (you can see our deployed version here: ://cs220-helloapp.herokuapp.com/). Don't worry: while the app is implemented in Python, no Python knowledge is necessary for this lab.


## Creating your lab repository

Like previous labs, we will provide you with an  *invitation URL* that will allow you sign up for the lab assignment on GitHub, and which will result in the creation of a repository called `2020-lab7-GITHUB_USERNAME` inside our `cmsc22000-labs` organization on GitHub. Your repository will be seeded with some files for the lab and, more specifically, will contain the code for HelloApp.


# Task 1: Create a Heroku App
[20 points]

Heroku is a common service used to host web applications. For this task you'll sign up for a (free) account and use it to deploy an app with an Internet-reachable URL.

1. Go to https://signup.heroku.com/login
2. Sign up and mark your "role" as "student". You will need to confirm your account, and then create a password.

Once you've created your account, you're ready to create a Heroku app.

1. Go to your dashboard, https://dashboard.heroku.com/apps
2. Click the button that says "New" and then click on "Create new app"
3. Under "app-name" title your app `CNETID-cs220-lab7` (where `CNETID` should be replaced with your CNetID). This means that the url for your app will be `https://CNETID-cs220-lab7.herokuapp.com`

You've created your app! But navigate to `https://CNETID-cs220-lab7.herokuapp.com`. As you can see, there's nothing there. In the coming tasks we will get  HelloApp up and running on this URL.

Before continuing, enter the URL of your Heroku app on Gradescope.

# Task 2: Deploy using Heroku CLI
[20 points]

In class, we saw that we can deploy an app to Heroku simply by pushing to their Git repository. Your local `2020-lab7-GITHUB_USERNAME` repository is currently configured to push only to GitHub, so we need to set it up to also push to Heroku. We can do this using a command-line tool provided by Heroku.

First, you'll need to log into Heroku like this (make sure you run this command *inside* your `2020-lab7-GITHUB_USERNAME` directory):

```sh
$ heroku login
```

{{% warning %}}
The `heroku` command is available on the CSIL machines and the `linux.cs` servers.

If you are running inside the CS VM, then you will need to install Flask and the `heroku` command by running the following:

```sh
$ sudo -H pip3 install flask
$ sudo snap install --classic heroku
```

If you are using the Headless VM setup, take into account that the `heroku login` command will attempt to open a browser to log you into Heroku, which is not possible from headless mode. Instead, the command will print out a URL, which you will have to manually copy/paste into a browser in your computer.
{{% /warning %}}

The instructions for deploying using the CLI are located at `https://dashboard.heroku.com/apps/CNETID-cs220-lab7/deploy/heroku-git` (under "Deploy using Heroku Git"). We already have a git repository, so we'll follow the instructions for *Existing Git Repository*.

```sh
$ heroku git:remote -a CNETID-cs220-lab7
```

So, we've set up Heroku for this app, but we haven't deployed it yet... Navigate to your app's webpage, and you'll see nothing is there.

In order to deploy, you should use:

```sh
$ git push heroku master
```

The `heroku git:remote` command you ran above added the `heroku` remote to your local repository, and pushing to it means that Heroku's servers will receive your code for the first time. The deployment will take about a minute or so and, once it's done, you should see a message like this:

```sh
remote: -----> Launching...
remote:        Released v3
remote:        https://CNETID-cs220-lab7.herokuapp.com/ deployed to Heroku
remote: 
remote: Verifying deploy... done.
To https://git.heroku.com/CNETID-cs220-lab7.git
 * [new branch]      master -> master
```

Go ahead and go to `https://CNETID-cs220-lab7.herokuapp.com/`. HelloApp should now be running correctly at that URL.

The version you just deployed happens to be a correct version of the app. We actually have a few tests that will run some basic checks to make sure the app is behaving as intended. You can run this tests simply by running this:

```sh
$ pytest
```

This should produce an output like this:

```sh
====================================== test session starts =======================================
platform linux -- Python 3.5.2, pytest-3.5.1, py-1.5.3, pluggy-0.6.0
rootdir: /var/tmp/borja/cs220-helloapp-2019, inifile:
plugins: metadata-1.7.0, json-0.4.0, html-1.17.0
collected 2 items

tests/test_greeting.py ..                                                                  [100%]

==================================== 2 passed in 0.02 seconds ====================================
```

Now, let's break our app. Edit the file `hello/templates/index.html` and replace `Hello` with `Howdy`. If you re-run the tests, one test will pass, but another will fail:

```sh
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

```sh
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

That way, we can check that you've followed the steps described in this task. You do not need to enter anything into Gradescope for this task.


# Task 3: Create .travis.yml for HelloApp
[40 points]

As you may remember from our [previous lab]({{< relref "lab6.md" >}}), we have a way to make sure our app passes all the tests every time we push.

For this, you should create a `.travis.yml` file in your `2020-lab7-GITHUB_USERNAME` repo. With Python, there's no need to build, so you should just define a single job that runs the command `pytest` as its test script (in a Linux environment)

In the last task, you made the tests fail. Commit and push your .travis.yml file and make sure the CI job fails specifically because the tests are failing (you will need to inspect the job log to see that `pytest` is failing in your CI build). Take the URL of the failed build, and enter it in Gradescope. 

Now, go back and fix the app so that they all pass. Then, push your fixed app to both GitHub and to Heroku. Take the URL of the successful build, and enter it in Gradescope.

# Task 4: Deploy using Github Integration with Travis CI
[20 points]

Wouldn't it be convenient if we could deploy continuously, as soon as tests pass? You might think "well, what if we had a deploy phase in our Travis CI"? This is possible (see https://docs.travis-ci.com/user/deployment/heroku/), but it turns out Heroku makes it *even easier* than that. On your Heroku app dashboard, in the "Deploy" tab, under "Deployment method", select "GitHub - connect to GitHub" instead of "Heroku Git - Use Heroku CLI".

Then, you should be able to connect to your repo. To do this, you need to first select the `cmsc22000-labs` organization under "Search for a repository to connect to", and then enter your repository's name (`2020-lab7-GITHUB_USERNAME`) in the text field (make sure to click the "Search" button so Heroku will search for your repository). 

Once you connect the repo, you should see an option that says "Automatic deploys" with a checkbox "Wait for CI to pass before deploy". Make sure that checkbox is checked, and then click on "Enable Automatic Deploys"

Make the tests fail again and push to GitHub with a simple `git push`. The CI tests should fail and, if you navigate to your URL, you'll see that the broken version has not been deployed.

{{% warning %}}
**Caution:** In the above `git push` step, *don't* push to Heroku as you did in previous tasks. What's happening here is that the Heroku service will now wait for tests to pass CI, and then automagically pull your code and deploy it. No need to manually push to Heroku.
{{% /warning %}}

Before continuing, fix the tests and make sure your CI tests are passing again.

Now, we're going to make a change that doesn't make the tests fail, to verify the change is correctly deployed just by pushing to GitHub. If you look at the app, you'll see that the main page shows the title "What is your name?" followed by a form with a field titled "Name". That "Name" title seems a bit redundant, so we're going to remove it. Edit `hello/templates/index.html` and remove this line:

```
    <label for="name">Name</label>
```

Now, commit your changes and push to GitHub. Once the CI tests pass, your updated app should be available on Heroku shortly aftewards. On your app dashboard on Heroku, you can go to the "Activity" tab to see whether your latest commit has been deployed (this tab can also provide details on why an app wasn't deployed).

For this task, you just need to make sure that you've pushed your code to GitHub as instructed above.

### Submitting your lab

In this lab, you just need to enter a few URLs into Gradescope (make sure you've done so at the points instructed above). You should also make sure you've pushed your code to GitHub (but will not be submitting your code through Gradescope; we just need to check that you've made the commits we expected you to make).

