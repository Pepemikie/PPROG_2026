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
  Id object;              /*!< Whether the space has an object or not */
};

/*Allocates memory for a new space and initializes its ID, name, connections, and object*/
Space* space_create(Id id) {
  Space* newSpace = NULL;

/* Checks if the given ID is valid */
  if (id == NO_ID) return NULL;

  /* Allocates memory for the space */
  newSpace = (Space*)calloc(1, sizeof(Space));
  if (newSpace == NULL) {
    return NULL;
  }

/* Initializes the space ID, name, links, and object */
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->north = NO_ID;
  newSpace->south = NO_ID;
  newSpace->east = NO_ID;
  newSpace->west = NO_ID;
  newSpace->object = NO_ID;

  return newSpace;
}

/*Frees the memory used by the space.*/
Status space_destroy(Space* space) {
  /* Checks if the space exists */
  if (!space) {
    return ERROR;
  }

  /* Frees memory used by the space */
  free(space);
  return OK;
}

/*Returns the ID of the space.*/
Id space_get_id(Space* space) {
  /* Returns NO_ID if the space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
  /* Returns the space’s ID */
  return space->id;
}

/*Sets the name of the space.*/
Status space_set_name(Space* space, char* name) {
  /* Checks if space or name is NULL */
  if (!space || !name) {
    return ERROR;
  }

/* Copies the name into the space structure */
  if (!strcpy(space->name, name)) {
    return ERROR;
  }
  return OK;
}

/*Returns the name of the space.*/
const char* space_get_name(Space* space) {
  /* Returns NULL if space doesn’t exist */
  if (!space) {
    return NULL;
  }
    /* Returns the space’s name */
  return space->name;
}

/*Sets the ID of the space to the north.*/
Status space_set_north(Space* space, Id id) {
  /* Checks if space exists and ID is valid */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Sets the link for the corresponding direction */
  space->north = id;
  return OK;
}

/*Returns the ID of the north space.*/
Id space_get_north(Space* space) {
  /* Returns NO_ID if space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
  /* Returns the ID of the linked space in the given direction */
  return space->north;
}

/*Sets the ID of the space to the south.*/
Status space_set_south(Space* space, Id id) {
  /* Checks if space exists and ID is valid */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Sets the link for the corresponding direction */
  space->south = id;
  return OK;
}

/*Returns the ID of the south space.*/
Id space_get_south(Space* space) {
  /* Returns NO_ID if space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
  /* Returns the ID of the linked space in the given direction */
  return space->south;
}

/*Sets the ID of the space to the east.*/
Status space_set_east(Space* space, Id id) {
    /* Checks if space exists and ID is valid */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Sets the link for the corresponding direction */
  space->east = id;
  return OK;
}

/*Returns the ID of the east space.*/
Id space_get_east(Space* space) {
  /* Returns NO_ID if space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
  /* Returns the ID of the linked space in the given direction */
  return space->east;
}

/*Sets the ID of the space to the west.*/
Status space_set_west(Space* space, Id id) {
    /* Checks if space exists and ID is valid */
  if (!space || id == NO_ID) {
    return ERROR;
  }
  /* Sets the link for the corresponding direction */
  space->west = id;
  return OK;
}

/*Returns the ID of the west space.*/
Id space_get_west(Space* space) {
  /* Returns NO_ID if space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
/* Returns the ID of the linked space in the given direction */
  return space->west;
}

/*Assigns an object ID to the space.*/
Status space_set_object(Space* space, Id value) {
  /* Checks if space exists */
  if (!space) {
    return ERROR;
  }
  /* Assigns an object ID to the space */
  space->object = value;
  return OK;
}

/*Returns the object ID in the space (or NO_ID if empty).*/
Id space_get_object(Space* space) {
  /* Returns NO_ID if space doesn’t exist */
  if (!space) {
    return NO_ID;
  }
  /* Returns the object ID in the space */
  return space->object;
}

/*Prints the space’s ID, name, links in all directions, and whether it contains an object*/
Status space_print(Space* space) {
  Id idaux = NO_ID;

/* Checks if space exists */
  if (!space) {
    return ERROR;
  }

  /* 1. Print the id and the name of the space */
  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* 2. For each direction, print its link */
  idaux = space_get_north(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> North link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No north link.\n");
  }
  idaux = space_get_south(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> South link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No south link.\n");
  }
  idaux = space_get_east(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> East link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No east link.\n");
  }
  idaux = space_get_west(space);
  if (idaux != NO_ID) {
    fprintf(stdout, "---> West link: %ld.\n", idaux);
  } else {
    fprintf(stdout, "---> No west link.\n");
  }

  /* 3. Print if there is an object in the space or not */
  if (space_get_object(space) != NO_ID) {
    fprintf(stdout, "---> Object in the space.\n");
  } else {
    fprintf(stdout, "---> No object in the space.\n");
  }

  return OK;
}
