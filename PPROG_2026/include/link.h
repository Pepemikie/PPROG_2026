/**
 * @brief It defines the link module interface
 *
 * @file link.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 28-03-2026
 * @copyright GNU Public License
 */

#ifndef LINK_H
#define LINK_H

#include "types.h"
#include "space.h"

typedef struct _Link Link;

/**
 * @brief It creates a new Link, allocating memory and initializing its members
 * @author Jose Miguel Romero Oubina
 *
 * @param id the identification number for the new Link
 * @return a new pointer to a Link struct, initialized
 */
Link* link_create(Id id);

/**
 * @brief It destroys a Link, freeing the allocated memory
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_destroy(Link* link);

/**
 * @brief It gets the id of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return the id of the Link
 */
Id link_get_id(Link* link);

/**
 * @brief It sets the name of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @param name a string with the name to store
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_name(Link* link, char* name);

/**
 * @brief It gets the name of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return a string with the name of the Link or NULL if there was some mistake
 */
const char* link_get_name(Link* link);

/**
 * @brief It sets the origin space of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @param origin the id of the origin space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_origin(Link* link, Id origin);

/**
 * @brief It gets the origin space of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return the id of the origin space or NO_ID if there was some mistake
 */
Id link_get_origin(Link* link);

/**
 * @brief It sets the destination space of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @param destination the id of the destination space
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_destination(Link* link, Id destination);

/**
 * @brief It gets the destination space of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return the id of the destination space or NO_ID if there was some mistake
 */
Id link_get_destination(Link* link);

/**
 * @brief It sets the direction of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @param direction the direction of the Link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_direction(Link* link, Direction direction);

/**
 * @brief It gets the direction of a Link
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return the direction of the Link or UNKNOWN_DIR if there was some mistake
 */
Direction link_get_direction(Link* link);

/**
 * @brief It sets whether a Link is open or closed
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @param open a boolean indicating whether the Link is open or closed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_set_open(Link* link, Bool open);

/**
 * @brief It gets whether a Link is open or closed
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return a boolean indicating whether the Link is open or closed
 */
Bool link_get_open(Link* link);

#ifdef DEBUG
/**
 * @brief It prints the data of a Link (only for debugging purposes)
 * @author Jose Miguel Romero Oubina
 *
 * @param link a pointer to the Link
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status link_print(Link* link);
#endif
#endif