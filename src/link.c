/**
 *   It implements the link module
 *
 * @file link.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 28-03-2026
 * @copyright GNU Public License
 */

#include "link.h"
#include "types.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Structure for the Link type */
struct _Link {
  Id id; /**< The unique identifier of the link */
  char name[WORD_SIZE + 1]; /**< The name of the link */
  Id origin; /**< The id of the origin space */
  Id destination; /**< The id of the destination space */
  Direction direction; /**< The direction of the link from the origin space */
  Bool open; /**< Whether the link is open or closed */
};

/*   It creates a new Link, allocating memory and initializing its members */
Link *link_create(Id id) {
  Link *newLink = NULL;

  if (id == NO_ID) return NULL; /* error control */

  newLink = (Link *)calloc(1, sizeof(Link)); /* allocates and zeroes memory */
  if (newLink == NULL) return NULL;

  /* initializes all fields by default */
  newLink->id = id;
  newLink->name[0] = '\0';
  newLink->origin = NO_ID;
  newLink->destination = NO_ID;
  newLink->direction = UNKNOWN_DIR;
  newLink->open = FALSE;

  return newLink;
}

/*   It destroys a Link, freeing the allocated memory */
Status link_destroy(Link *link) {
  if (!link) return ERROR;
  free(link);
  return OK;
}

/*   It gets the id of a Link */
Id link_get_id(Link *link) {
  if (!link) return NO_ID;
  return link->id;
}

/*   It gets the name of a Link */
const char *link_get_name(Link *link) {
  if (!link) return NULL;
  return link->name;
}

/*   It sets the name of a Link */
Status link_set_name(Link* link, char* name) {
  if (!link || !name) return ERROR;
  strncpy(link->name, name, WORD_SIZE - 1);
  link->name[WORD_SIZE - 1] = '\0';
  return OK;
}

/*   It sets the origin space of a Link */
Status link_set_origin(Link *link, Id origin) {
  if (!link) return ERROR;
  link->origin = origin;
  return OK;
}

/*   It gets the origin space of a Link */
Id link_get_origin(Link *link) {
  if (!link) return NO_ID;
  return link->origin;
}

/*   It sets the destination space of a Link */
Status link_set_destination(Link *link, Id destination) {
  if (!link) return ERROR;
  link->destination = destination;
  return OK;
}

/*   It gets the destination space of a Link */
Id link_get_destination(Link *link) {
  if (!link) return NO_ID;
  return link->destination;
}

/*   It sets the direction of a Link */
Status link_set_direction(Link *link, Direction direction) {
  if (!link) return ERROR;
  link->direction = direction;
  return OK;
}

/*   It gets the direction of a Link */
Direction link_get_direction(Link *link) {
  if (!link) return UNKNOWN_DIR;
  return link->direction;
}

/*   It sets whether a Link is open or closed */
Status link_set_open(Link *link, Bool open) {
  if (!link) return ERROR;
  link->open = open;
  return OK;
}

/*   It gets whether a Link is open or closed */
Bool link_get_open(Link *link) {
  if (!link) return FALSE;
  return link->open;
}

#ifdef DEBUG
/*   It prints the data of a Link */
Status link_print(Link* link) {
  char *dir_str = NULL;
  if (!link) return ERROR;
  
  switch (link->direction) {
    case N: dir_str = "N"; break;
    case S: dir_str = "S"; break;
    case E: dir_str = "E"; break;
    case W: dir_str = "W"; break;
    case U: dir_str = "U"; break;
    case D: dir_str = "D"; break;
    default: dir_str = "UNKNOWN"; break;
  }
  
  fprintf(stdout, "--> Link (Id: %ld; Name: %s; Origin: %ld; Destination: %ld; Direction: %s; Open: %d)\n",
          link->id, link->name, link->origin, link->destination,
          dir_str, link->open);
  return OK;
}
#endif