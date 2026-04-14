/**
 * @brief It defines the character interpreter interface
 *
 * @file character.h
 * @author Jorge Garcia Garrido
 * @version 1
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/**
 * @brief Size of the graphic description string, as defined in the project statement
 */
#define GDESC_SIZE 7

/**
 * @brief Opaque type representing a game character
 */
typedef struct _Character Character;

/**
 * @brief It creates a new character, allocating memory and initializing its members
 * @author Jorge Garcia Garrido
 *
 * @param id the identification number for the new character
 * @return a pointer to the new character, initialized, or NULL if allocation failed
 */
Character* character_create(Id id);

/**
 * @brief It destroys a character, freeing the allocated memory
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character that must be destroyed
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_destroy(Character* c);

/**
 * @brief It gets the id of a character
 * @author Jose Miguel Romero Oubina
 *
 * @param c a pointer to the character
 * @return the id of the character, or NO_ID if the pointer is NULL
 */
Id character_get_id(Character* c);

/**
 * @brief It gets the name of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @return a string with the name of the character, or NULL if the pointer is NULL
 */
const char* character_get_name(Character* c);

/**
 * @brief It sets the name of a character
 * @author Jose Miguel Romero Oubina
 *
 * @param c a pointer to the character
 * @param name a string with the name to store
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_set_name(Character* c, char* name);

/**
 * @brief It gets the graphic description of a character
 * @author Jose Miguel Romero Oubina
 *
 * @param c a pointer to the character
 * @return a string with the graphic description of the character, or NULL if the pointer is NULL
 */
char* character_get_gdesc(Character* c);

/**
 * @brief It sets the graphic description of a character
 * @author Jose Miguel Romero Oubina
 *
 * @param c a pointer to the character
 * @param gdesc a string with the graphic description to store
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_set_gdesc(Character* c, char* gdesc);

/**
 * @brief It gets the health of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @return an integer with the health points of the character, or -1 if the pointer is NULL
 */
int character_get_health(Character* c);

/**
 * @brief It sets the health of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @param health the health value to assign to the character
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_set_health(Character* c, int health);

/**
 * @brief It checks whether a character is friendly
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @return TRUE if the character is friendly, FALSE otherwise
 */
Bool character_is_friendly(Character* c);

/**
 * @brief It sets the friendly status of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @param friendly the friendly status to assign to the character
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_set_friendly(Character* c, Bool friendly);

/**
 * @brief It gets the message of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @return a string with the message of the character, or NULL if the pointer is NULL
 */
const char* character_get_message(Character* c);

/**
 * @brief It sets the message of a character
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @param message the message string to assign to the character
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_set_message(Character* c, char* message);

#ifdef DEBUG
/**
 * @brief It prints the data of a character to the standard output
 * @author Jorge Garcia Garrido
 *
 * @param c a pointer to the character
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status character_print(Character* c);
#endif

#endif /* CHARACTER_H */