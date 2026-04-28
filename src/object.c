/**
 *   It implements the object functionality
 *
 * @file object.c
 * @author Jose Miguel Romero Oubina
 * @version 0
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

/** @brief Structure for the Object type */
struct _Object {
  Id id;                  /**< The unique identifier of the object */
  char name[WORD_SIZE]; /**< The name of the object */
  char description[WORD_SIZE]; /**< The description of the object */
  int health;            /**< Health points added/removed when taken */
  Bool movable;          /**< Whether the object can be moved */
  Id dependency;         /**< Id of the object this depends on */
  Id open;               /**< Id of the link this object can open */
};

/*   It creates a new Object, allocating memory and initializing its members */
Object* object_create(Id id) {
  Object *new_object = NULL;
  if (id == NO_ID) return NULL; /* error control */

  new_object = (Object *) malloc(sizeof (Object)); /* allocates memory for the object */
  if (new_object == NULL) return NULL;

  new_object->id = id;
  strcpy(new_object->name, "");
  strcpy(new_object->description, ""); /* initializes name and description to empty strings */
  new_object->health = 0;
  new_object->movable = FALSE;
  new_object->dependency = NO_ID;
  new_object->open = NO_ID;

  return new_object;
}

/*   It destroys an Object, freeing the allocated memory */
Status object_destroy(Object* object) {
  if (!object) return ERROR;
  free(object); /* frees the object */
  return OK;
}

/*   It gets the id of an Object */
Id object_get_id(Object* object) {
  if (!object) return NO_ID;
  return object->id;
}

/*   It sets the name of an Object */
Status object_set_name(Object* object, char* name) {
  if (!object || !name) return ERROR;
  if (!strncpy(object->name, name, WORD_SIZE - 1)) return ERROR; /* copies name safely */
  object->name[WORD_SIZE - 1] = '\0';
  return OK;
}

/*   It gets the name of an Object */
const char* object_get_name(Object* object) {
  if (!object) return NULL;
  return object->name;
}

/*   It sets the description of an Object */
Status object_set_description(Object* object, char* description) {
  if (!object || !description) return ERROR;
  if (!strncpy(object->description, description, WORD_SIZE - 1)) return ERROR; /* copies description safely */
  object->description[WORD_SIZE - 1] = '\0';
  return OK;
}

/*   It gets the description of an Object */
const char* object_get_description(Object* object) {
  if (!object) return NULL;
  return object->description;
}

/*   It sets the health of an Object */
Status object_set_health(Object* object, int health) {
  if (!object) return ERROR;
  object->health = health;
  return OK;
}

/*   It gets the health of an Object */
int object_get_health(Object* object) {
  if (!object) return 0;
  return object->health;
}

/*   It sets whether an Object is movable */
Status object_set_movable(Object* object, Bool movable) {
  if (!object) return ERROR;
  object->movable = movable;
  return OK;
}

/*   It gets whether an Object is movable */
Bool object_get_movable(Object* object) {
  if (!object) return FALSE;
  return object->movable;
}

/*   It sets the dependency of an Object */
Status object_set_dependency(Object* object, Id dependency) {
  if (!object) return ERROR;
  object->dependency = dependency;
  return OK;
}

/*   It gets the dependency of an Object */
Id object_get_dependency(Object* object) {
  if (!object) return NO_ID;
  return object->dependency;
}

/*   It sets the open link of an Object */
Status object_set_open(Object* object, Id open) {
  if (!object) return ERROR;
  object->open = open;
  return OK;
}

/*   It gets the open link of an Object */
Id object_get_open(Object* object) {
  if (!object) return NO_ID;
  return object->open;
}

#ifdef DEBUG
/*   It prints the data of an Object */
Status object_print(Object* object) {
  if (!object) return ERROR;
  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Description: %s; Health: %d; Movable: %d; Dependency: %ld; Open: %ld)\n", 
          object->id, object->name, object->description, object->health, object->movable, object->dependency, object->open); /* prints id, name and description */
  return OK;
}
#endif