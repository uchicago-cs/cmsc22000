---
title: "Design Exercise: Boardmaster 3000"
---

You have recently joined a software company that is developing an exciting new game: The Boardmaster 3000! This game will allow users to play a variety of two-player board games, all of which can be played on a square [chessboard](https://en.wikipedia.org/wiki/Chessboard) (like [chess](https://en.wikipedia.org/wiki/Chess), [checkers](https://en.wikipedia.org/wiki/Draughts), and some [variants of chess](https://en.wikipedia.org/wiki/List_of_chess_variants)) However, we are following an incremental software development model, so we are going to start by supporting only chess. This will give us a chance to get some initial feedback on the Boardmaster 3000 before we move on to supporting other games.

What’s that you say? There’s a lot of chess games out there already? Ah, but the Boardmaster 3000 will feature a state-of-the-art multiplatform VR interface with AI adversaries powered by sophisticated Deep Learning algorithms! Also, you can bet on games using our own cryptocurrency, Boardcoin!

Very exciting stuff… which is in the hands of other teams in the company. Your team will be focusing on a different task: loading/saving games from/to disk, and providing an API for manipulating the state of the game.


## The CBF Format

The Boardmaster 3000 will need to be able to save games to disk (e.g., if we want to stop playing, and then resume the game at a later time), and then load those saved games from disk (additionally, a user may want to load a famous chess match). We will be using a simple file format called CBF (ChessBoard File), where the chessboard is represented with text characters. For example, this chessboard:

![Chess game](/cmsc22000/img/chess.png "Chess game. Source: https://en.wikipedia.org/wiki/Deep_Blue_versus_Kasparov,_1997,_Game_6")

Would be represented like this:

```
R_BK_B_R
PP_NQ_P_
__P_PNbP
________
___p_b__
_____n__
ppp__ppp
r__q_rk_
```


Each line represents a row of the chessboard. Empty spots are represented by an underscore character, black pieces are represented with uppercase letters, and white pieces are represented with lowercase letters:

*   `p`/`P`: Pawn
*   `r`/`R`: Rook
*   `b`/`B`: Bishop
*   `n`/`N`: Knight
*   `q`/`Q`: Queen
*   `k`/`K`: King 


## Chess rules

Our first version of the Boardmaster 3000 will only have to support a subset of the rules of chess. In particular, we will only support the moves specified in the “Basic moves” section of the [Rules of chess](https://en.wikipedia.org/wiki/Rules_of_chess) Wikipedia article. This means we do not yet support castling, _en passant_, or pawn promotion.


## Your task

Broadly speaking, you will be responsible for designing modules for loading, manipulating, and saving the state of a single game. While this may not seem terribly exciting in isolation, your modules will be used by a lot of other teams in the Boardmaster 3000 project. For example, when our advanced Chess AI, fondly nicknamed “The Chessinator 3000”, needs to know whether a piece in position (x<sub>0</sub>, y<sub>0</sub>) can move to position (x<sub>1</sub>, y<sub>1</sub>), it will be calling your code.

Take into account that you are only going to be _designing_ these modules. So, you will be focusing only on specifying the _interface_ of those modules, and not their implementation (with one exception: you will have to provide a specification of any internal data structures you expect to use)

Your modules must provide at least the following functionality:



*   Loading a game from disk
*   Saving a game to disk
*   Determining the following about the state of the game:
    *   What piece (if any) is in position _x, y_?
    *   What are the possible moves for the piece in position _x, y_?
    *   Can piece in position (x<sub>0</sub>, y<sub>0</sub>) move to position (x<sub>1</sub>, y<sub>1</sub>)?
    *   What piece (if any) will the piece in position (x<sub>0</sub>, y<sub>0</sub>) take if it moves to position (x<sub>1</sub>, y<sub>1</sub>)
    *   Can the piece in position _x, y _be taken by some other piece in one move?
    *   What pieces have been taken by a given player?
*   Changing the state of the game:
    *   Move piece in position (x<sub>0</sub>, y<sub>0</sub>) to position (x<sub>1</sub>, y<sub>1</sub>), unless it is an illegal move.

Hint: A big part of this design will be to figure out how to represent the state of the game using C structs.


## Deliverables

Instead of preparing a formal document, you will be specifying your design in C code. For each module you design, you must provide a header file and a C file. The header file should contain all the functions that are provided by that module, and the C file should contain empty implementations of those functions. Each function in the header file must include code comments explaining the purpose of the function.

For example:


```
math.h:

    /* This function adds two numbers */
    int add(int x, int y);

math.c:

    /* See math.h*/
    int add(int x, int y)
    {
		/* TODO */
		Return 0;
    }

```


You must also provide struct definitions for any data structures you expect to use in your modules. You must use code comments to provide a description of the struct, as well as any non-obvious fields.

You may assume that you have the ability to use standard data structures like linked lists, hash tables, etc. If you need to use such a type, you can include a forward declaration in lieu of an actual data structure (i.e., you do not need to design a linked list module or find an existing one). 

For example:


```
printer.h:

    /* Forward declaration */
    typedef struct list list_t;

    /* This struct represent a single print job. A print
       job includes some text that needs to be printed out */
    typedef struct printjob
    {
        int identifier;
        char *text;
    } printjob_t;

    /* 
    typedef struct printer
    {
        char *name;

        /* Duplex printing: true if printer can do two-sided printing */
        bool duplex; 

        /* Print job that is currently being printed (NULL if none) */
        printjob_t *current_job;

        /* List of printjob_t structs. Represents the jobs that
           are waiting to be printed */
        list_t *jobs;
    } printer_t;
```


We encourage you to follow this [style guide](https://uchicago-cs.github.io/cmsc23300/style_guide.html) when writing your code, but will not be grading you based on style at this point. However, we will expect you to follow a style guide in the project (similar to the one we link to), so familiarizing yourself with a style guide will be good practice.

Please note that your code _must_ compile correctly. This will ensure that you are properly specifying your structs and functions. We will be talking about building projects with multiple modules during third week but, in the interim, you can compile your code like this:

```
gcc file1.c file2.c file3.c main.c -o bm300
```

Do not name your modules `file1.c`, `file2.c`, etc. Instead replace those filenames with those of your C modules. Please note that, for your code to compile correctly, you must include a `main.c` file with an empty `main()` function (your `main()` function does not need to call any of your functions, etc.). You are welcome to provide a `Makefile`, but are not required to do so.

Finally, you must include a `README` file with a summary of each module, and any other general notes on your design.

Note: Once the design exercise is done, all the teams will be able to see each other’s designs (along with the comments we will provide, except for their exact score). This will allow you to see how other teams approached the same design problem, which can be very useful in honing your own design skills. However, this also means you have to make sure your code and documentation will be easy to read and understand by others.


## Submission Instructions

We will be creating team repositories on our GitLab server (the name of the repository will be the CNetIDs of everyone on the team, separated by hyphens). One of you should initialize the repository,  in the same way you did in Lab #1, and the rest of you should clone the repository once it has been initialized.

You must upload all your work for this exercise to your team repository. *Do not use your individual repository!* Since we have not yet seen certain advanced Git features, including how to deal with "merge conflicts", we suggest that, for the time being, you only have one person pulling/pushing from/to the repository at any given time.

Once you are ready to submit, run `chisubmit init` in the root of your team repository. You will be prompted to choose between your individual registration or your team registration; make sure you choose the latter. Once you have done so, you just need to run this:

```
chisubmit student assignment submit design1
```
(you do not need to run the `assignment register` command, like the labs, because we will be registering the teams ourselves on chisubmit)




