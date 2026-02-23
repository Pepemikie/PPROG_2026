/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @authorJose Miguel Romero Oubina
 * @version 0
 * @date 14-02-2026
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
  Id current_id = NO_ID;/*intitializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {/*error control*/
    return;
  }

  current_id = space_get_south(game_get_space(game, space_id));
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);
  }

  return;/*return nothing*/
}

void game_actions_back(Game *game) {
  Id current_id = NO_ID;/*initializating*/
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {/*error control*/
    return;
  }

  current_id = space_get_north(game_get_space(game, space_id));
  if (current_id != NO_ID) {/*error control*/
    game_set_player_location(game, current_id);
  }

  return;
}

/*create take and drop actions*/
  void game_actions_take(Game *game) {
    /*inicialitating*/
  Id player_location = NO_ID;
  Space *current_space = NULL;
  Id object_id = NO_ID;
  Player *player = NULL;
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {/*error control*/
    return;
  }
  
  current_space = game_get_space(game, player_location);
  if (current_space == NULL) {/*error control*/
    return;
  }
  
  object_id = space_get_object(current_space);
  if (object_id == NO_ID) {/*check if it is an object*/
    printf("There is no object here\n");
    return;
  }
  
  player = game_get_player(game);
  if (player == NULL) {/*error control*/
    return;
  }

  player_set_object_id(player, object_id);/*player obtains object id*/
  space_set_object(current_space, NO_ID);/*object id in space transforms into nothing*/
}

void game_actions_drop(Game *game) {
    /*inicialitating*/
  Id player_location = NO_ID;
  Space *current_space = NULL;
  Player *player = NULL;
  Id carried_object = NO_ID;
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) {/*error control*/
    return;
  }
  
  current_space = game_get_space(game, player_location);
  if (current_space == NULL) {/*error control*/
    return;
  }
  
  player = game_get_player(game);
  if (player == NULL) {/*error control*/
    return;
  }
  
  carried_object = player_get_object_id(player);
  if (carried_object == NO_ID) {/*checks if the player has the object*/
    printf("You do not have an object\n");
    return;
  }
  
  if (space_get_object(current_space) != NO_ID) {/*checks if there is an object on the same spot as the player*/
    printf("There is an object here, drop yours elsewhere...\n");
    return;
  }
  
  space_set_object(current_space, carried_object);
  player_set_object_id(player, NO_ID);

}
