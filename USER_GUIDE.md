
#     **MUSEUM ROBBERY - User Documentation & Guide**
---------------------------------------------------------
# INDEX

1.  PLOT
2.  HOW TO PLAY
3.  COMMAND REFERENCE
4.  PLAYERS
5.  CHARACTERS
6.  SPACES
7.  GAME RULES
8.  THE MAP
9.  COMPLETE WALKTHROUGH
10. SOLUTION
-----------------------
## **PLOT**

### _PLOT_
- You are a master thief who has infiltrated one of the world’s most famous museums. Your mission: to steal the museum’s most prized possession, the priceless crown.

- To achieve your goal, you’ll need to navigate 13 different rooms, collect armour and healing items, recruit allies, battle enemies to earn rewards, and solve the museum’s puzzles. During the heist, you’ll discover locked doors that can be opened with various items.


### _GOAL_
- Your goal: to get hold of the precious crown, reach the Crown Room, and survive long enough to escape with your treasure. Work with your partner, recruit allies to gain an advantage in combat, and use each item wisely. The museum is full of dangers and surprises: use strategy to outwit the guards and claim your prize!

-----------------------
## **HOW TO PLAY**


### _EXECUTION_
- `./rob_the_museum museum.dat` -> Normal mode  
- `./rob_the_museum museum.dat -d` -> Deterministic mode (for testing)  
- `./rob_the_museum museum.dat -l output.log` -> With log file

-----------------------
## **COMMAND REFERENCE**


### _PLAYER COMMANDS_
- `move <dir> or m <n|s|e|w|u|d>`  
      - Move trough rooms.     
      - `<dir>` refers to north, south, east, west, up and down.
- `colab <player> or k <player> `  
      - `<player>` refers to the team mate's name.

### _OBJECT COMMANDS_
- `take <obj> or t <obj>`  
      - Pick up an object and add it to your backpack  
      - `<obj>` refers to the object's name
- `drop <obj> or d <obj>`  
      -  Leave an object in the current room  
      - `<obj>` refers to the object's name
- `inspect <obj> or i <obj>`  
      -  Examine an object to learn its properties  
      - `<obj>` refers to the object's name
- `open <link> with <obj>`  
      -  Open the link between 2 rooms  
      - `<link>` refers to the link's name  
      - `<obj>` refers to the object's name
- `use <obj> over <char>`  
      -  Uses an object to gain or loose health points, over character is optional,   
      if you don't specify, you will use it for yourself  
      - `<obj>` refers to the object's name  
      - `<char>` refers to the ally's name

### _CHARACTER COMMANDS_
- `attack <char> or a <char>`  
      -  Attacks the enemy with the sum of all your allies  
      - `<char>` refers to the enemy's name 
- `char <char> or c <char>`  
      -  Chats with the ally to receive some information  
      - `<char>` refers to the ally's name  
- `recruit <char> or r <char>`  
      -  Recruits the ally so you can have more opportunities   
      - `<char>` refers to the ally's name 
- `abandon <char> or b <char>`  
      -  Abandons the ally that you have previously recruited  
      - `<char>` refers to the ally's name 

### _OTHER COMMANDS_
- `save <file> or s <file>`  
      -  Saves your game, so you can load it later  
      - `<file>` refers to the slot's name where the game is saved
- `load <file> or l <file>`  
      -  Load the game that you saved before  
      - `<file>` refers to the slot's name where the game is saved
- `exit or e`  
      -  Exits the game  

### _TIPS_
- Use short forms (in parentheses) for faster typing
- Type command names in lowercase or uppercase
- Most commands are case-insensitive
- Save the game with the name of "slot1"

-----------------------
## **PLAYERS**
### _PLAYER 1_
- Name: Robber_1
- Graphic Description: $P1
- Init position: Entry
- Init health points: 10
- Max backpack: 5
### _PLAYER 2_
- Name: Robber_2
- Graphic Description: $P2
- Init position: Bathroom
- Init health points: 14
- Max backpack: 7

-----------------------
## **CHARACTERS**
### _BATMAN_
- Name: Batman
- Graphic Description: /(B)\
- Health points: 25
- Enemy
- Location: Greek Room
- Message: I'm Batman

### _POLICE_
- Name: Police
- Graphic Description: (P)/=*
- Health points: 12
- Enemy
- Location: Prehistoric Room
- Message: HEY! YOU!

### _GUIDE_
- Name: Guide
- Graphic Description: (G)!>
- Health points: 3
- Enemy
- Location: Entry Room
- Message: Welcome to the Museum

### _JOSEMI_
- Name: Josemi
- Graphic Description: >(:{)
- Health points: 8
- Ally
- Location: Mesopotamic Room
- Message: Malloc

### _INAKI_
- Name: Inaki
- Graphic Description: /(:D)
- Health points: 5
- Ally
- Location: Armor Room
- Message: Calloc

### _RODRI_
- Name: Rodri
- Graphic Description: \\(Bo)
- Health points: 9
- Ally
- Location: Lunchroom
- Message: Realloc

### _BABY_
- Name: Baby
- Graphic Description: :?!}
- Health points: 1
- Ally
- Location: Crown Room
- Message: Can't escape, you needed crown

