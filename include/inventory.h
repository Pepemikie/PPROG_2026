/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Jose Miguel Romero Oubina
 * @version 1.2
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include "types.h"
#include "set.h"

/** @brief It defines the Inventory struct */
typedef struct _Inventory Inventory;

/**
 * @brief It creates a new Inventory, allocating memory and initializing its members
 * @author Jose Miguel Romero Oubina
 * 
 * @param max_objects the maximum number of objects that the inventory can hold
 * @return a new pointer to an Inventory struct, initialized
 */
Inventory *inventory_create(int max_objects);

/**
 * @brief It destroys an Inventory, freeing the allocated memory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_destroy(Inventory *inventory);

/**
 * @brief It adds an object to the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to which the object will be added
 * @param object_id the identification number for the object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_add_object(Inventory *inventory, Id object_id);

/**
 * @brief It removes an object from the inventory by its id
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which the object will be removed
 * @param object_id the identification number for the object to be removed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_del_object(Inventory *inventory, Id object_id);

/**
 * @brief It checks if an object is in the inventory by its id
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to check
 * @param object_id the identification number for the object to check
 * @return TRUE, if the object is in the inventory or FALSE if it is not or if there was some mistake
 */
Bool inventory_has_object(Inventory *inventory, Id object_id);

/**
 * @brief It gets the objects in the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to check
 * @return a pointer to the Set containing the objects in the inventory or NULL if there was some mistake
 */
Set *inventory_get_objects(Inventory *inventory);

/**
 * @brief It sets the objects in the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to check
 * @param objects a pointer to the Set containing the objects to set
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_set_objects(Inventory *inventory, Set *objects);

/**
 * @brief Sets the maximum number of objects the inventory can hold
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to check
 * @param max_objs the maximum number of objects the inventory can hold
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_set_max_objs(Inventory *inventory, int max_objs);

/**
 * @brief Gets the maximum number of objects the inventory can hold
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to check
 * @return the maximum number of objects the inventory can hold or -1 if there was some mistake
 */
int inventory_get_max_objs(Inventory *inventory);

/**
 * @brief It gets the number of objects in the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the number of objects
 * @return the number of objects in the inventory or -1 if there was some mistake
 */
int inventory_get_number_of_objects(Inventory *inventory);

/**
 * @brief It checks if the inventory is full
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the number of objects
 * @return TRUE if the inventory is full, FALSE if it is not or if there was some mistake
 */
Bool inventory_is_full(Inventory *inventory);

/**
 * @brief It checks if the inventory is empty
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the number of objects
 * @return TRUE if the inventory is empty, FALSE if it is not or if there was some mistake
 */
Bool inventory_is_empty(Inventory *inventory);

#ifdef DEBUG
/**
 * @brief It prints the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to print
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory *inventory);
#endif
#endif