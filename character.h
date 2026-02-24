/**
 * @brief It defines the character interpreter interface
 *
 * @file character.h
 * @author Jorge Garcia Garrido
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/*Defines the size of the graphic description depending on the statement*/
#define GDESC_SIZE 7

typedef struct _Character Character;

/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author  Jorge Garcia Garrido
 *
 * @param id the identification number for the new chracter
 * @return a new character, initialized
 */
Character* character_create(Id id);

/**
 * @brief It destroys a character, freeing the allocated memory
 * @author  Jorge Garcia Garrido
 *
 * @param player a pointer to the character that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_destroy(Character* c);

/* Getters y Setters necesarios para el F4 */
/**
 * @brief It gets the id of a character
 * @author  Jorge Garcia Garrido
 *
 * @param player a pointer to the character
 * @return the id of character
 */
Id character_get_id(Character* c);

/**
 * @brief It gets the name of a character
 * @author  Jorge Garcia Garrido
 *
 * @param player a pointer to the character
 * @return  a string with the name of the character
 */
const char* character_get_name(Character* c);

/**
 * @brief It sets the name of a character
 * @author Jorge Garcia Garrido
 *
 * @param player a pointer to the character
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_name(Character* c, char* name);

int character_get_health(Character* c);

/**
 * @brief It sets the health of the character
 * @author Jorge Garcia Garrido
 *
 * @param player a pointer to the player
 * @param object_id is the object's id that is going to be passed to the player's 
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status character_set_health(Character* c, int health);

Bool character_is_friendly(Character* c);
Status character_set_friendly(Character* c, Bool friendly);

const char* character_get_message(Character* c);
Status character_set_message(Character* c, char* message);

Status character_print(Character* c);

#endif