---
title: "Lab 5: Testing"
date: 2018-01-26
publishdate: 2018-01-26
draft: true
---

**Due:** Thursday, May 3rd, 4pm

By this point in your CS careers, you’re probably all familiar with this kind of `C` development workflow:

1. Write a bunch of code
2. Hope it works
3. Run `gcc`
4. `gcc` is **a n g r y**
5. Fix compile errors
6. Run program
7. It segfaults, awesome
8. Fix segfault
9. Now my tree has all kinds of incorrect values but I don’t know how they got there, and I don’t know what part of my code is wrong
10. Rip all hair out
11. Go live in the woods
12. Finally at peace

This lab is all about **testing**, a practice that aims to un-suckify the above workflow. Generally speaking, there are two kinds of tests: **unit** and **integration**. **Unit tests** check the correctness of one specific function: for example, in your system design lab, a test that checks the correctness of the `is_user_in_channel()` function would be a unit test. **Integration tests** check the correctness of an entire system: for example, a test that sets up a mock chat server and two users, has them log on, and send a message to each other would be an integration test. The combined assurances of good unit tests and good integration tests give us confidence that the software we write is correct.

By the end of this lab, you’ll have experience writing unit tests, as well as an appreciation for their importance. You’ll be writing tests for existing code, as well as using the practice of **Test-Driven Development** to develop new code.

# Task 0: Setup
This lab will use the `libgeometry` library. We’re going to import your `libgeometry` code from lab 2, so that we can write tests for the `segment` code that you refactored back in lab 2. If you didn’t finish lab 2 completely, now would be a good time to go back and make sure it’s squared away before starting here. To import your lab 2 code:

```sh
$ cp lab2/libgeometry lab5
$ git add lab5
$ git commit -m “Starting lab 5”
```

{{% warning %}}
**Note**: This lab contains two primary tasks, both of which will be completed in the same directory - there won’t be `task1` and `task2` directories this time around. Everything should happen in the `lab5` directory.
{{% /warning %}}

# Task 0.5: A bit about `criterion`
Let’s learn a little bit about how our testing framework of choice (`criterion`) works. Consider the following sample tests:

```c
Test(foo, add)
{
    int x, y;

    x = 4;
    y = 5;

    cr_assert_eq(x + y, 9, “4 + 5 should be 9!”);
    cr_assert_eq(x + y, y + x, “Addition should be commutative!”);
}

Test(foo, subtract)
{
    int x, y;

    x = 2;
    y = 10;

    cr_assert_eq(y - x, 8, “10 - 2 should be 8!”);
    cr_assert_eq(x - y, -8, “2 - 10 should be -8!”);
}
```

Let’s unpack what’s going on here. First of all, `Test` is actually a *macro*, not a function. We’re not defining two functions both called `Test`, we’re calling the `Test` macro twice. `Test` takes two arguments (strictly speaking it actually supports many more, but for our purposes we’ll only need these two): a **suite name** and a **test name**. The **suite name** is just the name of the relevant context: if you take a look at `test_point.c` and `test_polygon.c`, you’ll see that the suite names are just `point` and `polygon`. The **test name** should just be a short identifier of what the test is testing.

