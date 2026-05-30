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
#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/** 
 * @brief Structure representing the game
 */
struct _Game {
  Player *players[MAX_PLAYERS]; /**< Array of pointers to Player structures */
  int n_players; /**< Number of players in the game */
  Object *objects[MAX_OBJECTS]; /**< Array of pointers to Object structures */
  int n_objects; /**< Number of objects in the game */
  char last_object_description[WORD_SIZE]; /**< String with the description of the last object inspected */
  Space *spaces[MAX_SPACES]; /**< Array of pointers to Space structures */
  int n_spaces; /**< Number of spaces in the game */
  Character *characters[MAX_CHARACTERS]; /**< Array of pointers to Character structures */
  int n_characters; /**< Number of characters in the game */
  char last_message[WORD_SIZE]; /**< String with the last message of the character */
  Link *links[MAX_LINKS]; /**< Array of pointers to Link structures */
  int n_links; /**< Number of links in the game */
  Command *last_cmd; /**< Pointer to the last Command issued by the player */
  int last_cmd_player; /**< Index of the player who issued the last command */
  Status last_status; /**< Status of the last action performed */
  Bool finished; /**< Flag indicating whether the game has finished */
  int turn; /**< Current player's turn */
  int failure_count; /**< Number of consecutive failed actions */
  Bool must_keep_turn; /**< Flag indicating whether the player must keep their turn after a failed action */
};

/**
 * @brief Gets the id of the space at a given position in the spaces array
 * 
 * @param game a pointer to the Game struct
 * @param position the index of the space in the spaces array
 * @return Id of the space at the given position, or NO_ID if the position is invalid
 */
Id game_get_space_id_at(Game *game, int position);

/* It creates a new Game, allocating memory and initializing its members */
Game *game_create() {
  Game *game = NULL;
  int i;

  game = (Game *)malloc(sizeof(Game)); /* allocates memory for the game */
  if (game == NULL) return NULL;

  for (i = 0; i < MAX_SPACES; i++) game->spaces[i] = NULL; /* initializes spaces to NULL */

  game->n_spaces = 0;
  game->last_cmd = command_create(); /* creates an empty command */
  game->last_cmd_player = -1;
  game->finished = FALSE;
  game->last_status = OK;
  strcpy(game->last_message, "");
  strcpy(game->last_object_description, ""); /* initializes last message and description to empty strings */

  for (i = 0; i < MAX_OBJECTS; i++) game->objects[i] = NULL; /* initializes objects to NULL */
  for (i = 0; i < MAX_CHARACTERS; i++) game->characters[i] = NULL; /* initializes characters to NULL */
  for (i = 0; i < MAX_LINKS; i++) game->links[i] = NULL; /* initializes links to NULL */
  for (i = 0; i < MAX_PLAYERS; i++) game->players[i] = NULL; /* initializes players to NULL. Multiplayer */
  game->n_links = 0;
  game->turn = 0;
  game->n_players = 0;
  game->n_characters = 0;
  game->n_objects = 0;

  game->failure_count = 0;
  game->must_keep_turn = FALSE;
  return game;
}


/*
GAME & SPACES
*/
/* It creates a Game and loads its data from a file */
Status game_create_from_file(Game *game, char *filename) {
  int i;
  Id location = NO_ID;
  if (!game || !filename) return ERROR;

  if (game_management_load_spaces(game, filename) == ERROR) return ERROR; /* loads spaces from file */
  if (game_management_load_objects(game, filename) == ERROR) return ERROR; /* loads objects from file */
  if (game_management_load_characters(game, filename) == ERROR) return ERROR; /* loads characters from file */
  if (game_management_load_links(game, filename) == ERROR) return ERROR; /* loads links from file */
  if (game_management_load_players(game, filename) == ERROR) return ERROR; /* loads players from file. Multiplayer */

  for (i = 0; i < game->n_players; i++) {
    if (game->players[i]) {
      location = player_get_location(game->players[i]);
      if (location != NO_ID) {
        game_discover_space(game, location); /* discovers the initial location of each player */
      }
    }
  }

  return OK;
}

