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

struct _Object {
  Id id;
  char name[WORD_SIZE];
  char description[WORD_SIZE];
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

#ifdef DEBUG
/*   It prints the data of an Object */
Status object_print(Object* object) {
  if (!object) return ERROR;
  fprintf(stdout, "--> Object (Id: %ld; Name: %s; Description: %s)\n", object->id, object->name, object->description); /* prints id, name and description */
  return OK;
}
#endif