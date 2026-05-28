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

/*
Tengo pensado que para hacer el juego tengas que conseguir la corona,
que solo se puede robar de BATMAN si ha muerto.
Si matas al policia de la sala 12, consigues una pistola.
Si matas a la guia te dará la llave para poder pasar de la 12 a la 131 e ir a por BATMAN mas facil
AL conseguir la corona, tendrás que avanzar hasta la sala de la corona. SI no tienes la corona, te quedas encerrado
en la 18 porq no se podrá salir y todo dependera del otro player.
*/

/*
***FALTA***
Regla 1. La corona aparece cuando Batman muere


Regla 2. Si estás en la sala 12, tienes un 10% más de probabilidad de ganar en un ataque a Batman
Regla 3. La puerta que se abre con la llave se cierra automáticamente con un 5% de probabilidad
Regla 4. Recuperas, con una probabilidad del 30%, 1 de vida si estás en el Lunchroom (ID 16)
Regla 5. Hay un 5% de probabilidad de que cuando se entre en el Art Room (ID 15), se caiga y pierda 1 de vida

***FALTA***
Regla 6. Si matas al policia de la sala 12, consigues una pistola que te da más vida al usarla
Regla 7. Si matas a la guia te dará la llave para poder pasar de la 12 a la 131 e ir a por BATMAN mas facil
Regla 8. Solo ganas el juego si entras a la sala de la corona con la corona

*/

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
    if (player_has_object(current_player, 29) == TRUE){
        game_set_finished(game, TRUE);
    }

    /* RULE 2: SURPRISE ATTACK OF BATMAN. 10% chance if you are in room 12 */
    if (random_chance < 10 && player_loc == 12) {
        /* Batman takes away 3 health points */
        player_modify_health(current_player, -3);
    }

    /* RULE 3: SECURITY SYSTEM. The door (ID 14) closes automatically (5% chance) */
    if (random_chance >= 10 && random_chance < 15) {
        door = game_get_link(game, 14);
        if (door) {
             link_set_open(door, FALSE); /* Closes the door automatically */
        }
    }

    /* RULE 4: TELEPORTATION. It teleports you to a different room (5% chance) */
    if (random_chance >= 15 && random_chance < 20) {
        /* Changes from the current room to room 111 (Bathroom) */
        game_set_player_location(game, 111);
    }

    /* RULE 5: REST AREA. You recover health in the Lunchroom (ID 16) (30% chance) */
    if (random_chance >= 0 && random_chance < 30 && player_loc == 16) {
        /* Prevent health from increasing infinitely */
        if (player_get_health(current_player) < 5) {
            player_modify_health(current_player, 1);
        }
    }

    /* RULE 6: TRAP OF THE MUSEUM. You slip in the Art Room (ID 15) (5% chance) */
    if (random_chance >= 30 && random_chance < 35 && player_loc == 15) {
        player_modify_health(current_player, -1);
    }
}