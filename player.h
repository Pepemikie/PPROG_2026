/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Cesar Soto Vega & Jose Miguel Romero Oubina
 * @version 1
 * @date 14-02-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

#define PLAYER_ID 1

typedef struct _Player Player;

/**
 * @brief It creates a new player, allocating memory and initializing its members
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param id the identification number for the new player
 * @return a new player, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a player, freeing the allocated memory
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a player
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @return the id of player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a player
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a player
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @return  a string with the name of the player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the id the player obtains the ID of the object obtained
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @param object_id is the object's id that is going to be passed to the player's 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object_id(Player* player, Id object_id);

/**
 * @brief It gets whether the player has an object id or not
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @return the id of the object id
 */
Id player_get_object_id(Player* player);

/**
 * @brief It sets the id the player obtains the ID of the player located
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @return a boolean, specifying if the player is located (TRUE) or not (FALSE)
 */
Status player_set_location(Player* player, Id location_id);

/**
 * @brief It gets whether the player is located or not
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * @param player a pointer to the player
 * @return the location of the player
 */
Id player_get_location(Player* player);

/**
 * @brief It prints the player information
 * @author  Cesar Soto Vega & Jose Miguel Romero Oubina
 *
 * This fucntion shows the id and name of the player, the players that surrounds it and wheter it has an object or not.
 * @param player a pointer to the player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);

#endif
