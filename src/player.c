/**
 *   It implements the player module
 *
 * @file player.c
 * @author Jose Miguel Romero Oubina
 * @version 2
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

/** @brief Structure for the Player type */
struct _Player {
  Id id; /**< The unique identifier of the player */
  char name[WORD_SIZE]; /**< The name of the player */
  Id location; /**< The id of the space where the player is located */
  Inventory *backpack;  /**< The inventory of the player, containing the objects they carry */
  int health; /**< The health points of the player */
  char gdesc[P_GDESC_SIZE]; /**< Graphic description: a string of 4 characters plus null terminator */
};

/*   It creates a new Player, allocating memory and initializing its members */
Player* player_create(Id id) {
  Player *new_player = NULL;
  if (id == NO_ID) {
    return NULL; /* error control */
  }
  new_player = (Player *) malloc(sizeof(Player)); /* allocates memory for the player */
  if (new_player == NULL) {
    return NULL;
  }
/* initializes all fields by default */
  new_player->id = id;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->backpack = inventory_create(MAX_BACKPACK_SIZE);
  new_player->health = 10;
  new_player->gdesc[0]= '\0';
  return new_player;
}

/*   It destroys a Player, freeing the allocated memory */
Status player_destroy(Player* player) {
  if (!player) {
    return ERROR; /* error control */
  }
  if (player->backpack) {
    inventory_destroy(player->backpack);
  }
  free(player);
  return OK;
}

/*   It gets the id of a Player */
Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

/*   It sets the name of a Player */
Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }
  if (!strncpy(player->name, name, WORD_SIZE - 1)) { /* copies name safely */
    return ERROR;
  }
  player->name[WORD_SIZE - 1] = '\0';
  return OK;
}

/*   It gets the name of a Player */
const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

/*   It sets the location of a Player */
Status player_set_location(Player* player, Id location) {
  if (!player) {
    return ERROR;
  }
  player->location = location; /* assigns the location id to the player */
  return OK;
}

/*   It gets the location of a Player */
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

/*   It adds an object to the player's inventory */
Status player_add_object(Player* player, Id object) {
  if (!player || object == NO_ID || !player->backpack) {
    return ERROR;/*error control*/
  }

  /*al tener un solo elmento, antes solo asigamos. ahora añadimos un espcio y metemos el objeto*/
  return inventory_add_object(player->backpack, object);
}

/*   It removes an object from the player's inventory */
Status player_del_object(Player* player, Id object) {
  if (!player || object == NO_ID || !player->backpack) {
    return ERROR;/*error control*/
  }
  return inventory_del_object(player->backpack, object);
}

/*   It checks if a Player has a specific object in their inventory */
Bool player_has_object(Player* player, Id object) {
  if (!player || object == NO_ID || !player->backpack) {
    return FALSE;/*error control*/
  }
  return inventory_has_object(player->backpack, object);
}

/*   It gets the id of an object in the player's inventory by its index */
Id player_get_object(Player* player, int index) {
  if (!player || index < 0 || !player->backpack) {
    return NO_ID;/*error control*/
  }
  if (index >= inventory_get_max_objs(player->backpack)) {
    return NO_ID;
  }
  return set_get_id(inventory_get_objects(player->backpack), index);
}

/*   It gets the player's inventory */
Inventory* player_get_backpack(Player* player) {
  if (!player) {/*error control*/
    return NULL;
  }
  return player->backpack;
}

/*   It gets the health of a Player */
int player_get_health(Player* player) {
  if(!player) {
    return -1;
  }
  return player->health;
}

/*   It sets the health of a Player */
Status player_set_health(Player* player, int health) {
  if (!player || health < 0) return ERROR;
  player->health = health; /* assigns health points to the player */
  return OK;
}

/*   It modifies the health of a Player by adding the given amount */
Status player_modify_health(Player* player, int health) {
  if (!player) return ERROR;
  return player_set_health(player, player_get_health(player) + health);
}

/*   It gets the graphic description of a Player */
const char* player_get_gdesc(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->gdesc;
}

/*   It sets the graphic description of a Player */
Status player_set_gdesc(Player* player, char* gdesc) {
  if (!player || !gdesc) {
    return ERROR;
  }
  strncpy(player->gdesc, gdesc, P_GDESC_SIZE - 1); /* copies description safely */
  player->gdesc[P_GDESC_SIZE - 1] = '\0'; 
  return OK;
}

Status player_set_max_objs(Player* player, int max_objs) {
  if (!player || max_objs < 0) {
    return ERROR;
  }
  
  if (player->backpack) {
    inventory_destroy(player->backpack); /* destroy the old backpack */
  }
  
  player->backpack = inventory_create(max_objs); /* create a new backpack with the maximum objects */
  if (!player->backpack) {
    return ERROR;
  }

  return OK;
}

#ifdef DEBUG
Status player_print(Player* player) {
  if (!player) {
    return ERROR;
  }
  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld; Objects: %d; Health: %d; Desc: %s)\n", 
  player->id, player->name, player->location, inventory_get_number_of_objects(player->backpack), player->health, player->gdesc); /* prints all player fields */
  return OK;
}
#endif