/**
 *   It implements the inventory module
 *
 * @file inventory.c
 * @author Jose Miguel Romero Oubina
 * @version 1.2
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "set.h"


struct _Inventory{
    Set *objs;
    int max_objs;
};

/*   It creates a new Inventory, allocating memory and initializing its members */
Inventory *inventory_create(int max_objects){
    Inventory *inv = NULL;

    if(max_objects <= 0) return NULL; /* error control */

    inv = malloc (sizeof(Inventory));
    if(!inv) return NULL;

    inv->objs = set_create();
    if(!inv->objs) {
        free(inv);
        return NULL;
    }

    inv->max_objs = max_objects;

    return inv;
}

/*   It destroys an Inventory, freeing the allocated memory */
Status inventory_destroy(Inventory *inventory){
    if (!inventory) {
        return ERROR; /* error control */
    }
    
    set_destroy(inventory->objs);

    free(inventory);
    return OK;
}

/*   It adds an object to the inventory */
Status inventory_add_object(Inventory *inventory, Id object_id){
    if (!inventory || object_id == NO_ID) return ERROR; /* error control */
    
    if (inventory_is_full(inventory)) return ERROR;

    return set_add(inventory->objs, object_id);
}

/*   It removes an object from the inventory by its id */
Status inventory_del_object(Inventory *inventory, Id object_id){
    if(inventory == NULL || object_id == NO_ID) {
        return ERROR; /* error control */
    }

    return set_del(inventory->objs, object_id);
}

/*   It checks if an object is in the inventory by its id */
Bool inventory_has_object(Inventory *inventory, Id object_id){
    if(inventory == NULL || object_id == NO_ID) return FALSE; /* error control */

    if(set_find(inventory->objs, object_id) != -1)
        return TRUE; /*object found*/

    return FALSE; /* object not found */
}

/*   It gets the objects in the inventory */
Set *inventory_get_objects(Inventory *inventory){
    if(inventory == NULL) return NULL; /* error control */
    
    return inventory->objs;
}

/* Sets the objects in the inventory */
Status inventory_set_objects(Inventory *inventory, Set *objects) {
  if (inventory == NULL || objects == NULL) {
    return ERROR;
  }

  set_destroy(inventory->objs);
  inventory->objs = objects;

  return OK;
}

/* Sets the maximum number of objects the inventory can hold */
Status inventory_set_max_objs(Inventory *inventory, int max_objs) {
    if (!inventory || max_objs <= 0) return ERROR;

    /* Cannot shrink below the current number of objects already stored */
    if (max_objs < set_get_n_ids(inventory->objs)) return ERROR;

    inventory->max_objs = max_objs;
    return OK;
}

/* Gets the maximum capacity of the inventory */
int inventory_get_max_objs(Inventory *inventory) {
    if (!inventory) return -1;
    return inventory->max_objs;
}

/*   It gets the number of objects in the inventory */
int inventory_get_number_of_objects(Inventory *inventory){
    if(inventory == NULL) {
        return -1; /* error control */
    }

    /*devuelve el numero de elementos, no tiene porq ser el tamaño completo*/
    return set_get_n_ids(inventory->objs);
}

/*   It checks if the inventory is full */
Bool inventory_is_full(Inventory *inventory) {
    if (!inventory) return FALSE; /* error control */
    if (set_get_n_ids(inventory->objs) >= inventory->max_objs) {
        return TRUE;
    }
    return FALSE;
}

/*   It checks if the inventory is empty */
Bool inventory_is_empty(Inventory *inventory) {
    if (!inventory) return TRUE; /* error control */
    if (set_get_n_ids(inventory->objs) == 0) {
        return TRUE;
    }
    return FALSE;
}

#ifdef DEBUG
/*   It prints the inventory */
Status inventory_print(Inventory *inventory){
    if(inventory == NULL) {
        return ERROR; /* error control */
    }

    fprintf(stdout, "Inventory: (max_objs: %d; n_objs: %d)\n", inventory->max_objs, set_get_n_ids(inventory->objs)); /* prints max capacity and current number of objects */

    for (i = 0; i < set_get_n_ids(inventory->objs); i++) {
        fprintf(stdout, "%ld ", set_get_id(inventory->objs, i)); 
    }
    
    fprintf(stdout, "\n");
    return OK;
}
#endif
