/**
 *   It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Jose Miguel Romero Oubina
 * @version 3
 * @date 01-04-2026
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

/*Makes the player pick up the object in the current space.*/
Status game_actions_take(Game *game);

/*Makes the player drop their carried object into the current space.*/
Status game_actions_drop(Game *game);

/*Makes the player attack if the character is not friendly*/
Status game_actions_attack(Game *game);

/*Makes the player interact with a character by chat*/
Status game_actions_chat(Game *game);

/*Moves the player to the next space if there is one and it's open*/
Status game_actions_move(Game *game);

/*Inspects an object*/
Status game_actions_inspect(Game *game);

/**
   Game actions implementation
*/

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_set_last_status(game, OK);
      break;

    case EXIT:
      game_set_last_status(game, OK);
      break;
    
    case TAKE:
      game_set_last_status(game, game_actions_take(game));
      break;

    case DROP:
      game_set_last_status(game, game_actions_drop(game));
      break;

    case ATTACK:
      game_set_last_status(game, game_actions_attack(game));
      break;

    case CHAT:
      game_set_last_status(game, game_actions_chat(game));
      break;

    case MOVE:
      game_set_last_status(game, game_actions_move(game));
      break;

    case INSPECT:
      game_set_last_status(game, game_actions_inspect(game));
      break;

    default:
      break;
  }

  return OK;
}

/*///////////////////////////////////////////////////////////////////////*/
/*   Makes the player pick up the named object in the current space */
Status game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;
  Object *obj = NULL;
  int num_objects = 0;
  int i=0;
  Id *objects = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;

  player_location = game_get_player_location(game);
  if(player_location == NO_ID) return ERROR;

  current_space = game_get_space(game, player_location);
  if(!current_space) return ERROR;

  last_cmd = game_get_last_command(game);
  if(!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if(!arg || arg[0] == '\0') return ERROR;

  if (inventory_is_full(player_get_backpack(game_get_player(game)))) return ERROR;

  num_objects = space_get_number_of_objects(current_space);

  if (num_objects > 0) {
    objects = space_get_objects(current_space);

    if (objects) {
      for (i = 0; i < num_objects; i++) {
        obj = game_get_object(game, objects[i]);

        if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
          object_id = objects[i];
          break;
        }
      }

      if (object_id != NO_ID) {
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
  Id player_location = NO_ID;
  Id carried_object_id = NO_ID;
  Space *current_space = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  Set *inv_set = NULL;
  Object *obj = NULL;
  Id *ids = NULL;
  int n = 0;
  int i = 0;

  if (!game) return ERROR;
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  current_space = game_get_space(game, player_location);
  if (!current_space) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  inv_set = inventory_get_objects(player_get_backpack(game_get_player(game)));
  if (!inv_set) return ERROR;

  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);
  if (!ids || n <= 0) return ERROR;

  for (i = 0; i < n; i++) {
    obj = game_get_object(game, ids[i]);
    if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
      carried_object_id = ids[i];
      break;
    }
  }

  if (carried_object_id == NO_ID) return ERROR;

  if (player_del_object(game_get_player(game), carried_object_id) == ERROR) return ERROR;

  space_add_object(current_space, carried_object_id);
  game_set_object_location(game, player_location, carried_object_id);

  return OK;
}

/*///////////////////////////////////////////////////////////////////////////////*/
/*Moves the player to the space in the direction specified by the command argument if there is one */
Status game_actions_move(Game *game) {
  Id current_space = NO_ID;
  Id next_space = NO_ID;
  Direction dir = UNKNOWN_DIR;
  char *arg = NULL;
  Command *cmd = NULL;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg) return ERROR;

  if (strcasecmp(arg, "north") == 0 || strcasecmp(arg, "n") == 0)
    dir = N;
  else if (strcasecmp(arg, "south") == 0 || strcasecmp(arg, "s") == 0)
    dir = S;
  else if (strcasecmp(arg, "east") == 0 || strcasecmp(arg, "e") == 0)
    dir = E;
  else if (strcasecmp(arg, "west") == 0 || strcasecmp(arg, "w") == 0)
    dir = W;
  else
    return ERROR;

  current_space = game_get_player_location(game);

  if (!game_connection_is_open(game, current_space, dir))
    return ERROR;

  next_space = game_get_connection(game, current_space, dir);

  if (next_space == NO_ID)
    return ERROR;

  return game_set_player_location(game, next_space);
}

/*///////////////////////////////////////////////////////////////////////////////*/
/* Inspects an object in the current space*/
Status game_actions_inspect(Game *game) {
  Command *cmd = NULL;
  char *arg = NULL;
  Id player_loc = NO_ID;
  Space *space = NULL;
  Id *objs = NULL;
  int i = 0;
  Object *obj = NULL;

  Set *inv = NULL;
  Id *ids = NULL;
  int n_ids = 0;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg) return ERROR;

  player_loc = game_get_player_location(game);
  space = game_get_space(game, player_loc);
  if (!space) return ERROR;

  int n = space_get_number_of_objects(space);
  objs = space_get_objects(space);

  for (i = 0; i < n; i++) {
    obj = game_get_object(game, objs[i]);
    if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
      printf("You see %s\n", object_get_name(obj));
      return OK;
    }
  }

  inv = inventory_get_objects(player_get_backpack(game_get_player(game)));
  if (inv) {
    ids = set_get_ids(inv);
    n_ids = set_get_n_ids(inv);

    for (i = 0; i < n_ids; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
        printf("You see %s\n", object_get_name(obj));
        return OK;
      }
    }
  }

  return ERROR;
}

/*///////////////////////////////////////////////////////////////////////////////*/
/*   Makes the player attack the enemy character in the current space */
Status game_actions_attack(Game *game) {
  return OK;
}

/*///////////////////////////////////////////////////////////////////////////////*/
/*   Makes the player interact with a friendly character by chat */
Status game_actions_chat(Game *game) {
  return OK;
}