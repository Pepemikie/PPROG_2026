/**
 *   It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Jose Miguel Romero Oubina
 * @version 2
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
   Private functions
*/

/*Does nothing when the command is not recognized.*/
void game_actions_unknown(Game *game);

/*is meant to handle exiting the game*/
void game_actions_exit(Game *game);

/*Moves the player to the south space if there is one*/
Status game_actions_next(Game *game);

/*Moves the player to the north space if there is one.*/
Status game_actions_back(Game *game);

/*Moves the player to the east space if there is one.*/
Status game_actions_right(Game *game);

/*Moves the player to the west space if there is one.*/
Status game_actions_left(Game *game);

/*Makes the player pick up the object in the current space.*/
Status game_actions_take(Game *game);

/*Makes the player drop their carried object into the current space.*/
Status game_actions_drop(Game *game);

/*Makes the player attack if the character is not friendly*/
Status game_actions_attack(Game *game);

/*Makes the player interact with a character by chat*/
Status game_actions_chat(Game *game);

/**
   Game actions implementation
*/

/*   It updates the game state according to the command introduced by the user */
Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command); /* stores the last command */

  cmd = command_get_code(command); /* retrieves the command code */

  switch (cmd) {
    case UNKNOWN:/*calls unknown action*/
      game_set_last_status(game, OK);
      break;

    case EXIT:/*calls exit action*/
      game_set_last_status(game, OK);
      break;
    
    case NEXT:/*calls next action*/
      game_set_last_status(game, game_actions_next(game));
      break;

    case BACK:/*calls back action*/
      game_set_last_status(game, game_actions_back(game));
      break;
    
     case TAKE:/*calls take action*/
      game_set_last_status(game, game_actions_take(game));
      break;

     case DROP:/*calls drop action*/
      game_set_last_status(game, game_actions_drop(game));
      break;

      case LEFT:/*calls left action*/
      game_set_last_status(game, game_actions_left(game));
      break;

      case RIGHT:/*calls right action*/
      game_set_last_status(game, game_actions_right(game));
      break;

      case ATTACK:/*calls attack action*/
      game_set_last_status(game, game_actions_attack(game));
      break;

      case CHAT:/*calls chat action*/
      game_set_last_status(game, game_actions_chat(game));
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

/*   Moves the player to the south space if there is one */
Status game_actions_next(Game *game) {
  Id current_id = NO_ID;/*intitializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);;/*space gets the player's location so it can be updated*/
  if (space_id == NO_ID) {/*error control*/
    return ERROR;
  }

  current_id = space_get_south(game_get_space(game, space_id));/*current_id gets the south space id to move forwards*/
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);/*if it cannot happen, set the player's location to the current space*/
    return OK;
  }

  return ERROR;
}

/*   Moves the player to the north space if there is one */
Status game_actions_back(Game *game) {
  Id current_id = NO_ID;/*initializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);/*space gets the player's location so it can be updated*/

  if (NO_ID == space_id) {/*error control*/
    return ERROR;
  }

  current_id = space_get_north(game_get_space(game, space_id));/*current_id gets the north space id to move backwards*/
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);/*if it cannot happen, set the player's location to the current space*/
    return OK;
  }

  return ERROR;/*return nothing*/
}
/*///////////////////////////////////////////////////////////////////////*/
/*   Makes the player pick up the named object in the current space */
Status game_actions_take(Game *game) {
  /*inicialitating*/
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;
  Object *obj = NULL;
  int num_objects = 0;
  int i=0;
  Id *objects = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;/*error control*/

  /*Get player location*/
  player_location = game_get_player_location(game);

  if(player_location == NO_ID)
    return ERROR;

  current_space = game_get_space(game, player_location);
  if(!current_space)
    return ERROR;

  
  last_cmd = game_get_last_command(game);
  if(!last_cmd)
    return ERROR;

  arg = command_get_arg(last_cmd); /*esta es la funcion que nos dio el profesor*/
  if(!arg || arg[0] == '\0'){
    return ERROR;
  }

  if (inventory_is_full(player_get_backpack(game_get_player(game)))) return ERROR;

  num_objects = space_get_number_of_objects(current_space);/*///AÑADIDO NUEVO////////////*/

  if (num_objects > 0) {
    objects = space_get_objects(current_space);/*//////////AÑADIDO NUEVO/////////*/

    if (objects) {
      for (i = 0; i < num_objects;  i++) { /* iterates through objects in the space */
        obj = game_get_object(game, objects[i]);

        if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) { /* checks name match */
          object_id = objects[i];
          break;
        }
      }

      if (object_id != NO_ID) { /* object found: assign to player and remove from space */
        /* Add the object ID to the inventory, remove it from the space */
        if (player_add_object(game_get_player(game), object_id) == ERROR) return ERROR;
        space_del_object(current_space, object_id);
        return OK;
      }
    }
  }

  return ERROR;
}
/*///////////////////////////////////////////////////////////////////////////////*/
/*   Makes the player drop the named object into the current space */
Status game_actions_drop(Game *game) {
  /*Initialitating*/
  Id player_location = NO_ID;
  Id carried_object_id = NO_ID;
  Space *current_space = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

/*mew initializing*/
  Set *inv_set = NULL;
  Object *obj = NULL;
  Id *ids = NULL;
  int n = 0;
  int i = 0;

  if (!game) return ERROR;/*error control*/
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  current_space = game_get_space(game, player_location);
  if (!current_space) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  /* Get the player's inventory */
  inv_set = inventory_get_objects(player_get_backpack(game_get_player(game)));/*/////////////////////////////////////////*/
  if (!inv_set) return ERROR;

  /* Search the inventory for an object whose name matches the argument */
  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);   /* assumes set exposes its ID array */
  if (!ids || n <= 0) return ERROR;

  for (i = 0; i < n; i++) {
    obj = game_get_object(game, ids[i]);
    if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
      carried_object_id = ids[i];
      break;
    }
  }

  if (carried_object_id == NO_ID) return ERROR; /* object not found in inventory */

  /* Eliminamos del player y añadimos al espacio */
  if (player_del_object(game_get_player(game), carried_object_id) == ERROR) return ERROR;

  space_add_object(current_space, carried_object_id);
  game_set_object_location(game, player_location, carried_object_id);

  return OK;
}

