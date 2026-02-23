/**
 * @brief It implements the game structure
 *
 * @file game.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include "game.h"
#include "game_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
   Private functions
*/

/**
 * @brief Assigns Space to the first empty space avaiable on game->spaces and adds 1 to the number of currently allocated spaces, then returns OK
 * Si space es NULL o el numero de espacios es igual o mayor a MAX_SPACES devolvera ERROR
 * @author Profesores PPROG
 * @param Game*  
 * @param Space*  
 * @return Status, OK, ERROR
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Returns the Space which Id corresponds to the int introduced
 * @author Profesores PPROG
 * @param Game*  
 * @param int position
 * @return Id, NO_ID = -1
 */
Id game_get_space_id_at(Game *game, int position);

/**
   Game interface implementation
*/

/*Initializes the game structure, creates the player, object, and command, and prepares the spaces array.*/
Status game_create(Game *game) {
/* Initializes all space pointers to NULL */
  int i;

  for (i = 0; i < MAX_SPACES; i++) {
    game->spaces[i] = NULL;
  }

  game->n_spaces = 0;/* Sets the number of spaces to 0 */
  game->player = player_create(PLAYER_ID);/* Creates and allocates memory for the player */
  game->object = object_create(OBJECT_ID);/* Creates and allocates memory for the object */


  game->last_cmd = command_create();/* Creates the command structure */
  game->finished = FALSE;/* Sets the game as not finished */

  return OK;
}

/*Creates the game and loads all spaces from a file, placing the player and object in the first space.*/
Status game_create_from_file(Game *game, char *filename) {
  /* Initializes the game structure */
  if (game_create(game) == ERROR) {
    return ERROR;
  }
/* Loads spaces from the file into the game */
  if (game_load_spaces(game, filename) == ERROR) {
    return ERROR;
  }

  /* The player and the object are located in the first space */
  game_set_player_location(game, game_get_space_id_at(game, 0));
  /* Places the object in the first space */
  game_set_object_location(game, game_get_space_id_at(game, 0));

  return OK;
}

/*Frees the memory used by all spaces and the last command.*/
Status game_destroy(Game *game) {
  int i = 0;
/* Frees the memory of all created spaces */
  for (i = 0; i < game->n_spaces; i++) {
    space_destroy(game->spaces[i]);
  }
/* Frees the memory of the last command */
  command_destroy(game->last_cmd);

  return OK;
}

/*Searches and returns the space with the given ID.*/
Space *game_get_space(Game *game, Id id) {
  int i = 0;
/* Checks that the ID is valid */
  if (id == NO_ID) {
    return NULL;
  }
/* Searches for the space with the given ID */
  for (i = 0; i < game->n_spaces; i++) {
    if (id == space_get_id(game->spaces[i])) {
      return game->spaces[i];
    }
  }
/* Returns NULL if no matching space is found */
  return NULL;
}

/*Returns the current space ID where the player is located.*/
Id game_get_player_location(Game *game) {
  if(!game)
    return NO_ID;
/* Returns the player's current location */
  return player_get_location(game->player);
}

/*Returns the player stored in the game.*/
Player *game_get_player(Game *game) { return game->player; }

/*Updates the player’s location to a given space ID.*/
Status game_set_player_location(Game *game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }
/* Sets the player's location to the given space ID */
  return player_set_location(game->player, id);
}

/*Finds and returns the space ID where the object is located*/
Id game_get_object_location(Game *game) {
  int i=0;
/* Searches all spaces to find where the object is located */
  for(i=0; game->spaces[i]!=NULL; i++){
    if(space_get_object(game->spaces[i]) != NO_ID){
      return space_get_id(game->spaces[i]);
    }
  }
  return NO_ID; 
}

/*Places the object in the specified space.*/
Status game_set_object_location(Game *game, Id space_id) {
  if (!game || space_id == NO_ID) {
    return ERROR;
  }
/* Places the object in the specified space */
  space_set_object(game_get_space(game, space_id), object_get_id(game->object));

  return OK;
}

/*Returns the object stored in the game.*/
Object *game_get_object(Game *game) { return game->object; }

/*Returns the last command entered by the user.*/
Command* game_get_last_command(Game *game) { return game->last_cmd; }

/*Updates the last command executed in the game.*/
Status game_set_last_command(Game *game, Command *command) {
  /* Stores the last command entered by the user */
  game->last_cmd = command;

  return OK;
}

/*Returns whether the game has finished or not.*/
Bool game_get_finished(Game *game) { return game->finished; }

/*Sets the game’s finished state.*/
Status game_set_finished(Game *game, Bool finished) {
  /* Updates the finished state of the game */
  game->finished = finished;

  return OK;
}

/*Prints all spaces and shows the player and object locations.*/
void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");
/* Prints all spaces in the game */
  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) {
    space_print(game->spaces[i]);
  }
/* Prints the object and player locations */
  printf("=> Object location: %ld\n", game_get_object_location(game));
  printf("=> Player location: %ld\n", player_get_location(game->player));
}

/**
   Implementation of private functions
*/

/*Adds a new space to the game’s spaces array.*/
Status game_add_space(Game *game, Space *space) {
  if ((space == NULL) || (game->n_spaces >= MAX_SPACES)) {
    return ERROR;
  }
/* Adds a space to the spaces array and increases the space count */
  game->spaces[game->n_spaces] = space;
  game->n_spaces++;

  return OK;
}

/*Returns the space ID stored at a specific position in the spaces array.*/
Id game_get_space_id_at(Game *game, int position) {
  if (position < 0 || position >= game->n_spaces) {
    return NO_ID;
  }
/* Returns the space ID at the given array position */
  return space_get_id(game->spaces[position]);
}

