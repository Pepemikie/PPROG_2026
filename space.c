/**
 * @brief It implements the space module
 *
 * @file space.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Space
 *
 * This struct stores all the information of a space.
 */
struct _Space {
  Id id;                    /*!< Id number of the space, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the space */
  Id north;                 /*!< Id of the space at the north */
  Id south;                 /*!< Id of the space at the south */
  Id east;                  /*!< Id of the space at the east */
  Id west;                  /*!< Id of the space at the west */
  Set *objects;
  Id character;              /*!< Whether the space has an object or not */
};

/** space_create allocates memory for a new space
 *  and initializes its members
 */
Space* space_create(Id id) {
  Space* newSpace = NULL;

  /* Error control */
  if (id == NO_ID) return NULL;

  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

  /* Initialization of an empty space*/
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->objects = set_create();
  newSpace->character = NO_ID;

  return newSpace;
}

Status space_destroy(Space* space) {
  if (!space) {
    return ERROR;
  }

  set_destroy(space->objects);

  free(space);
  return OK;
}

Id space_get_id(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->id;
}

Status space_set_name(Space* space, char* name) {
  if (!space || !name) {
    return ERROR;
  }

  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

const char* space_get_name(Space* space) {
  if (!space) {
    return NULL;
  }
  return space->name;
}

Status space_set_north(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->north = id;
  return OK;
}

Id space_get_north(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->north;
}

Status space_set_south(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->south = id;
  return OK;
}

Id space_get_south(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->south;
}

Status space_set_east(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->east = id;
  return OK;
}

Id space_get_east(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->east;
}

Status space_set_west(Space* space, Id id) {
  if (!space || id == NO_ID) {
    return ERROR;
  }
  space->west = id;
  return OK;
}

Id space_get_west(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->west;
}


Status space_add_object(Space* space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  

  return set_add(space->objects, id);
}


Status space_del_object(Space* space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  
  return set_del(space->objects, id);
}


Bool space_has_object(Space* space, Id id) {
  if (!space || id == NO_ID) return FALSE;
  
 
  return (set_find(space->objects, id) != -1);
}


Status space_set_character(Space* space, Id id) {
  if (!space) {
    return ERROR;
  }
  space->character = id;
  return OK;
}


Id space_get_character(Space* space) {
  if (!space) {
    return NO_ID;
  }
  return space->character;
}

/* space.c */

Status space_print(Space* space) {
  Id idaux = NO_ID;

  if (!space) {
    return ERROR;
  }

  /* 1. Imprimir ID y Nombre */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. Imprimir Direcciones */
  idaux = space_get_north(space);
  fprintf(stdout, "---> North link: %ld\n", idaux);
  idaux = space_get_south(space);
  fprintf(stdout, "---> South link: %ld\n", idaux);
  idaux = space_get_east(space);
  fprintf(stdout, "---> East link: %ld\n", idaux);
  idaux = space_get_west(space);
  fprintf(stdout, "---> West link: %ld\n", idaux);

  /* 3. Imprimir Objetos (F3) */
  fprintf(stdout, "---> Objects: ");
  set_print(space->objects);

  /* 4. ARREGLO F6: Imprimir Personaje */
  /* Mostramos el ID del personaje que vive en esta habitación */
  fprintf(stdout, "---> Character ID: %ld\n", space->character);

  return OK;
}