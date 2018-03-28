---
title: "Lab 1: Git"
date: 2018-01-28
publishdate: 2018-01-28
---

Git is a system used for developing software in a group. This system maintains files and all changes that are applied to them. You will each create an account on GitHub (if you do not already have one) and initialize a personal Git *repository* for this class that is hosted on a central server. The server stores the project files and stores all changes to those files *that have been uploaded to the repository*. We will be able to see any changes you upload to your repository, which allows us to provide help remotely, grade your programming assignments, and provide feedback.

Git tracks every version of a file or directory using *commits*. When you have made changes to one or more files, you can logically group those changes into a "commit" that gets added to your repository. You can think of commits as “checkpoints” in your work, representing the work you’ve done since the previous checkpoint. This mechanism makes it possible to look at and even revert to older versions of a file by going back to your code as it was when you “checkpointed” it with a commit.

When using Git, your basic working cycle will be:

* Log into a CS machine (or your machine if you have git installed)

* Change to your cmsc22000-spr-18-username directory

* Download updates from the Git server. In Git, this operation is called *pulling* from the server.

* Work on your files

* Add any new files and create a commit with any changes you have made

* Upload the commit to the Git server. In Git, this operation is called *pushing* to the server.

The course staff does not have access to any files stored in your home directory or files that you have not pushed to the Git server. All we can access are files that have been pushed to the Git server, so remember to always push your latest commits when you’re done or when you ask a question on Slack that will require us to look at your code.

## Creating an account

