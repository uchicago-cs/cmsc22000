---
title: "How to submit your labs"
date: 2018-01-28
publishdate: 2018-01-28
---

You will be submitting your labs using a tool called `chisubmit` that is available on the CS machines. Before using this tool, you first need to enable it inside your local repository. Just go into your local repository directory, and run the following:

    chisubmit init

When asked for your username and password, just enter your CNetID and password. If there are no errors, you will now be able to run chisubmit from inside that directory.

To submit a lab, it will typically be enough for you to push all your files to the GitLab server and then run the following from the directory where you ran `chisubmit init`:

    chisubmit student assignment register labX
    chisubmit student assignment submit labX

(where `X` is the lab number)

All labs will be due at **4pm** on the day of the next lab. You get two free 24-hour extensions to use throughout the quarter. You do not need to ask permission to use these extensions, or notify us that ou are using them: the `chisubmit` system will handle this automatically.

For more details on using chisubmit, please see the documentation available here: http://chi.cs.uchicago.edu/chisubmit/students.html Please note that everything before "Submitting an assignment" does not apply to you. However, if you do ever need to submit with an extension, please make sure you've read and understood how chisubmit handles this situation (in particular, you want to avoid being in a situation where you make a submission and, before re-submitting, the graders start grading your prior submission).
