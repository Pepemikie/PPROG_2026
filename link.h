/**
 * @brief It defines the link module
 *
 * @file link.h
 * @version 1
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"

typedef enum {
  N = 0,
  S = 1,
  E = 2,
  W = 3,
  UNKNOWN_DIR = 4
} Direction;

typedef struct _Link Link;

/**   It creates a new Link */
Link* link_create(Id id);

/**   It destroys a Link */
Status link_destroy(Link* link);

/**   It gets the id of a Link */
Id link_get_id(Link* link);

/**   It sets the name of a Link */
Status link_set_name(Link* link, char* name);

/**   It gets the name of a Link */
const char* link_get_name(Link* link);

/**   It sets the origin space of a Link */
Status link_set_origin(Link* link, Id origin);

/**   It gets the origin space of a Link */
Id link_get_origin(Link* link);

/**   It sets the destination space of a Link */
Status link_set_destination(Link* link, Id destination);

/**   It gets the destination space of a Link */
Id link_get_destination(Link* link);

/**   It sets the direction of a Link */
Status link_set_direction(Link* link, Direction direction);

/**   It gets the direction of a Link */
Direction link_get_direction(Link* link);

/**   It sets whether a Link is open or closed */
Status link_set_open(Link* link, Bool open);

/**   It gets whether a Link is open or closed */
Bool link_get_open(Link* link);

#ifdef DEBUG
/**   It prints the data of a Link */
Status link_print(Link* link);
#endif

#endif