/**
 * @brief It implements the game rules module
 *
 * @file game_rules.c
 * @author Rodrigo Cruz Asensio
 * @version 1
 * @date 08-05-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include "game.h"
#include "player.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief It executes the non-deterministic game rules and random events
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 *
 * This function evaluates six automatic rules each turn:
 * win condition, surprise attack, security door, magic wallet,
 * rest area, and museum trap.
 */
void game_rules_update(Game *game) {
    Player *current_player = NULL;
    int random_chance = 0;
    Id player_loc = NO_ID;
    Link *door = NULL;

    if (!game) return;

    /* Generate a random number between 0 and 99 */
    random_chance = rand() % 100;       
    
    /* Get the current player */
    current_player = game_get_player(game); 
    if (!current_player) return;

    player_loc = player_get_location(current_player); /* Get the player's current location */

    /* RULE 1: WIN CONDITION (If the crown [29] is taken, it disappears from the map) */
    /* If its location is NO_ID, it means it's in an inventory */
    if (game_get_object_location(game, 29) == NO_ID) {
        /* We finish the game if it's stolen (Adjust the function to your game_set_finished if needed) */
        game_set_finished(game, TRUE);
    }

    /* RULE 2: SURPRISE ATTACK OF BATMAN. 10% chance if you are in room 12 */
    if (random_chance < 10 && player_loc == 12) {
        /* Batman takes away 1 health point */
        player_modify_health(current_player, -1);
    }

    /* RULE 3: SECURITY SYSTEM. The door (ID 14) closes automatically (5% chance) */
    if (random_chance >= 10 && random_chance < 15) {
        door = game_get_link(game, 14);
        if (door) {
             link_set_open(door, FALSE); /* Closes the door automatically */
        }
    }

    /* RULE 4: THE MAGIC WALLET. It teleports you to a different room (5% chance) */
    if (random_chance >= 15 && random_chance < 20) {
        /* Changes from the current room to room 111 (Bathroom) */
        game_set_object_location(game, 44, 111);
    }

    /* RULE 5: REST AREA. You recover health in the Lunchroom (ID 16) (10% chance) */
    if (random_chance >= 20 && random_chance < 30 && player_loc == 16) {
        /* Evitamos que la salud suba infinitamente, por si acaso */
        if (player_get_health(current_player) < 5) {
            player_modify_health(current_player, 1);
        }
    }

    /* RULE 6: TRAP OF THE MUSEUM. You slip in the Art Room (ID 15) (5% chance) */
    if (random_chance >= 30 && random_chance < 35 && player_loc == 15) {
        player_modify_health(current_player, -1);
    }
}