Now let’s discuss the meat of these tests. Each test makes two **assertions** and exits. An **assertion** tests the validity of a given statement, and panics (causes the test to fail) if the statement is invalid. The way we make an assertion in `criterion` is by calling any one of a number of functions prefixed by `cr_assert` (you can find a full reference [here](https://criterion.readthedocs.io/en/master/assert.html#assertions-ref)). These tests use `cr_assert_eq`, which takes 3 arguments. It checks whether the first argument is equal to the second, and if not, causes the test to fail and prints out the error message given in the third argument (for those of you who took 151, this is very similar to Racket’s `check-expect` function).

# Task 1: Testing existing code
In this task, you’re going to write tests for the code you wrote in lab 2. You might be wondering: “when we were working on lab 2, didn’t we have to debug test failures? Why are we writing new tests?” Take a look inside the `tests` folder, and you’ll notice there are only two test files: `test_point.c` and `test_polygon.c`. Inside of `test_polygon.c`, there are numerous tests that indirectly call `segment_intersect`, but it would be nice to test that code directly to catch errors as early as possible (known as a **unit test**). The reason lab 2 was difficult to debug was because there were no **unit tests** for the `segment` code, making it hard to isolate exactly what was going wrong.

Create a new file in the `tests` directory called `test_segment.c`. You’ll need a few `#include` statements to get started:

```c
#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "point.h"
#include "segment.h"
```

{{% warning %}}
**Warning**: From now on, you must do all of your work over `ssh`, or in CSIL, or using the [department’s virtual machine](https://piazza.com/class/jf8q65bhmcg6gh?cid=34). Each of those environments have the `criterion` library properly set up and ready to go. While it is possible to install `criterion` on an unsupported machine, we cannot make any guarantees about it, which would defeat the purpose of testing.
{{% /warning %}}

You will also need to modify the `Makefile` in the `tests` directory to add your new file.

{{% warning %}}
**Caution**: There are *two* `Makefile`s in this project! There’s the root-level `Makefile` for building the library, but then there’s also a `Makefile` in the `tests` directory specifically for building test files. You should only modify the latter.
{{% /warning %}}

It’s time to write your first tests! In your `test_segment.c` file, write tests for each function in `segment.c` (that is, `segment_new`, `segment_init`, `segment_free`, `on_segment`, `orientation`, and `segment_intersect`). The former three of those functions should only need one test case, while the latter three will need multiple tests to be **covered** completely (in code with conditional branches, **coverage** is simply the notion that you should have a test case for each branch in the function). You may find it helpful to look at the other test files that are already present (`test_point.c` and `test_polygon.c`).

In addition to these tests, you should also submit a `task1.txt` file explaining each of the tests you created. For each test you write, include a summary of what the test checks for, as well as what behavior the test proves correct. For the `foo` examples above, I might write something like:

> The `add` and `subtract` tests check that arithmetic logic in `C` works
> correctly. Each of the tests check that a simple arithmetic operation produces
> the correct result, and the `add` test additionally (no pun intended) checks
> that addition is commutative. If these tests pass, we can confidently use the
> `+` and `-` operators in our `C` code.

# Task 2: Test-Driven Development
**Test-Driven Development** (or **TDD** for short) is a method of programming that uses tests to guide implementation. The goal of TDD is to make it easier to create clean, correct code on the first try and reduce debugging cycles. The key innovation of TDD is that it puts tests *before* code in the development cycle. A TDD development cycle looks something like this:

1. Write tests that cover all behavior of the interface you’re implementing
2. Write skeleton functions (i.e. functions that have the correct type signature but return dummy values, and don’t contain any logic) so that your program compiles
3. All of your tests fail because nothing is implemented yet
4. Inspect the first failing test. Implement the things it tests for.
5. Does the test pass? Great! Go back to step 4 for the next failing test. If the test doesn’t pass, debug what you implemented.

In this task, you will implement a new `circle_t` data structure for representing circles in `libgeometry`. For the purposes of this lab, circles will be represented by a center and radius. The center will be represented by a `point_t`, and the radius by a `double`.

You should create three new files: `include/circle.h`, `include/circle.c`, and `tests/test_circle.c`. You will need to update both the root-level `Makefile` and the `Makefile` in the `tests` directory to ensure the new files are compiled. Make a commit with the new files as well as the changes to the `Makefile`s, with the message “Starting lab 5 task 2”.

Now, use TDD to develop `new`, `init`, and `free` functions for circles.

{{% warning %}}
**Note:** To ensure that you are following TDD, we will be inspecting your commit history to check that you actually wrote your tests first. At minimum, we require the following workflow:

1. Write your tests in `tests/test_circle.c`
2. Write a struct definition in `include/circle.h`
3. Write skeleton functions in `src/circle.c`, and put their headers in `include/circle.h`
4. **Make a commit** indicating that you’ve written tests, and are about to start implementation
5. Write your implementations
6. **Make a commit** indicating that you’ve finished implementation and that your tests pass.

By all means, please make more commits as you write individual tests and implement individual functions. This is just the *minimum* we require to tell whether or not you implemented tests first.

{{% /warning %}}

Next, let’s implement a few slightly more complex functions that compute things about circles: `circle_diameter`, `circle_circumference`, and `circle_area`. Each of these functions should take a pointer to a `circle_t` struct as input, and return a `double`. The logic should be self-explanatory. When writing tests, you may find the function `cr_assert_float_eq` helpful. As you know, floating-point arithmetic on computers is not 100% accurate; `cr_assert_float_eq` allows you to check that the first value you supply to it is within some range of the second value. For example:

```c
circle_t *c = circle_new(point_new(0, 0), 5)
cr_assert_float_eq(circle_area(c), 3.14159*5*5, 10E-4, “Circle area wasn’t correct!”);
```

This checks whether or not our `circle_area` function is within 10^-4 (0.0001) of the expected value.

As above, you should use the TDD workflow when implementing these new functions.

Finally, you should add a `task2.txt` file that explains each test in the same manner as task 1.

Congratulations, you are now done with lab 5!