Status game_clear(Game *game) {
  int i = 0;

  if (!game) return ERROR;

  for (i = 0; i < game->n_spaces; i++) space_destroy(game->spaces[i]); /* destroys all spaces */

  for (i = 0; i < game->n_players; i++) player_destroy(game->players[i]); /* destroys all players. Multiplayer */

  for (i = 0; i < game->n_characters; i++) character_destroy(game->characters[i]); /* destroys all characters */

  for (i = 0; i < game->n_objects; i++) object_destroy(game->objects[i]); /* destroys all objects */

  for (i = 0; i < game->n_links; i++) link_destroy(game->links[i]); /* destroys all links */

  game->n_spaces = 0;
  game->n_players = 0;
  game->n_characters = 0;
  game->n_objects = 0;
  game->n_links = 0;
  game->turn = 0;
  game->finished = FALSE;
  strcpy(game->last_message, "");
  strcpy(game->last_object_description, "");

  return OK;
}

/* It destroys a Game, freeing the allocated memory */
Status game_destroy(Game *game) {
  if (!game) return ERROR;

  if(game_clear(game) == ERROR) return ERROR; /* clears current game data */

  command_destroy(game->last_cmd); /* destroys the last command */

  free(game);
  return OK;
}

/* It gets a space from the game by its id */
Space *game_get_space(Game *game, Id id) {
  int i = 0;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_spaces; i++) { /* iterates until matching id is found */
    if (id == space_get_id(game->spaces[i])) return game->spaces[i];
  }
  return NULL;
}

/* It gets the current turn index */
int game_get_turn(Game *game) {
  if (!game) return -1;
  return game->turn;
}

/* It sets the current turn index */
Status game_set_turn(Game *game, int turn) {
  if (!game || turn < 0 || turn >= game->n_players) return ERROR;
  game->turn = turn;
  return OK;
}

/* It advances the turn to the next player */
Status game_next_turn(Game *game) {
  if (!game || game->n_players == 0) return ERROR;
  game->turn = (game->turn + 1) % game->n_players; /* cycles through players */
  return OK;
}

/* It gets the last command introduced by the user */
Command *game_get_last_command(Game *game) {
  if (!game) return NULL;
  return game->last_cmd;
}

int game_get_last_command_player(Game *game) {
  if (!game) return -1;
  return game->last_cmd_player;
}

/* It sets the last command introduced by the user */
Status game_set_last_command(Game *game, Command *command) {
  if (!game){
    return ERROR;
  }
  game->last_cmd = command;
  game->last_cmd_player = command ? game->turn : -1;
  game->last_status = OK;
  return OK;
}

/* It gets the status of the last command executed */
Status game_get_last_status(Game *game) {
  if (!game) return ERROR;
  return game->last_status;
}

/* It sets the status of the last command executed */
Status game_set_last_status(Game *game, Status status) {
  if (!game) return ERROR;
  game->last_status = status;
  return OK;
}

/* It gets whether the game has finished */
Bool game_get_finished(Game *game) {
  if (!game) return FALSE;
  return game->finished;
}

/* It sets the finished state of the game */
Status game_set_finished(Game *game, Bool finished) {
  if (!game) return ERROR;
  game->finished = finished;
  return OK;
}

/* It adds a space to the game */
Status game_add_space(Game *game, Space *space) {
  if (!space || game->n_spaces >= MAX_SPACES) return ERROR;

  game->spaces[game->n_spaces] = space; /* stores space in the next available slot */
  game->n_spaces++;
  return OK;
}

/* It gets the number of spaces in the game */
int game_get_num_spaces(Game *game) {
  if (!game) return 0;
  return game->n_spaces;
}

/* It gets an spaces from the game by its index */
Space *game_get_space_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_SPACES) return NULL;
  return game->spaces[index];
}

