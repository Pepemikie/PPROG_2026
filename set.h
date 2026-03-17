/**
 * @brief It defines the set module interface
 *
 * @file set.h
 * @author  Jorge Garcia Garrido
 * @version 0
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"

#define MAX_SET 10

typedef struct _Set Set;

/**
 * @brief It creates a new empty Set, allocating memory and initializing its members
 * @author  Jorge Garcia Garrido
 *
 * @return a new pointer to a Set struct, initialized
 */
Set* set_create();

/**
 * @brief It destroys a Set, freeing the allocated memory
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_destroy(Set* set);

/**
 * @brief It adds an element to the Set if it does not already exist
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @param id the identification number to be added
 * @return OK, if everything goes well or ERROR if the Set is full or there was some mistake
 */
Status set_add(Set* set, Id id);

/**
 * @brief It removes an element from the Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @param id the identification number to be removed
 * @return OK, if everything goes well or ERROR if the element is not found or there was some mistake
 */
Status set_del(Set* set, Id id);

/**
 * @brief It searches for an id in the Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @param id the identification number to search for
 * @return the index of the element (0 to n-1), or -1 if not found
 */
int set_find(Set* set, Id id);

/**
 * @brief It gets the number of elements in the Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @return the number of elements stored, or -1 if there was some mistake
 */
int set_get_n_ids(Set* set);

/**
 * @brief It gets the id stored at a given position in the Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @param array_position the index of the element to retrieve
 * @return the id at the given position, or NO_ID if there was some mistake
 */
Id set_get_id(Set *set, int array_position);

/**
 * @brief It gets the array of ids stored in the Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @return a pointer to the array of ids stored in the Set
 */
Id* set_get_ids(Set *set);

#ifdef DEBUG
/**
 * @brief It prints the contents of a Set
 * @author  Jorge Garcia Garrido
 *
 * @param set a pointer to the Set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status set_print(Set* set);
#endif

#endif