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

void game_actions_attack(Game *game);

void game_actions_chat(Game *game);

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

      case LEFT:
      game_actions_left(game);
      break;

      case RIGHT:
      game_actions_right(game);
      break;

      case ATTACK:
      game_actions_attack(game);
      break;

      case CHAT:
      game_actions_chat(game);
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
  Object *obj = NULL;

  if (!game) return;
  player_id = game_get_player_location(game);
  current_space = game_get_space(game, player_id);

  
  object_id = 1; 
  obj = game_get_object(game, object_id); 

  if (obj && space_has_object(current_space, object_id)) {
    player_set_object(game_get_player(game), object_id);
    space_del_object(current_space, object_id);
  }
}

void game_actions_drop(Game *game) {
  Id player_id = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;


  object_id = player_get_object(game_get_player(game));
  
  if (object_id != NO_ID) {
    player_id = game_get_player_location(game);
    current_space = game_get_space(game, player_id);

    if (current_space) {
      
      player_set_object(game_get_player(game), NO_ID);
      space_add_object(current_space, object_id);
    }
  }
}

void game_actions_left(Game *game) {
  Id current_id = NO_ID, left_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;

  current_space = game_get_space(game, current_id);
  left_id = space_get_west(current_space); /* Obtenemos el ID del Oeste */

  if (left_id != NO_ID) {
    game_set_player_location(game, left_id);
  }
}

void game_actions_right(Game *game) {
  Id current_id = NO_ID, right_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return;

  current_space = game_get_space(game, current_id);
  right_id = space_get_east(current_space); /* Obtenemos el ID del Este */

  if (right_id != NO_ID) {
    game_set_player_location(game, right_id);
  }
}
void game_actions_attack(Game *game) {
  Player *p = NULL;
  Character *c = NULL;
  Id loc = NO_ID;
  int r;

  if (!game) return;

  p = game_get_player(game);
  loc = game_get_player_location(game);
  /* Buscamos al personaje en la sala actual */
  c = game_get_character_in_space(game, loc);

  /* Solo atacamos si hay enemigo, no es amigo y tiene vida */
  if (c && !character_is_friendly(c) && character_get_health(c) > 0) {
    r = rand() % 10; /* Número entre 0 y 9 */
    
    if (r >= 0 && r <= 4) {
      /* Gana el adversario: pierde el jugador */
      player_set_health(p, player_get_health(p) - 1);
    } else {
      /* Gana el jugador: pierde el personaje */
      character_set_health(c, character_get_health(c) - 1);
    }
  }
}
void game_actions_chat(Game *game) {
  Character *c = NULL;
  Id loc = NO_ID;

  if (!game) return;

  loc = game_get_player_location(game);
  c = game_get_character_in_space(game, loc);

  /* Solo hablamos si es amigo */
  if (c && character_is_friendly(c)) {
    /* Guardamos el mensaje para que el motor gráfico lo vea */
    game_set_last_message(game, character_get_message(c));
  }
}