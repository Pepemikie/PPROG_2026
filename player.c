/**
 * @brief Implementación de las funciones de Player
 * @file player.c
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

Player* player_create(Id id) {
  Player *new_player = NULL;

  if (id == NO_ID) {
    return NULL;
  }

  new_player = (Player *) malloc(sizeof (Player));
  if (new_player == NULL) {
    return NULL;
  }

  new_player->id = id;
  new_player->name[0] = '\0';
  new_player->location = NO_ID;
  new_player->object = NO_ID;
  new_player->health = 10;
  new_player->gdesc[0]= '\0';

  return new_player;
}

Status player_destroy(Player* player) {
  if (!player) {
    return ERROR;
  }

  free(player);
  return OK;
}

Id player_get_id(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->id;
}

Status player_set_name(Player* player, char* name) {
  if (!player || !name) {
    return ERROR;
  }

  if (!strcpy(player->name, name)) {
    return ERROR;
  }

  return OK;
}

const char* player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}

Status player_set_location(Player* player, Id location) {
  if (!player || location == NO_ID) {
    return ERROR;
  }
  player->location = location;
  return OK;
}

Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->location;
}

Status player_set_object(Player* player, Id object) {
  if (!player) {
    return ERROR;
  }
  player->object = object;
  return OK;
}

Id player_get_object(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->object;

}

int player_get_health(Player* p) {
  return (p) ? p->health : -1;
}

Status player_set_health(Player* p, int health) {
  if (!p || health < 0) return ERROR;
  p->health = health;
  return OK;
}


const char* player_get_gdesc(Player* p) {
  if (!p) {
    return NULL;
  }
  return p->gdesc;
}


Status player_set_gdesc(Player* p, char* gdesc) {
  if (!p || !gdesc) {
    return ERROR;
  }

  
  strncpy(p->gdesc, gdesc, P_GDESC_SIZE - 1);
  p->gdesc[P_GDESC_SIZE - 1] = '\0'; 

  return OK;
}


Status player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s; Location: %ld; Object: %ld)\n", 
          player->id, player->name, player->location, player->object);

  return OK;
}