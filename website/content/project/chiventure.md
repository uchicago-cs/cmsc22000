---
title: "chiventure: a Text Adventure Game Engine"
type: page
---

```
You wake up to find yourself in a strange hall. You have no idea how you got here. The last thing you remember is a blinding flash of light. You look at the tapestries lining the walls for any clues on your whereabouts. The tapestries depict valiant knights, fire-breathing wyverns, armies of goblins, and fearsome rulers sitting in their gilded thrones. Wherever you are, it must be in a different world from your own. 

No, not just a different world, but a different time altogether. 

A time of wizards and warlords and all manner of magical creatures, a time to fight back the forces of Throxar the Terrible and to heed the counsel of Wilfrax the Wise... 

It is a time of adventure. 

It is the time of...
```


[![chiventure](/cmsc22000/img/chiventure.jpg "chiventure")](https://www.youtube.com/watch?v=DGSXURPvRxY)


The CMSC 22000 project revolves around implementing a _text adventure game engine_. This means that you won’t be implementing an individual game but, rather, a platform that allows game authors (with little or no knowledge of computer programming) to develop text adventure games.

Not just that, you won't be implementing it from scratch but, rather, will work on existing code that was written in previous editions of CMSC 22000.


# Text Adventure Games

An [adventure game](https://en.wikipedia.org/wiki/Adventure_game) is a type of video game where the player is the protagonist of an interactive story. Broadly speaking, the protagonist inhabits a world that they can interact with: exploring their surroundings (e.g., reading a sign on the wall), going from one part of the world to another (e.g., going from one room to an adjacent room), manipulating objects in the world (e.g., using a crowbar to open a door), or conversing with non-player characters to gain knowledge that may prove useful later on. The game will have some sort of objective (like finding a treasure), which will mark the conclusion of the game (and the story).

In the early days of video games, adventure games were _text-based_, and players would specify actions using a command-line interface. For example, here is a screenshot of the classic adventure game [Zork](https://en.wikipedia.org/wiki/Zork) (note how commands are entered after the `>` prompt)


![Zork](/cmsc22000/img/zork.png "Zork")


Over time, adventure games became more sophisticated, featuring graphical interfaces, like the one in [The Secret of Monkey Island](https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island) (1990):


![The Secret of Monkey Island](/cmsc22000/img/monkey_island.png "The Secret of Monkey Island")

Source: [https://advgamer.blogspot.com/2014/04/game-43-secret-of-monkey-island-herring.html](https://advgamer.blogspot.com/2014/04/game-43-secret-of-monkey-island-herring.html) 

However, notice how this still retains the basic elements of an adventure game. For example, the player still inhabits a world they can interact with except, instead of typing actions, the player can select actions (Open, Close, Push, etc.) with the mouse, and then point to the recipient of that action (e.g, “Walk to pirate”)

Adventure games are rarely implemented entirely from scratch, though (in fact, this is true of most modern games too). Most games are implemented using a [game engine](https://en.wikipedia.org/wiki/Game_engine), a platform that provides game developers with high-level abstractions for writing games, so they don’t have to worry about every single detail of implementing the game.

For example, [LucasArts](https://en.wikipedia.org/wiki/LucasArts) was a prolific publisher of graphic adventure games ([The Secret of Monkey Island](https://en.wikipedia.org/wiki/The_Secret_of_Monkey_Island), [Loom](https://en.wikipedia.org/wiki/Loom_(video_game)), [Sam & Max Hit the Road](https://en.wikipedia.org/wiki/Sam_%26_Max_Hit_the_Road), [Indiana Jones and the Fate of Atlantis](https://en.wikipedia.org/wiki/Indiana_Jones_and_the_Fate_of_Atlantis), ...), and most of them were implemented using a game engine called [SCUMM](https://en.wikipedia.org/wiki/SCUMM), which provided  a high-level scripting language for specifying games, allowing game authors to focus on the narrative elements of the game, while the SCUMM developers focused on the low-level details (e.g., parsing the commands from the user, playing sounds, etc.)

For example, here is a simple SCUMM script that describes a “room” in a game (source: [https://monades.roperzh.com/scumm-internals-syntax/](https://monades.roperzh.com/scumm-internals-syntax/); check out that page to learn more about SCUMM) 


```
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
```


Similarly, Zork (and several other games from that era) ran on the [Z-machine](https://en.wikipedia.org/wiki/Z-machine) game engine, with games written in a language called Z-code (the Z-machine is, strictly speaking, a virtual machine, but we can think of it as a game engine). While text adventure games are less common nowadays, the text adventure format still thrives in the [interactive fiction](https://en.wikipedia.org/wiki/Interactive_fiction) genre, which can be written in languages like [Inform](https://en.wikipedia.org/wiki/Inform) (which are relatively easy to use by authors without a technical background).

# chiventure

![Projects Components](/cmsc22000/img/components.png "Project Components")

The components are the following:

*   **WDL**: Our game engine will have a “World Description Language” that provides the specification of a single game. This component is responsible for defining this language, and for parsing it.
*   **Game State**: A game will have some state we need to keep track of: rooms, objects in rooms, players, non-player characters, etc. This component models this state, and provides interfaces for simple manipulations of the state of the game (e.g., placing an object in the player’s inventory)
*   **Action Management**: During the game, a player will be able to perform actions (pushing, pulling, opening, closing, etc.) that will usually affect the state of the game in some way. The processing of these actions can be non-trivial; for example, picking up an object may only be possible if a certain condition is met (e.g., a magical orb can only be taken if you are in possession of a talisman) and may have additional effects (e.g., pushing a brick in a wall may unlock a door in a different room). This component is responsible for processing actions like “take the orb” (and checking whether it is possible to perform that action), and would use the Game State’s interface to actually change the state of the game.
*   **Checkpointing**: As the state of the game changes, we will want to checkpoint the game so we can resume it at a later time (or, more informally, we need the ability to save games and load games). This component is responsible for defining a file format for saving the state of the game, and providing interfaces for saving/loading this state. 
*   **CLI**: This component will be responsible for providing a command prompt, and parsing the commands entered by the user, and using the game state to validate some commands. For example, if a user types “push button”, the CLI would not call Action Management right away. Instead, it would need to check whether there is anything in the room that can be identified by “button”, whether it can be pushed, and may even have to ask the user to clarify what button (if there are multiple buttons in the room).
*   **UI**: Besides the command-line interface, games may have additional UI elements, like visualizing a map of the game or displaying graphics associated with individual rooms. This component would be responsible for any non-CLI elements of the user interface.




