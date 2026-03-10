/**
 * @brief It implements functions to manage a set of Ids
 *
 * @file set.c
 * @author Jorge Garcia Garrido
 * @version 0
 * @date 23-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"

/*Struct that is hidden to the rest of the program */
struct _Set {
  Id ids[MAX_SET]; /*Array of ids*/
  int n_ids;       /*Total amount of ids*/
};

Set* set_create() {
  Set *new_set = NULL;
  int i;

  new_set = (Set *) malloc(sizeof (Set));
  if (new_set == NULL) {
    return NULL;
  }

  /* Inicializamos el conjunto */
  new_set->n_ids = 0;
  for (i = 0; i < MAX_SET; i++) {
    new_set->ids[i] = NO_ID;
  }

  return new_set;
}

Status set_destroy(Set* set) {
  if (!set) {
    return ERROR;
  }

  free(set);
  return OK;
}

Status set_add(Set* set, Id id) {
  if (!set || id == NO_ID || set->n_ids >= MAX_SET) {
    return ERROR;
  }

  /* Si el elemento ya existe, no hacemos nada pero devolvemos OK (es un conjunto) */
  if (set_find(set, id) != -1) {
    return OK;
  }

  /* Añadimos el nuevo ID al final */
  set->ids[set->n_ids] = id;
  set->n_ids++;

  return OK;
}

Status set_del(Set* set, Id id) {
  int i, index;

  if (!set || id == NO_ID) {
    return ERROR;
  }

  /* Buscamos la posición del elemento */
  index = set_find(set, id);
  if (index == -1) {
    return ERROR;
  }

  /* Algoritmo de borrado: Desplazamos los elementos siguientes para cerrar el hueco */
  for (i = index; i < set->n_ids - 1; i++) {
    set->ids[i] = set->ids[i + 1];
  }

  /* Limpiamos la última posición que ahora queda libre */
  set->ids[set->n_ids - 1] = NO_ID;
  set->n_ids--;

  return OK;
}

int set_find(Set* set, Id id) {
  int i;

  if (!set || id == NO_ID) {
    return -1;
  }

  /* Búsqueda lineal en el array */
  for (i = 0; i < set->n_ids; i++) {
    if (set->ids[i] == id) {
      return i;
    }
  }

  return -1;
}

int set_get_n_ids(Set* set) {
  if (!set) {
    return -1;
  }
  return set->n_ids;
}

Status set_print(Set* set) {
  int i;

  if (!set) {
    return ERROR;
  }

  fprintf(stdout, "--> Set (n_ids: %d): ", set->n_ids);
  for (i = 0; i < set->n_ids; i++) {
    fprintf(stdout, "%ld ", set->ids[i]);
  }
  fprintf(stdout, "\n");

  return OK;
}