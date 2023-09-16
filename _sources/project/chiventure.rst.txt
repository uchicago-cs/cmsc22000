
.. warning::


    This website currently reflects the Spring 2022 offering of CMSC 22000. We are in
    the process of updating this page for the Autumn 2023 offering of CMSC 22000,
    which will include several major changes to the class. Most notably, the class
    will now be taught in Python (instead of C) and will revolve around the development
    of a Python-based web application.

.. code-block:: none

   You wake up to find yourself in a strange hall. You have no idea how you got
   here. The last thing you remember is a blinding flash of light. You look at the
   tapestries lining the walls for any clues on your whereabouts. The tapestries
   depict valiant knights, fire-breathing wyverns, armies of goblins, and fearsome
   rulers sitting in their gilded thrones. Wherever you are, it must be in a
   different world from your own.

   No, not just a different world, but a different time altogether. 

   A time of wizards and warlords and all manner of magical creatures, a time to
   fight back the forces of Throxar the Terrible and to heed the counsel of
   Wilfrax the Wise...

   It is a time of adventure. 

   It is the time of...

|chiventure|

The CMSC 22000 project revolves around implementing a *text adventure
game engine*. This means that you won’t be implementing an individual
game but, rather, a platform that allows game authors (with little or no
knowledge of computer programming) to develop text adventure games.

Not just that, you won’t be implementing it from scratch but, rather,
will work on existing code that was written in previous offerings of
CMSC 22000.

Text Adventure Games
====================

An `adventure game <https://en.wikipedia.org/wiki/Adventure_game>`__ is
a type of video game where the player is the protagonist of an
interactive story. Broadly speaking, the protagonist inhabits a world
that they can interact with: exploring their surroundings (e.g., reading
a sign on the wall), going from one part of the world to another (e.g.,
going from one room to an adjacent room), manipulating objects in the
world (e.g., using a crowbar to open a door), or conversing with
non-player characters to gain knowledge that may prove useful later on.
The game will have some sort of objective (like finding a treasure),
which will mark the conclusion of the game (and the story).

In the early days of video games, adventure games were *text-based*, and
players would specify actions using a command-line interface. For
example, here is a screenshot of the classic adventure game
`Zork <https://en.wikipedia.org/wiki/Zork>`__ (note how commands are
entered after the ``>`` prompt)

.. figure:: zork.png
   :alt: Zork

   Zork

Over time, adventure games became more sophisticated, featuring
graphical interfaces, like the one in `The Secret of Monkey
Island <https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island>`__
(1990):

.. figure:: monkey_island.png
   :alt: The Secret of Monkey Island

   The Secret of Monkey Island

   Source: https://advgamer.blogspot.com/2014/04/game-43-secret-of-monkey-island-herring.html

However, notice how this still retains the basic elements of an
adventure game. For example, the player still inhabits a world they can
interact with except, instead of typing actions, the player can select
actions (Open, Close, Push, etc.) with the mouse, and then point to the
recipient of that action (e.g, “Walk to pirate”)

Adventure games are rarely implemented entirely from scratch, though (in
fact, this is true of most modern games too). Most games are implemented
using a `game engine <https://en.wikipedia.org/wiki/Game_engine>`__, a
platform that provides game developers with high-level abstractions for
writing games, so they don’t have to worry about every single detail of
implementing the game.

For example, `LucasArts <https://en.wikipedia.org/wiki/LucasArts>`__ was
a prolific publisher of graphic adventure games (`The Secret of Monkey
Island <https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island>`__,
`Loom <https://en.wikipedia.org/wiki/Loom_(video_game)>`__, `Sam & Max
Hit the
Road <https://en.wikipedia.org/wiki/Sam_%26_Max_Hit_the_Road>`__,
`Indiana Jones and the Fate of
Atlantis <https://en.wikipedia.org/wiki/Indiana_Jones_and_the_Fate_of_Atlantis>`__,
…), and most of them were implemented using a game engine called
`SCUMM <https://en.wikipedia.org/wiki/SCUMM>`__, which provided a
high-level scripting language for specifying games, allowing game
authors to focus on the narrative elements of the game, while the SCUMM
developers focused on the low-level details (e.g., parsing the commands
from the user, playing sounds, etc.)

For example, here is a simple SCUMM script that describes a “room” in a
game (source: https://robertodip.com/blog/scumm-internals-syntax/; check
out that page to learn more about SCUMM)

::

       room "doorstep" doorstep {
         sounds {
           "SFX/doorclos" door-close
           "SFX/dooropen" door-open
         }

         costumes {
           "costumes\dave" dave-skin
         }

         enter {
           ; Code to set up the room lives here,
           ; you can trigger sounds, animations, etc.
         }

         exit {
           ; Things to do when exiting the room,
           ; cleaning states, stopping sounds, etc
         }

         object Key {
           name is "key"

           verb look-at {
             say-line "it is a key"
           }

           verb pick-up {
             pick-up-object key
           }
         }
       }

Similarly, Zork (and several other games from that era) ran on the
`Z-machine <https://en.wikipedia.org/wiki/Z-machine>`__ game engine,
with games written in a language called Z-code (the Z-machine is,
strictly speaking, a virtual machine, but we can think of it as a game
engine). While text adventure games are less common nowadays, the text
adventure format still thrives in the `interactive
fiction <https://en.wikipedia.org/wiki/Interactive_fiction>`__ genre,
which can be written in languages like
`Inform <https://en.wikipedia.org/wiki/Inform>`__ (which are relatively
easy to use by authors without a technical background).

If you’d like to learn more about text adventure games, specially as
they relate to interactive fiction, we recommend checking out the
`Interactive Fiction! <https://www.red-bean.com/sussman/if/>`__ page by
`Ben Collins-Sussman <https://www.red-bean.com/sussman/>`__ (SB’94).
This page also includes links to several games and interactive novels
that you can play for free. If you’d like to get a feel for what a text
adventure game feels like, we recommend checking out the interactive spy
novel, `Spider and
Web <https://en.wikipedia.org/wiki/Spider_and_Web>`__. You can play the
novel for free `here <https://eblong.com/zarf/zweb/tangle/>`__.

If you’d like to try out a graphic adventure game, many classic
adventure games are available on Steam, including `The Secret of Monkey
Island <https://store.steampowered.com/app/32360/The_Secret_of_Monkey_Island_Special_Edition/>`__,
`Indiana Jones and the Fate of
Atlantis <https://store.steampowered.com/app/6010/Indiana_Jones_and_the_Fate_of_Atlantis/>`__,
and many others.

chiventure code
===============

The chiventure code is available in the following repository: https://github.com/uchicago-cs/chiventure/

Additional documentation on the implementation of chiventure can be
found in the
`docs/ <https://github.com/uchicago-cs/chiventure/tree/master/docs>`__
directory of the chiventure repository.

.. |chiventure| image:: chiventure.jpg
   :target: https://www.youtube.com/watch?v=DGSXURPvRxY
