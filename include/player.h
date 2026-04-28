/**
 * @brief It defines the player module interface
 *
 * @file player.h
 * @author Jose Miguel Romero Oubina
 * @version 2
 * @date 25-03-2026
 * @copyright GNU Public License
 */
#ifndef PLAYER_H
#define PLAYER_H

#define P_GDESC_SIZE 7/**< Maximum size of the player's description */
#define MAX_BACKPACK_SIZE 3/**< Maximum size of the player's backpack */

#include "types.h"
#include "inventory.h"

/** @brief It defines the Player struct */
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
 * @brief It adds an object to the player's inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param player a pointer to the Player
 * @param object the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_add_object(Player* player, Id object);

/**
 * @brief It removes an object from the player's inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param player a pointer to the Player
 * @param object the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_del_object(Player* player, Id object);

/**
 * @brief It checks if a Player has a specific object in their inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param player a pointer to the Player
 * @param object the id of the object to check
 * @return TRUE, if the Player has the object, FALSE if they don't or if there was some mistake
 */
Bool player_has_object(Player* player, Id object);

/**
 * @brief It gets the id of an object in the player's inventory by its index
 * @author Jose Miguel Romero Oubina
 *
 * @param player a pointer to the Player
 * @param index the position of the object in the inventory (0-based)
 * @return the id of the object at the given index, or NO_ID if there was some mistake
 */
Id player_get_object(Player* player, int index);

/**
 * @brief It gets the player's inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param player a pointer to the Player
 * @return a pointer to the Inventory struct representing the player's backpack, or NULL if there was some mistake
 */
Inventory* player_get_backpack(Player* player);

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

/**
 * @brief It sets the maximum number of objects that a Player can carry in their inventory (F11, I3)
 * @author Rodrigo Cruz Asensio
 * 
 * @param player a pointer to the Player
 * @param max_objs the maximum number of objects 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_set_max_objs(Player* player, int max_objs);

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
 * @brief It modifies the health of a Player by adding the given amount
 * @author Profesores PPROG
 *
 * @param player a pointer to the Player
 * @param health the health points to add (can be negative)
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status player_modify_health(Player* player, int health);

#endif