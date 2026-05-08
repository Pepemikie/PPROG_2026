═══════════════════════════════════════════════════════════════
        MUSEUM ROBBERY - User Documentation & Guide
═══════════════════════════════════════════════════════════════

1. STORY & OBJECTIVE
2. HOW TO PLAY
3. COMMANDS REFERENCE
4. CHARACTERS GUIDE
5. OBJECTS & LOCATIONS
6. THE MAP
7. COMPLETE WALKTHROUGH
8. SOLUTION (Step-by-step commands)

══════════════════
STORY & OBJECTIVE
══════════════════
- You are two master thieves who have infiltrated one of the most famous museums in the world. Your mission: steal the priceless Crown located deep within the Mesopotamian Room. But you're not alone—the museum is guarded by dangerous enemies like the Police and Batman, while mysterious allies roam the halls (Guide, Josemi, Inaki, and Rodri) who may help you if you convince them.

-To reach your objective, you'll need to navigate through 13 different rooms, collect weapons and protective gear, recruit allies, and solve the museum's puzzles. Many doors are locked—but you'll find a KEY in the Prehistory Room that can unlock the passage to the Greek Room, opening up new paths to the Crown. Along the way, you'll discover mysterious objects with special properties: some heal you, others harm enemies, and some reveal secret passages.

-Your Goal: Reach the Crown Room, grab the Crown, and survive long enough to escape with your treasure. Work together with your partner, recruit allies for combat advantage, and use every object wisely. The museum is full of dangers and surprises—use strategy to outsmart the guards and claim your prize!

══════════════════
HOW TO PLAY
══════════════════
## 🎮 HOW TO PLAY

**Compilation:**
  make 

**Execution:**
./rob_the_museum                  # Normal mode
./rob_the_museum -d               # Deterministic mode (for testing)
./rob_the_museum -l log.txt       # With log file


**Gameplay:**
- Two players take turns controlling a robber each
- Each player starts in the Entry room with 5 health points and a backpack of 3 slots
- Type commands to move, collect objects, recruit characters, and interact with the world
- **Objective:** Reach the Crown Room and grab the Crown
- The game ends when you successfully escape with the Crown or when your health reaches 0

**Controls:**
- Type commands followed by Enter
- Example: `move north` → Move to the North
- Type `help` to see all available commands
- Type `exit` or `quit` to leave the game

══════════════════
COMMANDS REFERENCE
══════════════════

**Movement:**
- `move <direction> (m)`           - Move through rooms. Directions: north, south, east, west, up,    down

**Inventory Management:**
- `take <object> (t)`              - Pick up an object and add it to your backpack
- `drop <object> (d)`              - Leave an object in the current room
- `inspect <object> (i)`           - Examine an object to learn its properties

**Object Usage:**
- `use <object> (u)`               - Use an object (e.g., potion to heal)
- `use <object> over <character>`  - Use an object on an ally (e.g., heal a recruited character)
- `open <link> with <object>`      - Use an object to open a locked door

