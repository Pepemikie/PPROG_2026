/**
 *   It implements the game structure
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

struct _Game {
  Player *player;
  Object *objects[MAX_OBJECTS];
  Space *spaces[MAX_SPACES];
  Character *characters[MAX_CHARACTERS];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
  Bool object_adquirido;
  char last_message[WORD_SIZE];
  Status last_status;
};

/**
   Private functions
*/

/*   It gets the id of the space at a given position in the spaces array */
Id game_get_space_id_at(Game *game, int position);

/*   It sets the object_adquirido flag of the game */
void game_object_set_bool(Game *game, Bool object_bool) {
  if (!game) return;
  game->object_adquirido = object_bool;
}

/**
   Game interface implementation
*/

/*   It creates a new Game, allocating memory and initializing its members */
Game *game_create() {
  Game *game = NULL;
  int i;

  game = (Game *)malloc(sizeof(Game)); /* allocates memory for the game */
  if (game == NULL) return NULL;

  for (i = 0; i < MAX_SPACES; i++) game->spaces[i] = NULL; /* initializes spaces to NULL */

  game->n_spaces = 0;
  game->player = player_create(1); /* creates the player with default id */
  game->last_cmd = command_create();
  game->finished = FALSE;
  game->last_status = OK;
  strcpy(game->last_message, "");

  for (i = 0; i < MAX_OBJECTS; i++) game->objects[i] = NULL; /* initializes objects to NULL */
  for (i = 0; i < MAX_CHARACTERS; i++) game->characters[i] = NULL; /* initializes characters to NULL */

  return game;
}

/*   It creates a Game and loads its data from a file */
Status game_create_from_file(Game *game, char *filename) {
  if (!game || !filename) return ERROR;

  if (game_reader_load_spaces(game, filename) == ERROR) return ERROR; /* loads spaces from file */
  if (game_reader_load_objects(game, filename) == ERROR) return ERROR; /* loads objects from file */
  if (game_reader_load_characters(game, filename) == ERROR) return ERROR; /* loads characters from file */

  game_set_player_location(game, game_get_space_id_at(game, 0)); /* places player in the first space */

  return OK;
}

/*   It destroys a Game, freeing the allocated memory */
Status game_destroy(Game *game) {
  int i = 0;

  if (!game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) space_destroy(game->spaces[i]); /* destroys all spaces */

  player_destroy(game->player);
  command_destroy(game->last_cmd);

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++)
    object_destroy(game->objects[i]); /* destroys all objects */

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++)
    character_destroy(game->characters[i]); /* destroys all characters */

  free(game);
  return OK;
}

/*   It gets a space from the game by its id */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_spaces; i++) { /* iterates until matching id is found */
    if (id == space_get_id(game->spaces[i])) return game->spaces[i];
  }
  return NULL;
}

/*   It gets the player of the game */
Player *game_get_player(Game *game) {
  if (!game) return NULL;
  return game->player;
}

/*   It gets the current location of the player */
Id game_get_player_location(Game *game) {
  if (!game) return NO_ID;
  return player_get_location(game->player);
}

/*   It sets the location of the player */
Status game_set_player_location(Game *game, Id id) {
  if (!game || id == NO_ID) return ERROR;
  return player_set_location(game->player, id);
}

/*   It gets the location of an object by its id */
Id game_get_object_location(Game *game, Id object_id) {
  int i;

  if (!game || object_id == NO_ID) return NO_ID;

  for (i = 0; i < game->n_spaces; i++) { /* iterates spaces until the object is found */
    if (space_has_object(game->spaces[i], object_id) == TRUE)
      return space_get_id(game->spaces[i]);
  }
  return NO_ID;
}

/*   It adds an object to the game */
Status game_add_object(Game *game, Object *object) {
  int i = 0;

  if (!game || !object) return ERROR;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++); /* finds first empty slot */

  if (i >= MAX_OBJECTS) return ERROR;

  game->objects[i] = object;
  return OK;
}

/*   It gets an object from the game by its id */
Object *game_get_object(Game *game, Id id) {
  int i;
  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) { /* iterates until matching id is found */
    if (object_get_id(game->objects[i]) == id) return game->objects[i];
  }
  return NULL;
}

