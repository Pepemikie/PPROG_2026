/**
 *   It implements the space module
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

struct _Space {
  Id id;
  char name[WORD_SIZE + 1];
  Set *objects;
  Id character;
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1];
};

/*   It creates a new Space, allocating memory and initializing its members */
Space *space_create(Id id) {
  Space *newSpace = NULL;
  int i;

  if (id == NO_ID) return NULL; /* error control */

  newSpace = (Space *)calloc(1, sizeof(Space)); /* allocates and zeroes memory */
  if (newSpace == NULL) return NULL;

  /* initializes all fields by default */
  newSpace->id = id;
  newSpace->name[0] = '\0';
  newSpace->character = NO_ID;

  newSpace->objects = set_create(); /* creates the object set */
  if (!newSpace->objects) {
    free(newSpace);
    return NULL;
  }

  for (i = 0; i < SPACE_GDESC_LINES; i++)
    strcpy(newSpace->gdesc[i], "         "); /* fills gdesc lines with spaces */

  return newSpace;
}

/*   It destroys a Space, freeing the allocated memory */
Status space_destroy(Space *space) {
  if (!space) return ERROR;

  if (space->objects) set_destroy(space->objects); /* destroys the object set */

  free(space);
  return OK;
}

/*   It gets the id of a Space */
Id space_get_id(Space *space) {
  if (!space) return NO_ID;
  return space->id;
}

/*   It gets the name of a Space */
const char *space_get_name(Space *space) {
  if (!space) return NULL;
  return space->name;
}

/*   It sets the name of a Space */
Status space_set_name(Space *space, char *name) {
  if (!space || !name) return ERROR;
  if (strlen(name) >= WORD_SIZE) return ERROR; /* checks name length */
  strcpy(space->name, name);
  return OK;
}

/*   It adds an object to the Space */
Status space_add_object(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  return set_add(space->objects, id); /* delegates to the set module */
}

/*   It removes an object from the Space */
Status space_del_object(Space *space, Id id) {
  if (!space || id == NO_ID) return ERROR;
  return set_del(space->objects, id); /* delegates to the set module */
}

/*   It checks whether an object is in the Space */
Bool space_has_object(Space *space, Id id) {
  if (!space || id == NO_ID) return FALSE;
  if (set_find(space->objects, id) == -1) return FALSE; /* not found */
  return TRUE;
}

/*   It gets the array of object ids stored in the Space */
Id *space_get_objects(Space *space) {
  if (!space) return NULL;
  return set_get_ids(space->objects); /* delegates to the set module */
}

/*   It gets the number of objects in the Space */
int space_get_number_of_objects(Space *space) {
  if (!space) return -1;
  return set_get_n_ids(space->objects); /* delegates to the set module */
}

/*   It sets the character located in the Space */
Status space_set_character(Space *space, Id id) {
  if (!space) return ERROR;
  space->character = id; /* assigns the character id to the space */
  return OK;
}

/*   It gets the id of the character located in the Space */
Id space_get_character(Space *space) {
  if (!space) return NO_ID;
  return space->character;
}

/*   It sets the graphic description of a Space */
Status space_set_gdesc(Space *space, char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1]) {
  int i;
  if (!space || !gdesc) return ERROR;

  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    if (strlen(gdesc[i]) <= SPACE_GDESC_LENGTH) { /* checks line length before copying */
      strcpy(space->gdesc[i], gdesc[i]);
    } else {
      return ERROR;
    }
  }
  return OK;
}

/*   It gets a line of the graphic description of a Space */
char *space_get_gdesc(Space *space, int line) {
  if (!space) return NULL;
  if (line < 0 || line >= SPACE_GDESC_LINES) return NULL; /* checks line index bounds */
  return space->gdesc[line];
}

#ifdef DEBUG
/*   It prints the data of a Space */
Status space_print(Space *space) {
  Id idaux = NO_ID;

  if (!space) return ERROR;

  fprintf(stdout, "--> Space (Id: %ld; Name: %s)\n", space->id, space->name);

  /* prints all directional links */
  idaux = space_get_north(space);
  fprintf(stdout, "---> North link: %ld\n", idaux);
  idaux = space_get_south(space);
  fprintf(stdout, "---> South link: %ld\n", idaux);
  idaux = space_get_east(space);
  fprintf(stdout, "---> East link: %ld\n", idaux);
  idaux = space_get_west(space);
  fprintf(stdout, "---> West link: %ld\n", idaux);

  fprintf(stdout, "---> Objects: ");
  if (set_print(space->objects) == ERROR) { /* prints all objects in the space */
    fprintf(stdout, "ERROR printing objects\n");
  }

  fprintf(stdout, "---> Character ID: %ld\n", space->character);

  return OK;
}
#endif