/* It gets a space by its name*/
Space *game_get_space_by_name(Game *game, const char *name) {
  int i;
  if (!game || !name) return NULL;

  for ( i = 0; i < MAX_SPACES; i++) {
    Space *s = game_get_space_by_index(game, i);
    if (s && strcasecmp(space_get_name(s), name) == 0) {
      return s;
    }
    if (!s) break;
  }

  return NULL;
}

/* It sets the failure count of the game */
void game_set_failure_count(Game *game, int count) {
  if (game) game->failure_count = count;
}

/* It gets the failure count of the game */
int game_get_failure_count(Game *game) {
  return game ? game->failure_count : 0;
}

/* It sets whether the game must keep the current turn */
void game_set_must_keep_turn(Game *game, Bool keep) {
  if (game) game->must_keep_turn = keep;
}

/* It gets whether the game must keep the current turn */
Bool game_get_must_keep_turn(Game *game) {
  return game ? game->must_keep_turn : FALSE;
}


/*
PLAYER
*/
/* It gets the ACTUAL player of the game */
Player *game_get_player(Game *game) {
  if (!game || game->n_players == 0) return NULL;
  return game->players[game->turn]; /* returns the actual player */
}

/* It adds a player to the game */
Status game_add_player(Game *game, Player *player) {
  if (!game || !player) return ERROR;
  if (game->n_players >= MAX_PLAYERS) return ERROR;

  game->players[game->n_players] = player; /* stores player in next empty slot */
  game->n_players++;
  return OK;
}

/* It gets the number of players in the game */
int game_get_num_players(Game *game) {
  if (!game) return 0;
  return game->n_players;
}

/* It gets the current location of the player */
Id game_get_player_location(Game *game) {
  if (!game) return NO_ID;
  return player_get_location(game_get_player(game));
}

/* It sets the location of the player */
Status game_set_player_location(Game *game, Id id) {
  Status status;
  Player *player = NULL;

  if (!game || id == NO_ID) return ERROR;

  player = game_get_player(game); /* gives the actual player */
  if (!player) return ERROR;

  status = player_set_location(player, id); /* sets the location of the actual player */
  if (status == OK){
    game_discover_space(game, id); /* discovers the new location of the player */
  }

  return status;
}

/* It gets a player from the game by its index */
Player *game_get_player_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= game->n_players) return NULL;

  return game->players[index]; /* returns the player at the given index */
}

/* It gets a player by its name*/
Player *game_get_player_by_name(Game *game, const char *name) {
  int i;
  if (!game || !name) return NULL;

  for ( i = 0; i < MAX_PLAYERS; i++) {
    Player *p = game_get_player_by_index(game, i);
    if (p && strcasecmp(player_get_name(p), name) == 0) {
      return p;
    }
    if (!p) break;
  }

  return NULL;
}

/* It gets a player by its id */
Player *game_get_player_by_id(Game *game, Id id){
  int i;
  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < MAX_PLAYERS; i++) {
    Player *p = game_get_player_by_index(game, i);
    if (p && player_get_id(p) == id) {
      return p;
    }
    if (!p) break;
  }
  return NULL;
}

/*
OBJECT
*/
/* It adds an object to the game */
Status game_add_object(Game *game, Object *object) {

  if (!game || !object || game->n_objects >= MAX_OBJECTS) return ERROR;

  game->objects[game->n_objects] = object; /* stores space in the next available slot */
  game->n_objects++;

  return OK;
}

/* It gets the number of objects in the game */
int game_get_num_objects(Game *game) {
  if (!game) return 0;
  return game->n_objects;
}

/* It sets the location of an object in the game */
Status game_set_object_location(Game *game, Id space_id, Id object_id) {
  Space *s = NULL;
  Object *obj = NULL;

  if (!game || space_id == NO_ID || object_id == NO_ID) return ERROR;

  s = game_get_space(game, space_id); /* retrieves the target space */
  obj = game_get_object(game, object_id); /* retrieves the object */

  if (!s || !obj) return ERROR;

  return space_add_object(s, object_get_id(obj)); /* adds object to the space */
}

