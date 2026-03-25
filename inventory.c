/**
 *   It implements the inventory module
 *
 * @file inventory.c
 * @author Jose Miguel Romero Oubina
 * @version 0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "set.h"
#include "object.h"

struct _Inventory{
    Set *objs[MAX_SET];
    int max_objs;
};

/*   It creates a new Inventory, allocating memory and initializing its members */
Inventory *inventory_create(){
    Inventory *inv = NULL;

    inv = malloc (sizeof(Inventory));
    if(!inv) return NULL;

    inv->max_objs = 0;
    for(int i = 0; i < MAX_SET; i++){
        inv->objs[i] = NULL;
    }

    return inv;
}

/*   It destroys an Inventory, freeing the allocated memory */
Status inventory_destroy(Inventory *inventory){
    int i;

    if (!inventory) {
        return ERROR; /* error control */
    }

    for (i = 0; i < inventory->max_objs; i++) {
        set_destroy(inventory->objs[i]);
    }

    free(inventory);
    return OK;
}

/*   It adds an object to the inventory */
Status inventory_add_object(Inventory *inventory, Object *object){
    if (!inventory || !object) {
        return ERROR; /* error control */
    }
    
    /* ///////////////////////// para meter el nuevo objeto en el espacio vacio del array, NO CREO QUE SE DEBA UTILIZAR, PERO POR SI SIRVE DESPUES
    for(int i = 0; i < ((inventory->max_objs )- 1); i++) {
        if(inventory->objs[i] == NULL) {
            inventory->objs[i] = object;
            return OK;
        }
    }
    */

    if(set_find(inventory->objs, object_get_id(object)) != -1) {
        return OK; /* if the object already exists, returns OK without adding it */
    }

    inventory->objs[inventory->max_objs] = object;
    inventory->max_objs++;
    
    return OK;
}

/*   It removes an object from the inventory by its id */
Status inventory_del_object(Inventory *inventory, Id object_id){
    int i, index;
    if(inventory == NULL || object_id == NO_ID) {
        return ERROR; /* error control */
    }

    index = set_find(inventory->objs, object_id);
    if(index == -1) {
        return ERROR; /* object not found */
    }

    for(i = index; i < inventory->max_objs - 1; i++) {
        inventory->objs[i] = inventory->objs[i + 1];
    }
    inventory->objs[inventory->max_objs - 1] = NULL;
    inventory->max_objs--;
    return OK; /* object deleted */
}

/*   It checks if an object is in the inventory by its id */
Bool inventory_has_object(Inventory *inventory, Id object_id){
    int i;
    if(inventory == NULL || object_id == NO_ID) {
        return FALSE; /* error control */
    }

    for(i = 0; i < inventory->max_objs; i++) {
        if(inventory->objs[i] && object_get_id(inventory->objs[i]) == object_id) {
            return TRUE; /* object found */
        }
    }

    return FALSE; /* object not found */
}

/*   It gets the number of objects in the inventory */
int inventory_get_number_of_object(Inventory *inventory){
    if(inventory == NULL) {
        return -1; /* error control */
    }

    /*return set_get_n_ids(inventory->objs);*//* ////////////////////ESTA FUNCION O EL RETURN DE MAX_OBJECTS?*/

    return inventory->max_objs;
}

/*   It gets an object from the inventory by its index */
Object *inventory_get_object_by_index(Inventory *inventory, int index){
    if(inventory == NULL || index < 0 || index >= inventory->max_objs) {
        return NULL; /* error control */
    }

    return inventory->objs[index];
}

/*///////////////////// LO MISMO QUE INVENTORY HAS OBJECT, PERO DEVUELVE EL OBJETO EN LUGAR DE UN BOOLEANO. ¿ES NECESARIO?*/
/*   It gets an object from the inventory by its id */
Object *inventory_get_object_id(Inventory *inventory, Id object_id){
    int i;
    if(inventory == NULL || object_id == NO_ID) {
        return NULL; /* error control */
    }

    for(i = 0; i < inventory->max_objs; i++) {
        if(inventory->objs[i] && object_get_id(inventory->objs[i]) == object_id) {
            return inventory->objs[i]; /* object found */
        }
    }

    return NULL; /* object not found */
}

#ifdef DEBUG
/*   It prints the inventory */
Status inventory_print(Inventory *inventory){
    int i;
    if(inventory == NULL) {
        return ERROR; /* error control */
    }

    printf("Inventory:\n");
    for(i = 0; i < inventory->max_objs; i++) {
        if(inventory->objs[i]) {
            printf(" · %s \n     ID: %ld\n", object_get_name(inventory->objs[i]), object_get_id(inventory->objs[i]));
        }
    }

    return OK;
}
#endif