-----------------------
## **SPACES**

### _BASEMENT_
- Name: Basement
- ID: 10

### _ENTRY_
- Name: Entry
- ID: 11

### _BATHROOM_
- Name: Bathroom
- ID: 111

### _GARDEN_
- Name: Garden
- ID: 112

### _PREHISTORIC ROOM_
- Name: Prehistoric Room
- ID: 12

### _MESOPOTAMIAN ROOM_
- Name: Mesopotamian Room
- ID: 13

### _GREEK ROOM_
- Name: Greek Room
- ID: 131

### _ARMOR ROOM_
- Name: Armor Room
- ID: 14

### _ART ROOM_
- Name: Art Room
- ID: 15

### _LUNCHROOM_
- Name: Lunchroom
- ID: 16

### _TALKING ROOM_
- Name: Talking Room
- ID: 161

### _SPACE ROOM_
- Name: Space Room
- ID: 17

### _CROWN ROOM_
- Name: Crown Room
- ID: 18

-----------------------
## **GAME RULES**
### _RULE 1_
- The crown appears when Batman dies

### _RULE 2_
- If you are in room the Greek Room, you have a 20% chance of receiving a Batman attack
- This only affects the player who entered the room

### _RULE 3_
- The door opened with the key has a 10% chance of closing automatically

### _RULE 4_
- While in the Lunchroom, you have a 30% chance of gaining 1 health point

### _RULE 5_
- In the Art Room, there is a 10% chance of slipping and losing 1 health point

### _RULE 6_
- If you kill the Police in Prehisotric room, you obtain a gun
- The gun grants additional health when used

### _RULE 7_
- If you kill the Guide, you obtain a key
- This key allows you to open a door and makes Batman easier to find

### _RULE 8_
- You only win if you enter the Crown Room while carrying the Crown in your inventory

-----------------------
## **THE MAP**

A visual representation of the museum's layout based on the security blueprints.
```text
Piso 3
[Crown Room 18]
 (Diamond / Baby)
           ^17
```
```text
Piso 2
[Art Room 15] (Banana)
      ^ ^131
      |
      v
[Lunchroom 16] <---> [Talking Room 161]
(Rum/Martini/Rodri)   (Necklace/Phone/Wallet)
                              X
                              |
                              v   X18
                        [Space Room 17]
                        (Engine/Moonrock)
```
```text
Piso 1
(Inaki/Shield/Sword)
[Armor Room 14]  <---> [Mesopothamic Room 13](Josemi/Vessel)
      X                       ^
      |                       |
      v     v15               X
[Greek Room 131] X---> [Prehistoric Room 12](Police/Skull/Hieroglyphs)
(Batman/Bone)                          ^11
```
```text
Piso 0
                         v12
(P2/Paperroll) (P1/Guide/Knife/Map/Pickaxe)            
[Bathroom 111] <---> [Entry 11] <---> [Garden 112](Snail)
                           ^10
```
```text
Piso -1
        v11
[Basement 10](Bomb)         
```
**Note_1: The link West from 12 to 131 (Door) is LOCKED and requires the Key.**  
**Note_2: The link North from 171 to 161 (Security_lock) is LOCKED and requires the Bomb.**

-----------------------
## **COMPLETE WALKTHROUGH**
To ensure all the game’s features work correctly (picking up items, recruiting allies, opening locked doors and using items), follow this sequence:

1. Robber_1 attacks the Guide while Robber_2 takes some Paperroll from the Bathroom so they can pick up the knife without leaving fingerprints.
2. Once the Guide has been defeated, both players work together to move forward more quickly and simultaneously use the key dropped by the Guide to open the Door.
3. Passing the Police in the Prehistoric Room, we go through the Mesopotamian Room and the Armor Room to recruit Josemi and Inaki.
4. We head down to the Greek Room, where Batman will be waiting for us to enter. After defeating Batman as a team, we take the Crown he was guarding and head up to the Art Room.
5. We proceed to the Talking Room, where we’ll speak to Josemi for some words of encouragement and examine the Crown to see just how interesting it is.
6. We proceed to the Crown Room, where we’ll find our secret passage so we can escape the museum without being defeated.
-----------------------
## **SOLUTION**
**List of all commands that you will need to use to do de "COMPLETE WALKTHROUGH"**

```text

attack guide
attack guide
attack guide
attack guide
attack guide
attack guide
take key
move up
move north
recruit josemi
move west
recruit inaki
take sword
take shield
use shield
use sword
move south
take bone
move east
take skull
use skull
open door with key
move west
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
attack batman
take crown
move up
move south
move east
move south
move up
```