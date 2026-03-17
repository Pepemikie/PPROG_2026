/**
 *   It implements the player module
 *
 * @file player.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"

/* Estructura de datos interna del jugador */
struct _Player {
  Id id;
  char name[WORD_SIZE];
  Id location;
  Id object; 
  int health;
  char gdesc[P_GDESC_SIZE];
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
  new_player->object = NO_ID;
  new_player->health = 10;
  new_player->gdesc[0]= '\0';
  return new_player;
}

/*   It destroys a Player, freeing the allocated memory */
Status player_destroy(Player* player) {
  if (!player) {
    return ERROR; /* error control */
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

/*   It sets the object carried by a Player */
Status player_set_object(Player* player, Id object) {
  if (!player) {
    return ERROR;
  }
  player->object = object; /* assigns the object id to the player */
  return OK;
}

/*   It gets the object carried by a Player */
Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;
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

#ifdef DEBUG
/*   It prints the data of a Player */
Status player_print(Player* player) {
  if (!player) {
    return ERROR;
  }
  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld; Object: %ld; Health: %d; Desc: %s)\n", 
  player->id, player->name, player->location, player->object, player->health, player->gdesc); /* prints all player fields */
  return OK;
}
#endif