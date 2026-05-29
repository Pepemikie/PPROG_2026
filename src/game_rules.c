/**
 * @brief It implements the game rules module
 *
 * @file game_rules.c
 * @author Rodrigo Cruz Asensio
 * @version 2
 * @date 28-05-2026
 * @copyright GNU Public License
 */

#include "game_rules.h"
#include "game.h"
#include "player.h"
#include "inventory.h"
#include <stdlib.h>
#include <time.h>

/*
Regla 1. La corona aparece cuando Batman muere
Regla 2. Si estás en la sala 12, tienes un 10% más de probabilidad de ganar en un ataque a Batman
Regla 3. La puerta que se abre con la llave se cierra automáticamente con un 10% de probabilidad
Regla 4. Recuperas, con una probabilidad del 30%, 1 de vida si estás en el Lunchroom (ID 16)
Regla 5. Hay un 5% de probabilidad de que cuando se entre en el Art Room (ID 15), se caiga y pierda 1 de vida
Regla 6. Si matas al policia de la sala 12, consigues una pistola que te da más vida al usarla
Regla 7. Si matas a la guia te dará la llave para poder pasar de la 12 a la 131 e ir a por BATMAN mas facil
Regla 8. Solo ganas el juego si entras a la sala de la corona con la corona
*/


void game_rules_update(Game *game) {
    Player *current_player = NULL;
    int random_chance = 0;
    Id player_loc = NO_ID;

    Link *door = NULL;
    Id space_id = NO_ID;

    Object *crown = NULL;
    Object *gun = NULL;
    Object *key = NULL;

    Character *batman = NULL;
    Character *police = NULL;
    Character *guide = NULL;

    int batman_surprise_attack = 3;

    if (!game) return;

    /* Generate a random number between 0 and 99 */
    random_chance = rand() % 100;       
    
    /* Get the current player */
    current_player = game_get_player(game); 
    if (!current_player) return;

    player_loc = player_get_location(current_player); /* Get the player's current location */

    /* Rule 1. The crown appears when Batman dies */
    batman = game_get_character_by_name(game, "Batman");
    if (batman && (character_get_health(batman) <= 0) && 
        (game_get_object_location(game, object_get_id(game_get_object_by_name(game, "Crown"))) == NO_ID) && 
        (inventory_has_object(player_get_backpack(current_player), object_get_id(game_get_object_by_name(game, "Crown"))) == FALSE)) {
    
        crown = game_get_object_by_name(game, "Crown");
        space_id = game_get_character_location(game, character_get_id(batman));
        if (space_id != NO_ID && crown) {
            game_set_object_location(game, space_id, object_get_id(crown));
        }
    }

    /* Rule 2. If you are in 12 room, you have 20% chance of receiving a Batman attack (only for the player who decided to enter) */
    if (random_chance < 20 && player_loc == game_get_character_location(game, character_get_id(game_get_character_by_name(game, "Batman")))) {
        /* Batman takes away 3 health points */
        if (player_get_health(current_player) < batman_surprise_attack) {
            batman_surprise_attack = player_get_health(current_player);
        }
        else {
            player_set_health(current_player, player_get_health(current_player) - batman_surprise_attack);
        }
    }

    /* Rule 3. The door that opens with key, closes automatically with a 10% chance */
    else if (random_chance >= 20 && random_chance < 30) {
        door = game_get_link_by_name(game, "Door");
        if (door) {
            link_set_open(door, FALSE); /* Closes the door automatically */
        }
    }

    /* Rule 4. You gain, with a 30% chance, 1 point of health if you are in the Lunchroom */
    else if (random_chance >= 30 && random_chance < 60) {
        if (player_loc == space_get_id(game_get_space_by_name(game, "Lunchroom"))) {
            /* Prevent health from increasing infinitely */
            if (player_get_health(current_player) < 10) {
                player_set_health(current_player, player_get_health(current_player) + 1);
            }
        }
    }

    /* Rule 5. There is a 10% chance of slipping in the Art Room and losing 1 health point */
    else if (random_chance >= 60 && random_chance < 70) {
        if (player_loc == space_get_id(game_get_space_by_name(game, "Art Room"))) {
            player_set_health(current_player, player_get_health(current_player) - 1);
        }
    }

    /* Rule 6. If you kill the policeman in room 12, you get a gun that gives you more health when used */
    police = game_get_character_by_name(game, "Police");
    if (police && (character_get_health(police) <= 0) && 
        (game_get_object_location(game, object_get_id(game_get_object_by_name(game, "Gun"))) == NO_ID) && 
        (inventory_has_object(player_get_backpack(current_player), object_get_id(game_get_object_by_name(game, "Gun"))) == FALSE)) {
    
        gun = game_get_object_by_name(game, "Gun");
        space_id = game_get_character_location(game, character_get_id(police));
        if (space_id != NO_ID && gun) {
            game_set_object_location(game, space_id, object_get_id(gun));
        }
    }

    /* Rule 7. If you kill the guide you will get a key that allows you to open a door and make it easier to find BATMAN */
    guide = game_get_character_by_name(game, "Guide");
    if (guide && (character_get_health(guide) <= 0) && 
        (game_get_object_location(game, object_get_id(game_get_object_by_name(game, "Key"))) == NO_ID) && 
        (inventory_has_object(player_get_backpack(current_player), object_get_id(game_get_object_by_name(game, "Key"))) == FALSE)) {
    
        key = game_get_object_by_name(game, "Key");
        space_id = game_get_character_location(game, character_get_id(guide));
        if (space_id != NO_ID && key) {
            game_set_object_location(game, space_id, object_get_id(key));
        }
    }

    /* Rule 8. You only win if you enter in the crwon room while you have the crown in your inventory */
    if (player_has_object(current_player, object_get_id(game_get_object_by_name(game, "Crown"))) == TRUE){
        if(player_get_location(current_player) == space_get_id(game_get_space_by_name(game, "Crown Room"))){
            game_set_finished(game, TRUE);
        }
    }

}
