/**
 * @brief Define la interfaz del módulo Object
 * @file object.h
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "types.h"

typedef struct _Object Object;

/* Funciones de creación y destrucción */
Object* object_create(Id id);
Status object_destroy(Object* object);

/* Funciones get y set */
Id object_get_id(Object* object);
Status object_set_name(Object* object, char* name);
const char* object_get_name(Object* object);

/* Función de impresión para depuración */
Status object_print(Object* object);

#endif