/*   It gets an object from the game by its index */
Object *game_get_object_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_OBJECTS) return NULL;
  return game->objects[index];
}

/*   It sets the location of an object in the game */
Status game_set_object_location(Game *game, Id space_id, Id object_id) {
  Space *s = NULL;
  Object *obj = NULL;

  if (!game || space_id == NO_ID || object_id == NO_ID) return ERROR;

  s = game_get_space(game, space_id); /* retrieves the target space */
  obj = game_get_object(game, object_id); /* retrieves the object */

  if (!s || !obj) return ERROR;

  return space_add_object(s, object_get_id(obj)); /* adds object to the space */
}

/*   It gets the last command introduced by the user */
Command *game_get_last_command(Game *game) {
  if (!game) return NULL;
  return game->last_cmd;
}

/*   It sets the last command introduced by the user */
Status game_set_last_command(Game *game, Command *command) {
  if (!game){
    game->last_status = ERROR;
    return ERROR;
  }
  game->last_cmd = command;
  game->last_status = OK;
  return OK;
}

/*   It gets the status of the last command executed */
Status game_get_last_status(Game *game) {
  if (!game) return ERROR;
  return game->last_status;
}

/*   It sets the status of the last command executed */
Status game_set_last_status(Game *game, Status status) {
  if (!game) return ERROR;
  game->last_status = status;
  return OK;
}

/*   It gets whether the game has finished */
Bool game_get_finished(Game *game) {
  if (!game) return FALSE;
  return game->finished;
}

/*   It sets the finished state of the game */
Status game_set_finished(Game *game, Bool finished) {
  if (!game) return ERROR;
  game->finished = finished;
  return OK;
}

/*   It adds a character to the game */
Status game_add_character(Game *game, Character *character) {
  int i;
  if (!game || !character) return ERROR;

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++); /* finds first empty slot */

  if (i >= MAX_CHARACTERS) return ERROR;

  game->characters[i] = character;
  return OK;
}

/*   It sets the location of a character in the game */
Status game_set_character_location(Game *game, Id space_id, Id character_id) {
  int i;
  if (!game || space_id == NO_ID || character_id == NO_ID) return ERROR;

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) { /* iterates until matching id is found */
    if (character_get_id(game->characters[i]) == character_id) {
      character_set_location(game->characters[i], space_id); /* sets character location */
      space_set_character(game_get_space(game, space_id), character_id); /* links character to space */
      return OK;
    }
  }
  return ERROR;
}

/*   It gets the character located in a given space */
Character *game_get_character_in_space(Game *game, Id space_id) {
  int i;
  if (!game || space_id == NO_ID) return NULL;

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) { /* iterates until matching location is found */
    if (character_get_location(game->characters[i]) == space_id)
      return game->characters[i];
  }
  return NULL;
}

/*   It gets a character from the game by its index */
Character *game_get_character_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_CHARACTERS) return NULL;
  return game->characters[index];
}

/*   It sets the last message displayed in the game */
Status game_set_last_message(Game *game, const char *message) {
  if (!game || !message) return ERROR;
  strncpy(game->last_message, message, WORD_SIZE - 1); /* copies message safely */
  game->last_message[WORD_SIZE - 1] = '\0';
  return OK;
}

/*   It gets the last message displayed in the game */
const char *game_get_last_message(Game *game) {
  if (!game) return NULL;
  return game->last_message;
}

#ifdef DEBUG
/*   It prints the data of the game */
void game_print(Game *game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < game->n_spaces; i++) space_print(game->spaces[i]); /* prints all spaces */

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) {
    printf("=> Object %ld location: %ld\n",
           object_get_id(game->objects[i]),
           game_get_object_location(game, object_get_id(game->objects[i]))); /* prints each object location */
  }
  printf("=> Player location: %ld\n", game_get_player_location(game));
}
#endif

/**
   Implementation of private functions
*/

/*   It adds a space to the game */
Status game_add_space(Game *game, Space *space) {
  if (!space || game->n_spaces >= MAX_SPACES) return ERROR;

  game->spaces[game->n_spaces] = space; /* stores space in the next available slot */
  game->n_spaces++;
  return OK;
}

/*   It gets the id of the space at a given position in the spaces array */
Id game_get_space_id_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) return NO_ID;
  return space_get_id(game->spaces[position]);
}