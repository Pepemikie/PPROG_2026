/**
 * @brief It implements the object module
 *
 * @file object.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Object
 *
 * This struct stores all the information of a object.
 */
struct _Object {
  Id id;                    /*!< Id number of the object, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the object */
};

/** Allocates memory for a new object, sets its ID, and initializes its name to empty.*/
Object* object_create(Id id) {
  Object* newObject = NULL;

  /* Checks if the given ID is valid */
  if (id == NO_ID) return NULL;

  /* Allocates memory for the object */
  newObject = (Object*)calloc(1, sizeof(Object));
  if (newObject == NULL) {
    return NULL;
  }

/* Initializes the object ID and sets name as empty string */
  newObject->id = id;
  newObject->name[0] = '\0';

  return newObject;
}

/*Frees the memory used by the object.*/
Status object_destroy(Object* object) {
  /* Checks if the object exists */
  if (!object) {
    return ERROR;
  }

/* Frees the memory and sets pointer to NULL */
  free(object);
  object = NULL;
  return OK;
}

/*Returns the ID of the object.*/
Id object_get_id(Object* object) {
  /* Returns NO_ID if the object is NULL */
  if (!object) {
    return NO_ID;
  }
  /* Returns the object’s ID */
  return object->id;
}

/*Sets the name of the object.*/
Status object_set_name(Object* object, char* name) {
  /* Checks if object or name is NULL */
  if (!object || !name) {
    return ERROR;
  }

  /* Copies the new name into the object */
  if (!strcpy(object->name, name)) {
    return ERROR;
  }
  return OK;
}

/*Returns the name of the object.*/
const char* object_get_name(Object* object) {
  /* Returns NULL if the object doesn’t exist */
  if (!object) {
    return NULL;
  }
  /* Returns the object’s name */
  return object->name;
}

/*Prints the object’s ID and name to stdout.*/
Status object_print(Object* object) {
  /*Id idaux = NO_ID; (unused variable)*/

/* Checks if object is NULL */
  if (!object) {
    return ERROR;
  }

/* Prints object ID and name to the standard output */
  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}