**Character Interaction:**
- `recruit <character> (r)`      - Recruit a friendly character to follow you and help in combat
- `abandon <character> (b)`        - Tell a character to stop following you
- `chat <character> (c)`           - Talk to a character
- `attack <character> (a)`        - Attack an enemy (allies do more damage if they're following you)

**Game Control:**
- exit (q)                       - Exit the game

**Tips:**
- Use short forms (in parentheses) for faster typing
- Type command names in lowercase or uppercase
- Most commands are case-insensitive

══════════════════
CHARACTERS GUIDE
══════════════════
**ENEMIES - Avoid or Defeat:**

**Batman** (Health: 24)
- Location: Prehistory Room (Room 12)
- Danger Level: ⚠️⚠️⚠️ (Very Dangerous)
- Description: "I'm Batman" - A powerful vigilante who will attack you on sight
- Strategy: Attack with allies for advantage, or recruit friends to help in combat

**Police** (Health: 10)
- Location: Prehistory Room (Room 12)
- Danger Level: ⚠️⚠️ (Dangerous)
- Description: "HEY! YOU!" - A museum guard trying to stop your heist
- Strategy: Weaker than Batman but still a threat; recruit allies before engaging

---

**ALLIES - Recruit Them!**

**Guide** (Health: 3)
- Location: Mesopotamian Room (Room 13)
- Description: "Welcome to the 05 museum" - A friendly tour guide
- Ability: Can follow you and provide combat advantage
- Strategy: Easy to recruit and helpful in fights, but fragile (low health)

**Josemi** (Health: 8)
- Location: Mesopotamian Room (Room 13)
- Description: "Malloc" - A mysterious ally
- Ability: Can follow you and help in combat
- Strategy: Moderate health; good support character

**Inaki** (Health: 5)
- Location: Armor Room (Room 14)
- Description: "Calloc" - Another friend
- Ability: Can follow you and provide combat support
- Strategy: Lower health, but still useful for numbers advantage

**Rodri** (Health: 9)
- Location: Armor Room (Room 14)
- Description: "Realloc" - A capable ally
- Ability: Can follow you and help in combat
- Strategy: Good health balance; solid choice for recruitment

---

**Recruitment Tip:**
Use `recruit <character>` to make an ally follow you. The more allies you have, the more damage you deal in combat!

══════════════════
OBJECTS & LOCATIONS
══════════════════
The museum is filled with interactive items. Some heal you, some are needed to progress, and some are just heavy!

**Key Items:**
- **Key (id: 50):** Found in the Prehistoric Room. Essential for opening the locked door.
- **Crown (id: 29):** The ultimate prize! Located in the Mesopotamian Room.

**Consumables & Weapons:**
- **Apple (id: 34):** Found in the Art Room. Use it to restore health!
- **Rum / Martini:** Found in the Lunchroom/Art Room. Use them at your own risk.
- **Sword / Gun / Knife:** Weapons scattered across the Entry, Prehistoric, and Armor rooms.

**Notable Rooms:**
- **11 - Entry:** The starting point. Safe, but empty.
- **12 - Prehistoric Room:** The central hub, but highly dangerous. Batman and Police are here!
- **13 - Mesopotamian Room:** Where the Crown is initially kept, guarded by the Guide and Josemi.
- **131 - Greek Room:** Accessible from Room 12 or 14. Leads to the upper floors.
- **18 - Crown Room:** The highest point of the museum. A great place to escape from!

══════════════════
THE MAP
══════════════════
A visual representation of the museum's layout based on the security blueprints.

```text
                                [18 Crown Rm]
                                      ^ (Up)
                                      |
                                [17 Space Rm]
                                      ^ (South) 
                                      |
        [161 Talking] <--(East)-- [16 Lunchroom]
                                      ^ (South) 
                                      |
                                  [15 Art Rm]
                                      ^ (Up)
                                      |
        [14 Armor Rm] --(South)-->[131 Greek Rm] <--(West)-- [12 Prehistoric] (Batman, Police)
             ^                                                    ^      | 
             | (West)                                     (North) |      | (Down)
             |                                                    |      v
        [13 Mesopotamian] <---------------------------------------/  [11 Entry] (START)
        (Crown, Guide, Josemi)
```
*Note: The link West from 12 to 131 (link12-131) is LOCKED and requires the Key.*

══════════════════
COMPLETE WALKTHROUGH
══════════════════
To successfully demonstrate all the features of the game (taking objects, recruiting allies, opening locked doors, and using items), follow this narrative path:

1. **The Infiltration:** Both players start in the Entry. Player 1 moves Up to the Prehistoric Room and immediately grabs the **Key** lying around, ignoring Batman for now.
2. **Recruiting Backup:** Player 2 moves Up, then North into the Mesopotamian Room. Realizing the danger, Player 2 recruits **Josemi** to help with any potential fights, and then secures the **Crown**!
3. **Opening Paths:** It's Player 1's turn again. The path West is blocked, so Player 1 uses the Key to open the locked link (`link12-131`). With the path clear, Player 1 moves West into the Greek Room, and then Up into the Art Room.
4. **Survival & Healing:** In the Art Room, Player 1 finds an **Apple**. Taking damage from a fall, Player 1 takes the Apple and uses it to heal.
5. **Regroup & Escape:** Player 2 moves West into the Armor Room to meet up with more allies, talking to Inaki. The players have successfully secured the Crown, formed a team, unlocked the museum's secrets, and are ready to escape!

══════════════════
SOLUTION
══════════════════
Copy and paste these exact commands to execute the Walkthrough automatically and see all game functionalities in action:

```text
move u
take key
turn
move u
move n
recruit Josemi
take Crown
turn
open link12-131 with key
move w
move u
take Apple
use Apple
turn
move w
chat Inaki
turn
move s
look
exit
```