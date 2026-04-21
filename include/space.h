/**
 * @brief It defines the space module interface
 *
 * @file space.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef SPACE_H
#define SPACE_H

#include "types.h"
#include "set.h"

#define SPACE_GDESC_LINES   5 /**< Number of lines in the graphic description of a Space */
#define SPACE_GDESC_LENGTH  9 /**< Maximum length of each line in the graphic description of a Space */

/** @brief It defines the Space struct */
typedef struct _Space Space;



/*
SPACE
*/
/**
 * @brief It creates a new Space, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new Space
 * @return a new pointer to a Space struct, initialized
 */
Space* space_create(Id id);

/**
 * @brief It destroys a Space, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_destroy(Space* space);

/**
 * @brief It gets the id of a Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @return the id of the Space
 */
Id space_get_id(Space* space);

/**
 * @brief It sets the name of a Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_name(Space* space, char* name);

/**
 * @brief It gets the name of a Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @return a string with the name of the Space
 */
const char* space_get_name(Space* space);

/**
 * @brief It sets the graphic description of a Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @param gdesc a 2D array of strings with the graphic description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_gdesc(Space* space, char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1]);

/**
 * @brief It gets a line of the graphic description of a Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @param line the index of the graphic description line to retrieve
 * @return a string with the requested line of the graphic description
 */
char* space_get_gdesc(Space* space, int line);

/**
 * @brief It sets whether a Space has been discovered (F12, I3)
 * @author Rodrigo Cruz Asensio
 *
 * @param space a pointer to the Space
 * @param discovered discovery status to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_discovered(Space *space, Bool discovered);

/**
 * @brief It gets whether a Space has been discovered (F12, I3)
 * @author Rodrigo Cruz Asensio
 *
 * @param space a pointer to the Space
 * @return TRUE if discovered, FALSE otherwise
 */
Bool space_get_discovered(Space *space);


/*
OBJECTS
*/
/**
 * @brief It adds an object to the Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @param id the id of the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_add_object(Space* space, Id id);

/**
 * @brief It removes an object from the Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @param id the id of the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_del_object(Space* space, Id id);

/**
 * @brief It checks whether an object is in the Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @param id the id of the object to search for
 * @return TRUE if the object is in the Space, FALSE otherwise
 */
Bool space_has_object(Space* space, Id id);

/**
 * @brief It gets the array of object ids stored in the Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @return a pointer to the array of object ids in the Space
 */
Id* space_get_objects(Space* space);

/**
 * @brief It gets the number of objects in the Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @return the number of objects stored in the Space
 */
int space_get_number_of_objects(Space* space);


/*
CHARACTERS
*/
/**
 * @brief It sets the character located in the Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @param id the id of the character to be assigned to the Space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_set_character(Space* space, Id id);

/**
 * @brief It adds a character to the Space
 * 
 * @param space a pointer to the Space
 * @param id the id of the character to be added to the Space
 * @return OK, if everything goes well or ERROR if there was some mistake 
 */
Status space_add_character(Space *space, Id id);

/**
 * @brief It gets the id of the character located in the Space
 * @author Jose Miguel Romero Oubina
 *
 * @param space a pointer to the Space
 * @return a pointer to the id of the character in the Space, or NULL if there is none
 */
Id *space_get_character(Space *space);
/**
 * @brief It checks whether a character is in the Space
 * 
 * @param space a pointer to the Space
 * @param character_id the id of the character to search for
 * @return TRUE if the character is in the Space, FALSE otherwise
 */
Bool space_has_character(Space *space, Id character_id);

/**
 * @brief It gets the number of characters in the Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @return the number of characters stored in the Space
 */
int space_get_number_of_characters(Space* space);


#ifdef DEBUG
/**
 * @brief It prints the data of a Space
 * @author Profesores PPROG
 *
 * @param space a pointer to the Space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status space_print(Space* space);
#endif
#endif