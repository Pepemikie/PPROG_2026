/**
 * @brief It implements the player module
 *
 * @file player.c
 * @author Cesar Soto Vega & Jose Miguel Romero Oubina
 * @version 0
 * @date 08-02-2026
 * @copyright GNU Public License
 */

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Player
 *
 * This struct stores all the information of a player.
 */
struct _Player {
  Id id;                    /*!< Id number of the player, it must be unique */
  char name[WORD_SIZE + 1]; /*!< Name of the player */
  Id location;/*nuevas funciones para tener una localizacion (como el name)*/
  Id object_id;/*mismo que location*/
};

/*Allocates memory for a new player, sets its ID, and initializes name, location, and carried object as empty.
 */
Player* player_create(Id id) {
  Player* newPlayer = NULL;

/* Checks if the given ID is valid */
  if (id == NO_ID) return NULL;

  /* Allocates memory for the player */
  newPlayer = (Player*)calloc(1, sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

/* Initializes the player ID, name, location, and carried object */
  newPlayer->id = id;
  newPlayer->name[0] = '\0';
  newPlayer->location = NO_ID;
  newPlayer->object_id = NO_ID;
  return newPlayer;
}

/*Frees the memory used by the player.*/
Status player_destroy(Player* player) {
  /* Checks if player exists */
  if (!player) {
    return ERROR;
  }

  /* Frees memory and sets pointer to NULL */
  free(player);
  player = NULL;
  return OK;
}

/*Returns the ID of the player.*/
Id player_get_id(Player* player) {
  /* Returns NO_ID if the player doesn’t exist */
  if (!player) {
    return NO_ID;
  }
  /* Returns the player’s ID */
  return player->id;
}

/*Sets the player’s name.*/
Status player_set_name(Player* player, char* name) {
  /* Checks for NULL player or name */
  if (!player || !name) {
    return ERROR;
  }

  /* Ensures name length does not exceed WORD_SIZE */
  if (strlen(name) >= WORD_SIZE) {
    return ERROR;
  }

  /* Copies the name into the player structure */
  if (!strcpy(player->name, name)) {
    return ERROR;
  }
  return OK;
}

/*Returns the player’s name*/
const char* player_get_name(Player* player) {
  /* Returns NULL if player doesn’t exist */
  if (!player) {
    return NULL;
  }
  /* Returns the player’s name */
  return player->name;
}

/*Assigns an object ID to the player.*/
Status player_set_object_id(Player* player, Id object_id) {
  /* Checks if player exists and object ID is valid */
  if (!player) {
    return ERROR;
  }
  /* Assigns the object ID to the player */
  player->object_id = object_id;
  return OK;
}

/*Returns the object ID the player is carrying*/
Id player_get_object_id(Player* player) {
  /* Returns NO_ID if player doesn’t exist */
  if (!player) {
    return NO_ID;
  }
  /* Returns the object ID the player is carrying */
  return player->object_id;
}

/*Sets the player’s current location.*/
Status player_set_location(Player* player, Id location_id) {
  /* Checks if player exists and location ID is valid */
  if (!player || location_id == NO_ID) {
    return ERROR;
  }
  /* Sets the player’s current location */
  player->location = location_id;
  return OK;
}

/*Returns the player’s current location.*/
Id player_get_location(Player* player) {
  /* Returns NO_ID if player doesn’t exist */
  if (!player) {
    return NO_ID;
  }
  /* Returns the player’s current location */
  return player->location;
}

/*Prints the player’s ID, name, location, and carried object.*/
Status player_print(Player* player) {
/* Checks if player exists */
  if (!player) {
    return ERROR;
  }

/* Prints player ID and name */
  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->id, player->name);

  /* Prints player location if assigned */
  if (player->location != NO_ID) {
    fprintf(stdout, "---> Location: %ld.\n", player->location);
  } else {
    fprintf(stdout, "---> No location.\n");
  }

  /* Prints object carried by player if any */
  if (player->object_id != NO_ID) {
    fprintf(stdout, "---> Object carried: %ld.\n", player->object_id);
  } else {
    fprintf(stdout, "---> No object carried.\n");
  }

  return OK;
}

/*Removes the object from the player if it matches the given object ID.*/
Status player_drop_object(Player* player, Id object_id) {
  /* Checks if player exists and object ID is valid */
  if (!player) {
    return ERROR;
  }
  if(object_id == NO_ID)
    return ERROR;
    
/* Drops the object if player is carrying it */
  if(player->object_id == object_id) {
    player->object_id = NO_ID;
  }

  return OK;
}
