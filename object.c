

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"

struct _Object {
  Id id;
  char name[WORD_SIZE];
};

/** Crea un objeto nuevo inicializando su ID y nombre */
Object* object_create(Id id) {
  Object *new_object = NULL;

  if (id == NO_ID) return NULL;

  new_object = (Object *) malloc(sizeof (Object));
  if (new_object == NULL) return NULL;

  new_object->id = id;
  new_object->name[0] = '\0';

  return new_object;
}

/** Libera la memoria de un objeto */
Status object_destroy(Object* object) {
  if (!object) return ERROR;

  free(object);
  return OK;
}

/** Devuelve el ID del objeto */
Id object_get_id(Object* object) {
  if (!object) return NO_ID;
  return object->id;
}

/** Cambia el nombre del objeto */
Status object_set_name(Object* object, char* name) {
  if (!object || !name) return ERROR;

  if (!strcpy(object->name, name)) return ERROR;

  return OK;
}

/** Devuelve el nombre del objeto */
const char* object_get_name(Object* object) {
  if (!object) return NULL;
  return object->name;
}

/** Imprime los datos del objeto para depuración */
Status object_print(Object* object) {
  if (!object) return ERROR;

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  return OK;
}