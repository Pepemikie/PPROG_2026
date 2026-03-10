/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Game {
  Player *player;
  Object *objects[MAX_OBJECTS];
  Space *spaces[MAX_SPACES];
  Character *characters[MAX_CHARACTERS];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
  Bool object_adquirido;
  char last_message[WORD_SIZE];
} Game;

/**
   Private functions
*/

Id game_get_space_id_at(Game *game, int position);
void game_object_set_bool(Game *game, Bool object_bool)
{
   if(!game)
   {
       return;
   }
   game->object_adquirido = object_bool;
}

/**
   Game interface implementation
*/



/**
 * @brief Crea una nueva instancia de Game y reserva memoria
 * @return Un puntero al nuevo Game o NULL si hay error
 */
Game* game_create() {
  Game *game = NULL;
  int i;

  /* Reservamos memoria para la estructura privada */
  game = (Game *) malloc(sizeof(Game));
  if (game == NULL) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  /* Inicializamos los campos (como vimos en F6) */
  game->n_spaces = 0;
  game->player = player_create(1); 
  game->last_cmd = command_create();
  game->finished = FALSE;
  strcpy(game->last_message, "");

  for (i = 0; i < MAX_OBJECTS; i++) game->objects[i] = NULL;
  for (i = 0; i < MAX_CHARACTERS; i++) game->characters[i] = NULL;

  return game;
}


Status game_create_from_file(Game *game, char *filename) {
  if (game_create(game) == ERROR) {
    return ERROR;
  }

  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  
if (game_load_objects(game, filename) == ERROR) {
  return ERROR;
}

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
 

  return OK;
}

Status game_destroy(Game *game) {
  int i = 0;

  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }

  player_destroy(game->player);
  command_destroy(game->last_cmd);

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) 
  object_destroy(game->objects[i]);
  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) 
  character_destroy(game->characters[i]);

  return OK;
}

Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }

  return NULL;
}

Player *game_get_player(Game *game) {
  if (!game) return NULL;
  return game->player;
}

Id game_get_player_location(Game *game) 
 { 
   return player_get_location(game->player);
 }
 
 /* Establece la ubicación del jugador en el juego*/
 Status game_set_player_location(Game *game, Id id) 
 {
   if (id == NO_ID) {
     return ERROR;
   }
 
   return player_set_location(game->player, id);
 
   
 }


Id game_get_object_location(Game *game) {
  int i;
  Id obj_id = NO_ID;

  if (!game) {
    return NO_ID;
  }

 
  obj_id = object_get_id(game->objects[0]);

  /* 2. Recorremos el array de espacios */
  for (i = 0; i < game->n_spaces; i++) {
  
    if (space_has_object(game->spaces[i], obj_id) == TRUE) {
 
      return space_get_id(game->spaces[i]);
    }
  }

  return NO_ID;
}


 
Status game_add_object(Game *game, Object *object) {
  int i = 0;

  if (!game || !object) {
    return ERROR;
  }


  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++);

  if (i >= MAX_OBJECTS) {
    return ERROR; 
  }

  game->objects[i] = object;

  return OK;
}


Object* game_get_object(Game* game, Id id) {
  int i;
  if (!game || id == NO_ID) return NULL;


  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    if (object_get_id(game->objects[i]) == id) {
      return game->objects[i];
    }
  }
  return NULL;
}


Status game_set_object_location(Game *game, Id space_id, Id object_id) {
  Space *s = NULL;
  Object *obj = NULL;

  if (!game || space_id == NO_ID || object_id == NO_ID) return ERROR;

  s = game_get_space(game, space_id);
  obj = game_get_object(game, object_id); /* Usamos la función del paso anterior */

  if (!s || !obj) return ERROR;

  return space_add_object(s, object_get_id(obj));
}

Command* game_get_last_command(Game *game) { return game->last_cmd; }

Status game_set_last_command(Game *game, Command *command) {
  game->last_cmd = command;

  return OK;
}

Bool game_get_finished(Game *game) { return game->finished; }

Status game_set_finished(Game *game, Bool finished) {
  game->finished = finished;

  return OK;
}

void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %ld\n", game_get_object_location(game));
  printf("=> Player location: %ld\n", game_get_player_location(game));
}

/**
   Implementation of private functions
*/



Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }

  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}

/* Busca un personaje en una localización específica */
Character* game_get_character_in_space(Game* game, Id space_id) {
  int i;
  if (!game || space_id == NO_ID) return NULL;

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) {
    if (character_get_location(game->characters[i]) == space_id) {
      return game->characters[i];
    }
  }
  return NULL;
}

/* Guarda el mensaje del personaje para mostrarlo en pantalla */
Status game_set_last_message(Game* game, const char* message) {
  if (!game || !message) return ERROR;
  strncpy(game->last_message, message, WORD_SIZE - 1);
  return OK;
}