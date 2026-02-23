/**
 * @brief It defines the object module interface
 *
 * @file object.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 03-02-2026
 * @copyright GNU Public License
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

#define OBJECT_ID 1

/*Object: estructura de datos*/
typedef struct _Object Object;

/*object: funciones create, destroy*/
/**
 * @brief It creates a new object, allocating memory and initializing its members
 * @author Jose Miguel Romero Oubina
 *
 * @param id the identification number for the new object
 * @return a new object, initialized
 */
Object* object_create(Id id);

/**
 * @brief It destroys a object, freeing the allocated memory
 * @author Jose Miguel Romero Oubina
 *
 * @param object a pointer to the object that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_destroy(Object* object);

/*object: funciones get, set*/
/**
 * @brief It gets the id of a object
 * @author Jose Miguel Romero Oubina
 *
 * @param object a pointer to the object
 * @return the id of object
 */
Id object_get_id(Object* object);

/**
 * @brief It sets the name of a object
 * @author Jose Miguel Romero Oubina
 *
 * @param object a pointer to the object
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_set_name(Object* object, char* name);

/**
 * @brief It gets the name of a object
 * @author Jose Miguel Romero Oubina
 *
 * @param object a pointer to the object
 * @return  a string with the name of the object
 */
const char* object_get_name(Object* object);

/*object: function print*/
/**
 * @brief It prints the object information
 * @author Jose Miguel Romero Oubina
 *
 * This fucntion shows the id and name of the object, the objects that surrounds it and wheter it has an object or not.
 * @param object a pointer to the object
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status object_print(Object* object);

#endif
