/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

void game_actions_unknown(Game *game);

void game_actions_exit(Game *game);

void game_actions_next(Game *game);

void game_actions_back(Game *game);

void game_actions_right(Game *game);

void game_actions_left(Game *game);

void game_actions_take(Game *game);

void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);
      break;

    case EXIT:
      game_actions_exit(game);
      break;

    case NEXT:
      game_actions_next(game);
      break;

    case BACK:
      game_actions_back(game);
      break;
    
     case TAKE:
      game_actions_take(game);
      break;

     case DROP:
      game_actions_drop(game);
      break;

    default:
      break;
  }

  return OK;
}

/**
   Calls implementation for each action
*/

void game_actions_unknown(Game *game) {}

void game_actions_exit(Game *game) {}

void game_actions_next(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {
    game_set_player_location(game, current_id);
  }

  return;
}

void game_actions_take(Game *game) {
  Id player_id = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;

  object_id = game_get_object_location(game);
  player_id = game_get_player_location(game);

  
  if ((NO_ID != object_id) && (object_id == player_id)) {
   
    player_set_object(game_get_player(game), object_get_id(game_get_object(game)));


    current_space = game_get_space(game, player_id);
    if (current_space) {
      
      space_del_object(current_space, object_get_id(game_get_object(game)));
    }
  }

  return;
}

void game_actions_drop(Game *game) {
  Id player_object = NO_ID;
  Id player_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;

  player_object = player_get_object(game_get_player(game));
  player_id = game_get_player_location(game);

  /* Si el jugador tiene un objeto, lo suelta en el espacio actual */
  if (player_object != NO_ID) {
    /* Borrar el objeto del inventario del jugador */
    player_set_object(game_get_player(game), NO_ID);
    
    /* Agregar el objeto al espacio actual */
    current_space = game_get_space(game, player_id);
    if (current_space) {
      space_add_object(current_space, player_object);
    }
  }

  return;
}