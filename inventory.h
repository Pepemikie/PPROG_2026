/**
 * @brief It defines the inventory interface
 *
 * @file inventory.h
 * @author Jose Miguel Romero Oubina
 * @version 0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include "types.h"
#include "object.h"

typedef struct _Inventory Inventory;

/**
 * @brief It creates a new Inventory, allocating memory and initializing its members
 * @author Jose Miguel Romero Oubina
 *
 * @return a new pointer to an Inventory struct, initialized
 */
Inventory *inventory_create();

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
 * @param object a pointer to the Object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_add_object(Inventory *inventory, Object *object);

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
 * @brief It gets the number of objects in the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the number of objects
 * @return the number of objects in the inventory or -1 if there was some mistake
 */
int inventory_get_number_of_object(Inventory *inventory);

/**
 * @brief It gets an object from the inventory by its index
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the object
 * @param index the index of the object to get
 * @return a pointer to the Object at the specified index or NULL if there was some mistake
 */
Object *inventory_get_object_by_index(Inventory *inventory, int index);

/**
 * @brief It gets an object from the inventory by its id
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory from which to get the object
 * @param object_id the identification number for the object to get
 * @return a pointer to the Object with the specified id or NULL if there was some mistake
 */
Object *inventory_get_object_id(Inventory *inventory, Id object_id);

/**
 * @brief It prints the inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param inventory a pointer to the Inventory to print
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status inventory_print(Inventory *inventory);

#endif