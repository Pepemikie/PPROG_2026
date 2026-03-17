/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H

#define P_GDESC_SIZE 7

#include "types.h"

typedef struct _Player Player;

/**
 * @brief It creates a new Player, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new Player
 * @return a new pointer to a Player struct, initialized
 */
Player* player_create(Id id);

/**
 * @brief It destroys a Player, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_destroy(Player* player);

/**
 * @brief It gets the id of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return the id of the Player
 */
Id player_get_id(Player* player);

/**
 * @brief It sets the name of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_name(Player* player, char* name);

/**
 * @brief It gets the name of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return a string with the name of the Player
 */
const char* player_get_name(Player* player);

/**
 * @brief It sets the location of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @param location the id of the space where the Player is going to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_location(Player* player, Id location);

/**
 * @brief It gets the location of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return the id of the space where the Player is located
 */
Id player_get_location(Player* player);

/**
 * @brief It sets the object carried by a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @param object the id of the object to be assigned to the Player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_object(Player* player, Id object);

/**
 * @brief It gets the object carried by a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return the id of the object carried by the Player, or NO_ID if none
 */
Id player_get_object(Player* player);

#ifdef DEBUG
/**
 * @brief It prints the data of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_print(Player* player);
#endif

/**
 * @brief It gets the health of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return an integer with the health points of the Player
 */
int player_get_health(Player* player);

/**
 * @brief It sets the health of a Player
 * @author Profesores PPROG
 *
 * @param pplayer a pointer to the Player
 * @param health the health points to be assigned to the Player
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_health(Player* pplayer, int health);

/**
 * @brief It gets the graphic description of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @return a string with the graphic description of the Player
 */
const char* player_get_gdesc(Player* player);

/**
 * @brief It sets the graphic description of a Player
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @param gdesc a string with the graphic description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_gdesc(Player* player, char* gdesc);

#endif