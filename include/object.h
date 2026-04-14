/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

/** @brief It defines the Object struct */
typedef struct _Object Object;

/**
 * @brief It creates a new Object, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @param id the identification number for the new Object
 * @return a new pointer to an Object struct, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destroys an Object, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object* object);

/**
 * @brief It gets the id of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @return the id of the Object
 */
Id object_get_id(Object* object);

/**
 * @brief It sets the name of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @return a string with the name of the Object
 */
const char* object_get_name(Object* object);

/**
 * @brief It sets the description of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @param description a string with the description to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_description(Object* object, char* description);

/**
 * @brief It gets the description of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @return a string with the description of the Object
 */
const char* object_get_description(Object* object);

#ifdef DEBUG
/**
 * @brief It prints the data of an Object
 * @author Profesores PPROG
 *
 * @param object a pointer to the Object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object* object);
#endif
#endif