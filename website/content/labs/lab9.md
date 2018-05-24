---
title: "Lab 9: Documentation and Logging"
date: 2018-01-26
publishdate: 2018-01-26
---

**Due:** Thursday, May 31st, 4pm

This lab will be divided into two distinct parts: one focused on documentation, and another focused on logging. In the first one, you will automatically generate documentation for libgeometry and, in the second one, we will provide you with a program that simulates playing Tic-Tac-Toe under several different strategies, and you will add logging code to better track the progress of the simulation.


# Part I: Documentation
As we saw in class, there are many different ways of producing documentation, from adding a simple README file to your project, to writing more comprehensive documentation. There are many frameworks for writing and/or publishing documentation, like [Sphinx](http://www.sphinx-doc.org/), [Read The Docs](https://readthedocs.org/), and [GitHub Pages](https://pages.github.com/). If you're curious to see what these looks like, check out the following examples:

* The [chisubmit documentation](http://chi.cs.uchicago.edu/chisubmit/) is produced with Sphinx, which involves using a [lightweight markup language](https://en.wikipedia.org/wiki/Lightweight_markup_language) called [reStructuredText](http://docutils.sourceforge.net/rst.html). You can see the source code of the chisubmit website here:
https://github.com/uchicago-cs/chiwebsite/tree/master/chisubmit (note: when looking at individual files, you will need to click "Raw" to see the original reStructuredText source)
* The CS 220 website (where you are reading this lab) is written in a markup language called [Markdown](https://en.wikipedia.org/wiki/Markdown), which is also used in many other platforms, including GitHub. You can see the source code for the CS 220 website here: https://github.com/uchicago-cs/cmsc22000/tree/master/website/content. You can see the source code for this lab here: https://raw.githubusercontent.com/uchicago-cs/cmsc22000/master/website/content/labs/lab9.md The CS 220 website itself is produced using a tool called [Hugo](https://gohugo.io/) which is not specifically designed for producing documentation (it is a more general-purpose tool for producing websites).

In this lab, we will focus on tools that produce documentation automatically from code. Sphinx can actually be used for this purpose, but only with Python code. We will instead use a tool called [Doxygen](http://www.stack.nl/~dimitri/doxygen/), which generates documentation from source code in a variety of languages. 

While tools like Doxygen can generate documentation based on any code (as long as they support the language it's written in), they are specially useful when we annotate the code wth comments that Doxygen can parse and then include in the generated documentation. In this lab, we will do this with the libgeometry code.

## Task 0: Setup
[0 Points]

You should already have the "upstream" remote set up in your repository. If you do, simply run

    $ git pull upstream master

to get the files for this lab. If you don't have the "upstream" remote set up, follow task 0 from [Lab 2]({{< relref "lab2.md" >}}).

The `lab9` directory contains a `libgeometry` directory with an updated version of `libgeometry` that has been documented in a way that allows Doxygen to automatically produce documentation based on it.

## Task 1: Creating the Doxygen configuration file

[10 points]

Doxygen stores all its configuration information in a configuration file, typically named `Doxyfile`. While you can create the file manually, you can also create a configuration template using the `doxygen` command. Before we do this, let's create a `docs` directory inside our `libgeometry` directory. Make sure to run the following commands inside the same directory that contains the `include` and `src` directories:

	$ mkdir docs/
	$ cd docs/
	$ doxygen -g

That last command will generate a `Doxyfile` file. If you open it, you will see it has a large number of options we can modify (Doxygen refers to options as "tags"). Fortunately, we will only have to modify a few tags. The value for a tag is specified like this:

    TAGNAME = VALUE 

Or, if multiple values are possible, like this:

    TAGNAME = VALUE1 VALUE2 …

Comments are prepended by the `#` character.

Try running Doxygen inside the `docs` directory (by default, it will read its configuration from the  `Doxyfile` file in the same directory):

	$ doxygen

This will create an `html` directory. If you open the index.html file in that directory using a browser, you will see it contains documentation for "My Project" (or rather, it contains no documentation for that project). We need to edit the `Doxyfile` to tell Doxygen where to look for our code. We will do this in the next task; before continuing make sure you add the `Doxyfile` to Git:

	$ git add Doxyfile
	$ git commit -m"Added basic Doxyfile"

## Task 2: Customizing the Doxygen configuration
[10 points]

Let's go ahead and change the following tags in the file (make sure to find them and set them to the values shown below):

    PROJECT_NAME           = "libgeometry"
    INPUT                  = ../
    FILE_PATTERNS          = *.c *.h
    RECURSIVE              = YES

These tags do the following:

* `PROJECT_NAME` specifies the project name that will be displayed in the generated documentation.
* `INPUT` specifies the root directory of the project (in this case, the parent directory of the `docs` directory, i.e. `../`)
* `FILE_PATTERNS` specifies the files that Doxygen should try to document automatically. Since libgeometry is a C project, we only want to look at files with a `.c` or a `.h` extension.
* `RECURSIVE` specifies that we want Doxygen to go into subdirectories when searching for files to generate documentation from.

This is only the tip of the iceberg, and there are a ton of other ways you can specify how the file is generated. A list of all the tags can be found here.
https://www.stack.nl/~dimitri/doxygen/manual/config.html 

Go ahead and re-run doxygen:

	$ doxygen
And re-load the `index.html` file inside the `html` directory. You will now see a "Classes" tab you can click on. This will show you the structs (or classes, in object oriented parlance) in your code. You should see two types: `point_t` and `polygon_t`. If you click on polygon_t you'll see that page contains abundant documentation about the `polygon_t` struct, its fields, and the functions associated with it. It even shows a helpful diagram showing how `polygon_t` relates to our other types; in particular, it shows that `polygon_t` has a field called `points` that relies on the `point_t` type. We can even click on `point_t` type to see the documentation for that type.

If you take a look at `point.h` and `polygon.h`, you'll see that the code comments in the structs and functions seem to follow a very specific format. For example:

    /** 
     * \memberof polygon_t
     * \brief Adds a point (expressed as x, y coordinates) to a polygon
     *
     * \param poly: The polygon
     * \param x: x coordinate of the point to add
     * \param y: y coordinate of the point to add
     *
     * \return 0 on success, 1 if an error occurs.
     */
    int polygon_add_xy(polygon_t *poly, double x, double y);

If you look up `polygon_add_xy` in the Doxygen-generated documentation, you'll see that it shows the same information we specified in the above comment. In the next task we'll learn more about this comment syntax, and will document a few functions of our own. Before continuing, make sure you commit the changes tp `Doxyfile`:

	$ git add Doxyfile
	$ git commit -m"Updated Doxyfile"

## Task 3: Documenting your code
[30 points]

To document a piece of code in a way that Doxygen can parse it, we need to add a *comment block* with *commands* that Doxygen understands. A comment block looks like this:

    /** 
     * \command1 ...
     * \command2 ...
     * \command3 ...
     */

It looks just like a regular C comment, but that second `*` at the start of the comment is deliberate: that is how Doxygen knows that it needs to parse the comment in search of commands. Note that there are other ways to format comments (take a look at https://www.stack.nl/~dimitri/doxygen/manual/docblocks.html#cppblock if you're curious).

If we are documenting a function, we would place the comment block immediately above the function, with commands that provide information about that function. For example:

* `\brief`, which gives a brief description of the function
* `\param`, to describe a parameter
* `\return`, to describe a return type
* `\memberof`, to specify that the function is associated with a specific type (we need to do this in C, as functions are not explicitly associated with a type, as they are in object-oriented languages)


Some other useful commands include the following:

* `\def`, used to document for a #define macro
* `\file`, used for documenting a file
* `\enum`, used for enums
* `\typedef`, for typedefs

You can find examples of most of the above throughout the provided libgeometry code. A full list of special commands can be found at https://www.stack.nl/~dimitri/doxygen/manual/commands.html. Doxygen supports multiple languages, so not all of these will necessarily apply to C.

Another style of comment is the inline comment, which is commonly used when documenting the variables in a struct. For example:

    typedef struct {
        double x; ///< x coordinate
        double y; ///< y coordinate
    } point_t;

In this comment we don't use a command, and simply provide a description of the variable that is being documented.

In this task, you will document your `segment_t` and `circle_t` types from previous labs. Your `lab5` directory should contain your most recent work on libgeometry. Simply copy any code related to `segment_t` and `circle_t` into your `lab9/libgeometry` directory. Please note that the version provided in `lab9` does not include any of the intersection-related code in `point.c` or `point.h`. Depending on how you refactored your code earlier in the quarter, you may need to also copy some of your code into `point.c` or `point.h`. Please note that it is ok if you do not copy over any of the tests you wrote.

Next, you should add Doxygen-style comment blocks in your `segment.h` and `circle.h` files. Each struct comment should include a brief description of the struct, and each function comment should include the following:

* A description of the function
* Each parameter (including a brief description of that parameter)
* The return value (including a brief description)

In your C (.c)  files, you should add a comment to see the header file (as we have done in the other files). 

Now to generate the documentation, run:

    doxygen Doxyfile

And it will generate the documentation in html! To see it, go to the html directory it generated and click on index.html. The Classes tab should now include your segment and circle types. Make sure that all your functions appear there!

Before continuing, make sure to add and commit the additional segment/circle files you added.

# Part II: Logging

Over the course of the projects, many of you have come across the desire to pepper your code with `printf` statements to see a "trace" of your program running. This is a great instinct; in this part of the lab, we're going to refine that notion with more powerful tooling to create a more elegant solution.

## What is logging?

Logging is, in essence, nothing more than controlled `printf`s, separated into *log levels*. Many of you have independently discovered this concept in the form of normal/quiet/verbose modes for your programs. A typical logging library will provide several standard log levels:

- `FATAL`: reserved for errors that crash the program or otherwise signify completely incorrect behavior;
- `ERROR`: for other non-fatal errors;
- `WARN`: for bad inputs, etc that are not errors but could result in errors down the line;
- `INFO`: for general informational messages (e.g. "starting server", "accepted connection", "file scan completed", etc);
- `DEBUG`: for program structure (e.g. "entering send_message function", messages that print for each iteration in a loop, etc);
- `TRACE`: for printing out the contents of data structures and other program values.

The order of these log levels is relevant: in the above list, each log level provides more detailed information than the log level before it. A typical logging library will allow you to *set* the log level, which means it will only print all the log messages at *or above* the specified log level. So, setting the log level to `INFO` will print out all the log messages at the `FATAL`, `ERROR`, `WARN`, and `INFO` levels. When debugging the program, you would set the log level to a deeper level, like `DEBUG` or `TRACE` to print more information during the execution of your program.

In this lab, we will use [this](https://github.com/rxi/log.c) log library which provides all of the above functionality (and a little more). In particular, we will take a program to simulate Tic-Tac-Toe games and add logging so we can see the progress of the simulation. The program is in the `lab9/tictactoe` directory. Before continuing, take a moment to read the README file in that directory. Make sure you can build the program, and run it as described in the README file.

# Task 4: Setup
[10 points]

In order to actually use the logging library, we need to import it into our repository. We could copy the files in, but that's a pretty inelegant solution. We instead will use a **submodule**. Run the following command from the root of your repository:

```
$ git submodule add https://github.com/rxi/log.c lab9/tictactoe/lib/log.c
```

{{% warning %}}
**Caution**: the above command creates a *folder* called `log.c`, *not* a file. The name of the whole library is `log.c`, which is really confusing because it sounds like a filename.
{{% /warning %}}

# Task 5: Up and running with `log.c`
[40 points]

Your task is simple: read the code and figure out what it does, and then add logging statements at the appropriate log levels throughout the code. You can `#include "log.c/log.h"` (again - confusing library name) to get those functions, and you can check out the `log.c` [GitHub page](https://github.com/rxi/log.c) for documentation. 

To select the log level, we have already added a `-v` parameter to the program that allows you to control the "verbosity" of the program. This is a common command-line convention, where `-v` means "be verbose", `-vv` means "be very verbose", `-vvv` means "be super verbose", etc. Inside the `main()` function, the `verbosity` variable will contain the number of `v`s that were specified in the command-line. You can use this to set the log level appropriately. For example, `-v` could correspond to `INFO`, `-vv` to `DEBUG`, and `-vvv` to `TRACE`. This allows us to easily control the amount of output (and the level of detail) of our program.

As you write log statements, you should have in mind three use cases:

1. A user running your program: if no `-v` option is specified, the user shouldn't see anything except fatal errors. Ensure that running your program this way does not print anything except the result summary, or any fatal errors that occur. Note: you do not need to alter the `printf` statements that print the summary. Those are part of the normal output of the program, and not something we would print using a logging library.
2. A developer working on your program (yourself): while developing new features, you likely want to see a rough trace of the structure of your program, without overwhelming yourself with output. There isn't really a clear brightline here on what belongs at the `WARN` through `DEBUG` log levels - use your best judgement.
3. A developer debugging your program (yourself): note that debugging is a distinct case from normal development. When debugging, it's helpful to get as much output as possible, to be able to inspect the output more clearly. The `TRACE` log level should thus contain the pretty-printed contents of all important data structures and variables whenever they are modified. Take into account that we already provide a function that pretty-prints a tic-tac-toe board, but which does not use a logging library to do so. You are welcome to modify this function so that it uses log functions.

You might notice that two of these three use cases are specifically aimed at *you*: you should write these log statements with your future self in mind (e.g., if you wanted to implement a new strategy and wanted to use logging to see how it unfolds step by step). When testing those use cases, make sure you set the `-n` option to a low value, to avoid overwhelming your terminal with output.

Besides adding the log statements, add a file called `lab9/tictactoe/tasks.txt`, and write down your methodology in that file. Explain what kinds of log statements you included, how you classified those statements in terms of the log levels, etc. There's no need to dig into every single log function call; simply explain your thought process.

### Submitting your lab

Don't forget to add any new files you added in this lab, and to commit and push all your changes (remember you can run `git status` to check this). 

Finally, Make sure you've set up the `chisubmit` tool as described in [How to submit your labs]({{< relref "submit.md" >}}), and then run the following:

    chisubmit student assignment register lab9
    chisubmit student assignment submit lab9