/*   Moves the player to the west space if there is one */
Status game_actions_left(Game *game) {
  Id current_id = NO_ID;
  Id left_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return ERROR;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return ERROR;

  current_space = game_get_space(game, current_id);
  if(current_space != NULL)
    left_id = space_get_west(current_space); /* Obtenemos el ID del Oeste */

  if (left_id != NO_ID) {
    game_set_player_location(game, left_id);
    return OK;
  }

  return ERROR;
}

/*   Moves the player to the east space if there is one */
Status game_actions_right(Game *game) {
  Id current_id = NO_ID;
  Id  right_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return ERROR;

  current_id = game_get_player_location(game);
  if (current_id == NO_ID) return ERROR;

  current_space = game_get_space(game, current_id);
  if(current_space != NULL)
    right_id = space_get_east(current_space); /* Obtenemos el ID del Este */

  if (right_id != NO_ID) {
    game_set_player_location(game, right_id);
    return OK;
  }
  return ERROR;
}

/*   Makes the player attack the enemy character in the current space */
Status game_actions_attack(Game *game) {
  Player *p = NULL;
  Character *c = NULL;
  Id loc = NO_ID;
  int r;

  if (!game) return ERROR;

  p = game_get_player(game);
  loc = game_get_player_location(game);
  /* Buscamos al personaje en la sala actual */
  c = game_get_character_in_space(game, loc);

  if(!c || character_is_friendly(c)) return ERROR;/*error control: no se puede atacar a un personaje amigo*/

  /* Solo atacamos si hay enemigo, no es amigo y tiene vida */
  if (c && !character_is_friendly(c) && character_get_health(c) > 0) {
    r = rand() % 10; /* Número entre 0 y 9 */
    
  if (r >= 0 && r <= 4) {
  /* Gana el adversario: pierde el jugador */
    player_set_health(p, player_get_health(p) - 1);
  
  /* Si el jugador llega a 0, termina el juego */
    if (player_get_health(p) <= 0) {
      game_set_finished(game, TRUE); /* marks game as finished */
    }
  } else {
  /* Gana el jugador: pierde el personaje */
    character_set_health(c, character_get_health(c) - 1);
    }
  }
  return OK;
}

/*   Makes the player interact with a friendly character by chat */
Status game_actions_chat(Game *game) {
  Character *c = NULL;
  Id loc = NO_ID;

  if (!game) return ERROR;

  loc = game_get_player_location(game);
  c = game_get_character_in_space(game, loc);

  if(!c || !character_is_friendly(c)) return ERROR;

  /* Solo hablamos si es amigo */
  if (c && character_is_friendly(c)) {
    /* Guardamos el mensaje para que el motor gráfico lo vea */
    game_set_last_message(game, character_get_message(c)); /* stores character message in game */
  }
 
  return OK;
}