/* It gets the location of an object by its id */
Id game_get_object_location(Game *game, Id object_id) {
  int i;

  if (!game || object_id == NO_ID) return NO_ID;

 for (i = 0; i < game->n_players; i++) { /* iterates players until the object is found */
    if (game->players[i] && player_has_object(game->players[i], object_id) == TRUE)
      return player_get_location(game->players[i]);
  }

  for (i = 0; i < game->n_spaces; i++) { /* iterates spaces until the object is found */
    if (space_has_object(game->spaces[i], object_id) == TRUE)
      return space_get_id(game->spaces[i]);
  }
  return NO_ID;
}

/* It gets an object from the game by its id */
Object *game_get_object(Game *game, Id id) {
  int i;
  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < MAX_OBJECTS && game->objects[i] != NULL; i++) { /* iterates until matching id is found */
    if (object_get_id(game->objects[i]) == id) return game->objects[i];
  }
  return NULL;
}

/* It gets an object from the game by its index */
Object *game_get_object_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_OBJECTS) return NULL;
  return game->objects[index];
}

/* It sets the last object description displayed in the game */
Status game_set_last_object_description(Game *game, const char *description) {
  if (!game || !description) return ERROR;
  strncpy(game->last_object_description, description, WORD_SIZE - 1); /* copies description safely */
  game->last_object_description[WORD_SIZE - 1] = '\0';
  return OK;
}

/* It gets the last object description displayed in the game */
const char *game_get_last_object_description(Game *game) {
  if (!game) return NULL;
  return game->last_object_description;
}

/* It gets a object by its name*/
Object *game_get_object_by_name(Game *game, const char *name) {
  int i;
  if (!game || !name) return NULL;
  
  for ( i = 0; i < MAX_OBJECTS; i++) {
    Object *o = game_get_object_by_index(game, i);
    if (o && strcasecmp(object_get_name(o), name) == 0) {
      return o;
    }
    if (!o) break;
  }

  return NULL;
}


/*
CHARACTER
*/
/* It adds a character to the game */
Status game_add_character(Game *game, Character *character) {

  if (!game || !character || game->n_characters >= MAX_CHARACTERS) return ERROR;

  game->characters[game->n_characters] = character; /* stores space in the next available slot */
  game->n_characters++;
  
  return OK;
}

/* It gets the number of characters in the game */
int game_get_num_characters(Game *game) {
  if (!game) return 0;
  return game->n_characters;
}

/* It sets the location of a character in the game */
Status game_set_character_location(Game *game, Id space_id, Id character_id) {
  Space *s = NULL;
  Character *c = NULL;

  if(!game || space_id == NO_ID || character_id == NO_ID) return ERROR;

  s = game_get_space(game, space_id); /* retrieves the target space */
  c = game_get_character(game, character_id); /* retrieves the character */
  
  if (!s || !c) return ERROR;

  return space_add_character(s, character_get_id(c), character_is_friendly(c)); /* adds character to the space */
}

/* It gets the location of a character by its id */
Id game_get_character_location(Game *game, Id character_id) {
  int i;
  if (!game || character_id == NO_ID) return NO_ID;

  for (i = 0; i < game->n_spaces; i++) {
    if (space_has_character(game->spaces[i], character_id) == TRUE)
      return space_get_id(game->spaces[i]);
  }
  return NO_ID;
}

/* It gets the character located in a given space */
Character *game_get_character_in_space(Game *game, Id space_id) {
  int i;
  Space *space = NULL;
  Id *character_id = NULL;

  if (!game || space_id == NO_ID) return NULL;
  
  space = game_get_space(game, space_id);
  if (!space) return NULL;
  
  character_id = space_get_character(space);
  if (!character_id) return NULL;

  for (i = 0; i < MAX_CHARACTERS && game->characters[i] != NULL; i++) {
      if (character_get_id(game->characters[i]) == *character_id)
          return game->characters[i];
  }
  return NULL;
}

/* It gets a character from the game by its id */
Character* game_get_character(Game* game, Id id) {
    int i;
  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < MAX_CHARACTERS&& game->characters[i] != NULL; i++) { /* iterates until matching id is found */
    if (character_get_id(game->characters[i]) == id) return game->characters[i];
  }
  return NULL;
}