If you do not already have a GitHub account, create one at [https://github.com/join](https://github.com/join) and make sure to select the free plan.

## Initialize a repository

Create a repository.

mkdir cmsc22000-spr-18-<username>

cd cmsc22000-spr-18-<username>

Create a dummy file to seed your repository with.

touch test.txt

Initialize the repo for git.
git init

Add, commit, and push your repository to initialize the repo on the server. (We will go into what these commands mean later on.)
git add test.txt
git commit -m "first commit"
git remote add origin https://github.com/<username>/<reponame>.git
git push -u origin master

Enter your username and password when prompted.

In the future, you can configure your machine so that you do not need to enter your username time you push files.

git config --global user.name "John Doe"

git config --global user.email johndoe@example.com

## Creating a commit

Creating a commit is a two-step process. First, you have to indicate what files you want to include in your commit. Let’s say we want to create a commit that only includes the test.txt file that you created earlier. We can specify this operation explicitly using the git add command from the Linux command-line:

git add hello_world.py

There are various shortcuts that will allow you to add all of the files in a directory, such as git add . or git add --all. Using these commands is poor practice, because you can easily end up adding files that you did not intend. Instead, it is better to add files explicitly when you create them and then use the command from the Linux command-line:

git add -u

when you want to add any file that has changed since your last commit.

To create the commit, use the git commit command. This command will take all the files you added with git add and will bundle them into a commit:

git commit -m "Created test.txt"

The text after the -m is a short message that describes the changes you have made since your last commit. Common examples of commit messages might be "Finished lab 1" or “Implemented insert function for data struct”.

Note

If you forget the -m "Comment" at the end then Git will think that you forgot to specify a commit message. It will graciously open up a default editor so that you can enter such a message. On the CS machines this editor is vim. To escape the vim view, press ZZ (shift-z twice). Now try git commit again and don’t forget the -m "Comment".

Once you run the above command, you will see something like the following output:

[master 99232df] Created test.txt
1 file changed, 1 insertion(+), 1 deletion(-)

You’ve created a commit, but you’re not done yet: you haven’t uploaded it to the server yet. Forgetting this step is actually a very common pitfall, so don’t forget to upload your changes. You must use the git push command for your changes to actually be uploaded to the Git server. *If you don’t, the graders will not be able to see your code*. Simply run the following command from the Linux command-line:

git push

You should see something like this output:

Counting objects: 7, done.
Delta compression using up to 16 threads.
Compressing objects: 100% (4/4), done.
Writing objects: 100% (4/4), 452 bytes, done.
Total 4 (delta 1), reused 0 (delta 0)
To git**@git**-dev.cs.uchicago.edu:cmsc12100-aut-17/username.git
   c8432e4..99232df  master -> master

You can ignore most of those messages. The important thing is to not see any warnings or error messages.

You can verify that our Git server correctly received your commit by visiting your online repository on GitHub:

https://github.com/username/repo-name

Where username should be substituted by your GitHub username and repo-name should be replaced with your repository’s name.

This URL takes you to the web frontend of your Git repository. More specifically, the above URL will show you the contents of your repository, exactly as it appears on the Git server. If you see a commit titled "Created test.txt", then your commit was successfully uploaded.

In general, if you’re concerned about whether the graders are seeing the right version of your code, you can just go to the above URL. Whatever is shown on that page is what the graders will see. If you wrote some code, and it doesn’t show up in the above URL, make sure you didn’t forget to add your files, create a commit, and push the most recent commit to the server.

## Pulling your changes from the server

If you have done work and committed it to the server from a lab computer and now wish to work on your machine (or vice versa), you will need to pull these changes from the server to your machine. To download these changes, run this command from inside your repository directory:

git pull

It is important that you commit and push your changes after every session and that you pull before you start to do any work.

Note

Your output may vary from our sample output slightly. Do not worry about the difference unless you see an error message or a warning message.

## git add revisited and git status

So far, we’ve created a single commit with a single file that we created. Now, create a copy of that file:

cp test.txt example.txt

Is example.txt part of your repository? You can use the following command to ask Git for a summary of the files it is tracking:

git status

This command should output something like this:

*# On branch master*
*# Changes not staged for commit:*
*#   (use "git add <file>..." to update what will be committed)*
*#   (use "git checkout -- <file>..." to discard changes in working directory)*
*#*
*#   modified:   test.txt*
*#*
*# Untracked files:*
*#   (use "git add <file>..." to include in what will be committed)*
*#*
*#   example.txt*
no changes added to commit (use "git add" **and**/**or** "git commit -a")

The exact output may vary depending on any other commands you’ve executed. However, the important thing is that there are two types of files listed here:

* Changes not staged for commit: This is a list of files that Git knows about and have been modified since your last commit, but which have not been added (with git add).

* Untracked files: This is a list of files that Git has found in the same directory as your repository, but which Git isn’t keeping track of.

* You may see some automatically generated files in your Untracked files section. Files that start with a pound sign (#) or end with a tilde should *not* be added to your repository. Files that end with a tilde are backup files created by some editors that are intended to help you restore your files if your computer crashes. In general, files that are automatically generated should not be committed to your repository. Other people should be able to generate their own versions, if necessary.

To add a previously untracked file to your repository, you can just use git add (unlike the previous commands, don’t actually run this just yet; you will be doing a similar exercise later on):

git add example.txt

If you re-ran git status you would see something like this:

*# On branch master*
*# Changes to be committed:*
*#   (use "git reset HEAD <file>..." to unstage)*
*#*
*#   new file:   example.txt*
*#*
*# Changes not staged for commit:*
*#   (use "git add <file>..." to update what will be committed)*
*#   (use "git checkout -- <file>..." to discard changes in working directory)*
*#*
*#   modified:   test.txt*

Notice how there is now a new category of files: Changes to be committed. Adding example.txt not only added the file to your repository, it also staged it into the next commit (which, remember, won’t happen until you actually run git commit).

The git status command reports the status on the local copy of the full repository. If you wish to look at the status of a smaller part of the repository (the directory you are working in for example), you can add a path name to the status command. For example:

git status .

reports the status of the current directory (a single dot is the path used to refer to the current directory).

## Unstaging, discarding changes, and removing files (optional, skip if short on time)

Take a closer look at the git status output above. Git is providing you hints in case you want to undo some of your work.

For example, you can use git reset example.txt to unstage the file. Doing so reverses git add example.txt so you can create a commit only of changes to other files. This is good practice if you think the changes you made to example.txt don’t logically go in the commit you are going to make.

Another useful git command is git checkout. This command will undo modifications to files. If you again look at the above git status output, you will see in the last line that test.txt was modified. To undo any changes to the file, type git checkout test.txt. This command will revert the file content to match the last commit you made in your repository’s history

Finally, if you would like to remove a file from your directory, using git rm test.txt combines the result of doing rm test.txt and git add test.txt.

## Looking at the commits log (optional, skip if short on time)

Once you have made multiple commits, you can see these commits, their dates, commit messages, author, and an SHA-1 hash by typing git log. This command will open a scrollable interface (using the up/down arrow keys) that you can get out of by hitting q.

There are also many flag options for git log that will specify your terminal output as well as for the other git commands that you can look into if interested.

## Exercises

1. You have already created the test.txt file in your directory. Now modify it by adding some text in the file. Verify these changes by using the command git status. You should see it under Changes not staged for commit.

2. Use git add and git commit to create a commit that includes only the test.txt file. A good commit message would be "Added my name as Author in test.txt".

3. Upload your work to the server using git push.

4. Verify that this file was sent by again using the command git status. You should see that the file test.txt is no longer listed.

5. If you have not already done so, use cp to make a copy of test.txt named example.txt.

6. If you run git status, example.txt should show up under Untracked files. Add it to the repository using git add.

7. Run git status again. Is example.txt in a different category of files now? Create a file named README.txt and write your answer in there. Add README.txt to your repo.

8. Although we have added both example.txt and README.txt, we have not yet created a commit. Create a commit and push it to the server.

9. Run git status a final time to verify that example.txt and README.txt were committed (if so, you should not see either in any category of files)

10. Run git push to upload your changes to the server.

**We strongly recommend you to check in and push changed files as often as possible, especially if you finished some work and are about to log off a computer. This way the latest files are accessible from any other computer where your repository is set up.**

