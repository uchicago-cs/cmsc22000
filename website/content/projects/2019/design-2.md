---
title: "Design Exercise: Boardmaster 3000 (Part II)"
---

Good news, everyone! The first version of the Boardmaster 3000 has been a resounding success! We got a lot of quality feedback from users, which included comments like “the VR interface is like nothing I’ve seen before”, “finally, a chess game that challenges both my intellect _and_ my senses”, and “the AI is creepily lifelike, in a good way, I guess”. We know you were not involved in any of those aspects of the game, but your modules for loading, manipulating, and saving the state of a game were an indispensable building block that made the rest of the game possible.

Encouraged by this early feedback on the first version of the game, we are going to add more features to the Boardmaster 3000:



*   Support for two more games: checkers and Almost Chess
*   Support for square chessboards larger than 8x8
*   Support for pawn promotion in chess
*   Support for CBFv2, a new and improved file format for specifying chessboard-based games

In this design exercise, you will revise your previous design to accommodate these additional features.


## Additional games

The Boardmaster 3000 must now support [checkers](https://en.wikipedia.org/wiki/Draughts) (and, specifically, [International Checkers](https://en.wikipedia.org/wiki/International_draughts)) and [Almost Chess](https://en.wikipedia.org/wiki/Almost_Chess). Take into account that, while we are only adding these two games right now, we anticipate we will likely want to support more games in the future, so our design should not be specific to just chess, checkers, and Almost Chess, and should be easily extensible to support other games played on a square chessboard. For example, it’s likely we will want to support [Capablanca Chess](https://en.wikipedia.org/wiki/Capablanca_Chess) in the near future.


### International Checkers

We will follow the rules described in the [International draughts](https://en.wikipedia.org/wiki/International_draughts) Wikipedia article. However, it is not our goal to support every possible rule perfectly in our first implementation of checkers. You may make any simplifying assumptions you want, as long as you support, at least, moves by regular and crowned pieces, and single-piece captures. Take into account this means you don’t have to support capturing multiple pieces in successive jumps.

Take into account that checkers is played on a 10x10 board, an additional requirement that is described further below.


### Almost Chess

In [Almost Chess](https://en.wikipedia.org/wiki/Almost_Chess), the queen piece is replaced with a [chancellor](https://en.wikipedia.org/wiki/Empress_(chess)) piece, which can move like a rook or a knight. Other than that, there are no other changes to the rules.


## Larger Chessboards

In part due to supporting checkers, we now have to be able to support chessboards larger than 8x8. Besides the 10x10 chessboard, we may want to also allow for chess to be played in chessboards larger than 8x8. You may assume that, when using a larger chessboard, the game still starts with 32 pieces, and that the exact initial arrangement will be an implementation detail.


## Pawn Promotion

We will now support pawn promotion in chess: when a pawn reaches the other end of the board, it can be promoted to a queen, rook, bishop, or knight. We will continue to _not_ support castling or _en passant_.


## Support for CBFv2

The CBF format we used in the first design is insufficient to support the new features being introduced in this new version of the Boardmaster 3000. Fortunately, there is a more advanced format, CBFv2, we can use. Here is an example for a chess game:


```
game: chess
board-size: 8
p1-captured: PPNN
P2-captured: q
R_BQKB_R
P____PP_
__PPP__b
__p_____
________
n_______
ppp_pppp
r___kbnr
```


Here is an example for a checkers game:


```
game: checkers
board-size: 10
p1-captured: CCC
p2-captured: c
_C_C_C_C_C
C_C_C_C_C_
___C_C_C_C
C_____C___
_______C__
__c_______
_c_____c_c
c_c_c_c_c_
_c_c_c_c_c
c_c_c_c_c_
```


A few notes:



*   For Almost Chess, the game type is `almost-chess`
*   The `captured` fields refer to the pieces capture _by_ that player (not _from_ that player). Player 1 (`p1`) is whatever player makes the first move in the game.
*   In almost chess, a chancellor is represented with `c`/`C`
*   In checkers, a crowned piece is represented with `k`/`K`


## Your task

You must modify the design you produced in the first design exercise to support these additional requirements, possibly adding additional modules. The number of changes required will depend on how general-purpose you made your first design (so, having to make only a few small changes is not necessarily a bad thing).

Take into account that the functionality provided by your modules is still, essentially, the same as before:



*   Loading a game from disk
*   Saving a game to disk
*   Determining the following about the state of the game:
    *   What piece (if any) is in position _x, y_?
    *   What are the possible moves for the piece in position _x, y_?
    *   Can piece in position (x<sub>0</sub>, y<sub>0</sub>) move to position (x<sub>1</sub>, y<sub>1</sub>)?
    *   What piece (if any) will the piece in position (x<sub>0</sub>, y<sub>0</sub>) take if it moves to position (x<sub>1</sub>, y<sub>1</sub>)
    *   Can the piece in position _x, y_ be taken by some other piece in one move?
    *   What pieces have been taken by a given player?
*   Changing the state of the game:
    *   Move piece in position (x<sub>0</sub>, y<sub>0</sub>) to position (x<sub>1</sub>, y<sub>1</sub>), unless it is an illegal move.

However, you must take into account the following:



*   Moving a piece could result in the piece changing to a different type (e.g., pawn promotion in chess and crowning in checkers). While this could be treated as an implementation detail (if you make a move, this is just a different way in which the internal state of the game changes), your “move” function should supply this information in some way (otherwise, the user of your module will have to check the state of the piece after every move, to see whether it has changed)
*   Since we expect to support more games in the future, you should avoid having a function for moving a chess piece and a function for moving a checkers piece. Otherwise, if we end up supporting 50 games, we’ll end up with 50 “move” functions! (and similarly with other functions in your interface)

Like the previous exercise, remember that you should focus only on specifying the _interface_ of your modules, and not their implementation. Make sure to review the _Deliverables_ section of the [first design exercise]({{< relref "design-1.md" >}}), as your updated design should follow the same guidelines described there.

Besides the C code that specifies your design, you should also answer the following questions in your README file:

*   In general, what major changes (if any) did you have to make to your design to accommodate the additional requirements?
*   In hindsight, what (if anything) would you have done differently in your original design that would’ve made it easier to add support for these additional requirements?



## Submission Instructions

Like the first part of the exercise, you should make sure you do all your work in your team repository (not in your individual repository). Once you are ready to submit, run `chisubmit init` in the root of your team repository (note: if you already did this in the first exercise, you don't need to do it again) Once you have done so, you just need to run this:

```
chisubmit student assignment submit design2
```

(you do not need to run the `assignment register` command, like the labs, because we will be registering the teams ourselves on chisubmit)