/* It gets a character from the game by its index */
Character *game_get_character_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_CHARACTERS) return NULL;
  return game->characters[index];
}

/* It sets the last message displayed in the game */
Status game_set_last_message(Game *game, const char *message) {
  if (!game || !message) return ERROR;
  strncpy(game->last_message, message, WORD_SIZE - 1); /* copies message safely */
  game->last_message[WORD_SIZE - 1] = '\0';
  return OK;
}

/* It gets the last message displayed in the game */
const char *game_get_last_message(Game *game) {
  if (!game) return NULL;
  return game->last_message;
}

/* It gets a character from the game by its name */
Character *game_get_character_by_name(Game *game, const char *name) {
  int i;
  if (!game || !name) return NULL;

  for ( i = 0; i < MAX_CHARACTERS; i++) {
    Character *c = game_get_character_by_index(game, i);
    if (c && strcasecmp(character_get_name(c), name) == 0) {
      return c;
    }
    if (!c) break;
  }

  return NULL;
}


/*
LINK
*/
/* It adds a link to the game */
Status game_add_links(Game *game, Link *link) {

  if (!game || !link || game->n_links >= MAX_LINKS) return ERROR;

  game->links[game->n_links] = link; /* stores link in the next available slot */
  game->n_links++;
  
  return OK;
}

/* It gets the number of links in the game */
int game_get_num_links(Game *game) {
  if (!game) return 0;
  return game->n_links;
}

/*  It gets the id of the space connected to a given space in a specific direction */
Id game_get_connection(Game *game, Id space_id, Direction direction) {
  int i;

  if (!game || space_id == NO_ID || direction == UNKNOWN_DIR) return NO_ID; /*error control*/

  for (i = 0; i < game->n_links; i++) {
    if (game->links[i] != NULL && link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == direction) {
      return link_get_destination(game->links[i]);
    }
  }
  return NO_ID;
}

/* It checks if the connection to a given space in a specific direction is open */
Bool game_get_connection_status(Game *game, Id space_id, Direction direction) {
  int i;

  if (!game || space_id == NO_ID || direction == UNKNOWN_DIR) return FALSE; /* error control */

  for (i = 0; i < game->n_links; i++) {
    if (game->links[i] != NULL && link_get_origin(game->links[i]) == space_id && link_get_direction(game->links[i]) == direction) {
      return link_get_open(game->links[i]);
    }
  }
  return FALSE;
}

/* It marks a Space as discovered*/
Status game_discover_space(Game *game, Id space_id) {
  Space *space = NULL;

  if (!game || space_id == NO_ID) return ERROR;

  space = game_get_space(game, space_id);
  if (!space) return ERROR;

  return space_set_discovered(space, TRUE);
}

/* It gets a link from the game by its id */
Link* game_get_link(Game *game, Id id) {
  int i;

  if (!game || id == NO_ID) return NULL;

  for (i = 0; i < game->n_links; i++) {
    if (game->links[i] != NULL && link_get_id(game->links[i]) == id) {
      return game->links[i];
    }
  }
  return NULL;
}

/* It gets a link from the game by its name (F11, I4) */
Link *game_get_link_by_name(Game *game, const char *name) {
  int i;

  if (!game || !name) return NULL;     

  for (i = 0; i < game->n_links; i++) { /* Iterates until matching name is found (the one passed as argument) */ 
    if (game->links[i] != NULL && strcasecmp(link_get_name(game->links[i]), name) == 0)
      return game->links[i];
  }

  return NULL;
}

/* It gets a link from the game by its index */
Link *game_get_link_by_index(Game *game, int index) {
  if (!game || index < 0 || index >= MAX_LINKS) return NULL;
  return game->links[index];
}


#ifdef DEBUG
/* It prints the data of the game */
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

Id game_get_space_id_at(Game *game, int position) {
  if (!game || position < 0 || position >= game->n_spaces) return NO_ID;
  return space_get_id(game->spaces[position]);
}
