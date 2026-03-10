/**
 * @brief It implements the game update through user actions
 *
 * @file game.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 03-03-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space.h"
#include "player.h"
#include "object.h"

/**
   Private functions
*/

/*Does nothing when the command is not recognized.*/
void game_actions_unknown(Game *game);

/*is meant to handle exiting the game*/
void game_actions_exit(Game *game);

/*Moves the player to the south space if there is one*/
void game_actions_next(Game *game);

/*Moves the player to the north space if there is one.*/
void game_actions_back(Game *game);

/*Moves the player to the east space if there is one.*/
void game_actions_right(Game *game);

/*Moves the player to the west space if there is one.*/
void game_actions_left(Game *game);

/*Makes the player pick up the object in the current space.*/
void game_actions_take(Game *game);

/*Makes the player drop their carried object into the current space.*/
void game_actions_drop(Game *game);

/**
   Game actions implementation
*/

/*Checks the command code and calls the corresponding action function to update the game.*/
Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_actions_unknown(game);/*runs the unknown command action*/
      break;

    case EXIT:
      game_actions_exit(game);/*runs the exit command action*/
      break;

    case NEXT:
      game_actions_next(game);/*runs the next command action*/
      break;

    case BACK:
      game_actions_back(game);/*runs the back command action*/
      break;
    
     case TAKE:
      game_actions_take(game);/*runs the take command action*/
      break;

     case DROP:
      game_actions_drop(game);/*runs the drop command action*/
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
  Id current_id = NO_ID;/*intitializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);/*space gets the player's location so it can be updated*/
  if (space_id == NO_ID) {/*error control*/
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));/*current_id gets the south space id to move forwards*/
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);/*if it cannot happen, set the player's location to the current space*/
  }

  return;/*return nothing*/
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;/*initializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);/*space gets the player's location so it can be updated*/

  if (space_id == NO_ID) {/*error control*/
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));/*current_id gets the north space id to move backwards*/
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);/*if it cannot happen, set the player's location to the current space*/
  }

  return;/*return nothing*/
}

/*//////////////////////WILL HAVE TO CHANGE IT IN THE NEXT ITERATION/////////////////////////*/
void game_actions_take(Game *game) {
  /*inicialitating*/
  Id player_id = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;/*error control*/

  object_id = game_get_object_location(game);/*gets the location of the object*/

  player_id = game_get_player_location(game);/*gets the location of the player*/

  
  if ((NO_ID != object_id) && (object_id == player_id)) {/*if object exists and is in the same space as the player*/
    player_set_object(game_get_player(game), object_get_id(game_get_object(game)));/*sets the player's object to the taken object*/

    current_space = game_get_space(game, player_id);/*current_space gets the space where the player is located*/
    if (current_space) {
      space_del_object(current_space, object_get_id(game_get_object(game)));/*removes the object from the space*/
    }
  }

  return;
}

void game_actions_drop(Game *game) {
  /*inicialitating*/
  Id player_object = NO_ID;
  Id player_id = NO_ID;
  Space *current_space = NULL;

  if (!game) return;/*error control*/

  player_object = player_get_object(game_get_player(game));/*gets the object the player is carrying*/
  player_id = game_get_player_location(game);/*gets the location of the player*/

  if (player_object != NO_ID) {/*if the player has an object, he drops it in the current space*/
    player_set_object(game_get_player(game), NO_ID);/*removes the object from the player's inventory*/
    
    /* Agregar el objeto al espacio actual */
    current_space = game_get_space(game, player_id);/*current_space gets the space where the player is located*/
    if (current_space) {
      space_add_object(current_space, player_object);/*adds the object to the space*/
    }
  }

  return;
}