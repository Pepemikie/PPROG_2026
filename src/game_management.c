/**
 * @brief It implements the game_management interpreter
 *
 * @file game_management.c
 * @author José Miguel Romero Oubiña
 * @version 1
 * @date 12-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_management.h"
#include "game.h"
#include "space.h"
#include "object.h"
#include "character.h"
#include "player.h"
#include "link.h"

/* It reads the spaces from a file, creates each space with its name and connections, and adds them to the game */
Status game_management_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1];
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  Status status = OK;
  Bool discovered = FALSE;
  int i;

  if (!game || !filename) return ERROR; /* error control */

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) { /* identifies space lines */
      toks = strtok(line + 3, "|"); /* parses id, name and connections */
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      discovered = toks ? (Bool)atoi(toks) : FALSE;

      /* Read gdesc lines — 5 lines of up to 9 chars */
      for (i = 0; i < SPACE_GDESC_LINES; i++) {
        toks = strtok(NULL, "|");
        if (toks) {
          strncpy(gdesc[i], toks, SPACE_GDESC_LENGTH);
          gdesc[i][SPACE_GDESC_LENGTH] = '\0';
        } else {
          strcpy(gdesc[i], "         "); /* fills empty lines with spaces */
        }
      }

#ifdef DEBUG
      printf("Leidos:%ld|%s|%s\n", id, name, discovered ? "discovered" : "not discovered");
#endif

      space = space_create(id);
      if (space != NULL) { /* sets all space attributes and adds it to the game */
        space_set_name(space, name);
        space_set_gdesc(space, gdesc);
        space_set_discovered(space, discovered);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* It reads the objects from a file, creates each object with its name and id, and adds them to the game */
Status game_management_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[WORD_SIZE] = "";
  char description[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, space_id = NO_ID;
  Object *obj = NULL;
  Status status = OK;
  int health = 0;
  Bool movable = FALSE;
  Id dependency = NO_ID;
  Id open = NO_ID;

  if (!game || !filename) return ERROR; /* error control */

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) { /* identifies object lines */
      toks = strtok(line + 3, "|"); /* parses id, name, gdesc, description, location, health, movable, dependency, open */
      if (!toks) continue;
      id = atol(toks);
      toks = strtok(NULL, "|");
      if (!toks) continue;
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      if (!toks) continue;
      strcpy(gdesc, toks);
      toks = strtok(NULL, "|");
      if (!toks) continue;
      strcpy(description, toks);
      toks = strtok(NULL, "|");
      if (!toks) continue;
      space_id = atol(toks);
      toks = strtok(NULL, "|");
      health = toks ? atoi(toks) : 0;
      toks = strtok(NULL, "|");
      movable = toks ? (Bool)atoi(toks) : FALSE;
      toks = strtok(NULL, "|");
      dependency = toks ? atol(toks) : NO_ID;
      toks = strtok(NULL, "|");
      open = toks ? atol(toks) : NO_ID;
#ifdef DEBUG
      printf("Leido: o:%ld|%s|%s|%s|%ld|%d|%d|%ld|%ld\n", id, name, gdesc, description, space_id, health, movable, dependency, open);
#endif
      if ((obj = object_create(id))) { /* sets object attributes and places it in the game */
        object_set_name(obj, name);
        object_set_gdesc(obj, gdesc);
        object_set_description(obj, description);
        object_set_health(obj, health);
        object_set_movable(obj, movable);
        object_set_dependency(obj, dependency);
        object_set_open(obj, open);
        game_add_object(game, obj);
        game_set_object_location(game, space_id, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* It reads the characters from a file, creates each character with its name, description and other attributes, and adds them to the game */
Status game_management_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  Id id = NO_ID;
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_SIZE] = "";
  int health = 0;
  int friendly = 0;
  Id space_id = NO_ID;
  Id following = NO_ID;
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Character *character = NULL;
  Status status = OK;

  if (!game || !filename) return ERROR; /* error control */

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) { /* identifies character lines */
      toks = strtok(line + 3, "|"); /* parses id, name, gdesc, health, friendly, location, following and message*/
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      strncpy(gdesc, toks, GDESC_SIZE - 1);
      gdesc[GDESC_SIZE - 1] = '\0';
      toks = strtok(NULL, "|");
      health = atoi(toks);
      toks = strtok(NULL, "|");
      friendly = atoi(toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);
      toks = strtok(NULL, "|");
      following = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) {
        toks[strcspn(toks, "\n")] = '\0';
        strncpy(message, toks, WORD_SIZE - 1);
        message[WORD_SIZE - 1] = '\0';
      }

#ifdef DEBUG
      printf("Leido: c:%ld|%s|%s|%d|%d|%ld|%ld|%s\n", id, name, gdesc, health, friendly, space_id, following, message);
#endif
      if ((character = character_create(id))) { /* sets all character attributes and places it in the game */
        character_set_name(character, name);
        character_set_gdesc(character, gdesc);
        character_set_health(character, health);
        character_set_friendly(character, (Bool)friendly);
        character_set_message(character, message);
        character_set_following(character, following);
        game_add_character(game, character);
        game_set_character_location(game, space_id, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* It reads the links from a file, creates each link with its attributes, and adds them to the game */
Status game_management_load_links(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, origin = NO_ID, destination = NO_ID;
  Direction direction = UNKNOWN_DIR;
  Bool open = TRUE;
  Link *link = NULL;
  Status status = OK;

  if (!game || !filename) return ERROR; /* error control */

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#l:", line, 3) == 0) { /* identifies link lines */
      toks = strtok(line + 3, "|"); /* parses id, name, origin, destination, open, direction */
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      open = (Bool)atoi(toks);
      toks = strtok(NULL, "|");
      if (strcmp(toks, "N") == 0)
      direction = N;
      else if (strcmp(toks, "S") == 0)
      direction = S;
      else if (strcmp(toks, "E") == 0)
      direction = E;
      else if (strcmp(toks, "W") == 0)
      direction = W;
      else if (strcmp(toks, "U") == 0)
      direction = U;
      else if (strcmp(toks, "D") == 0)
      direction = D;
      else
      direction = UNKNOWN_DIR;

#ifdef DEBUG
      printf("Leido: l:%ld|%s|%ld|%ld|%d|%d\n", id, name, origin, destination, open, direction);
#endif
      if ((link = link_create(id))) { /* sets all link attributes and adds it to the game */
        link_set_name(link, name);
        link_set_origin(link, origin);
        link_set_destination(link, destination);
        link_set_open(link, open);
        link_set_direction(link, direction);
        game_add_links(game, link);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* It reads the players from a file, creates each player and adds them to the game. Multiplayer */
Status game_management_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[P_GDESC_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location_id = NO_ID, object_id = NO_ID, team = NO_ID;
  int health = 0, max_objs = 0, objects = 0, i;
  Player *player = NULL;
  Status status = OK;
  Space *init_space = NULL;/*save and load initial space */

  if (!game || !filename) return ERROR; /* error control */

  file = fopen(filename, "r");
  if (file == NULL) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#p:", line, 3) == 0) { /* identifies player lines */
      toks = strtok(line + 3, "|"); /* parses id */ 
      id = atol(toks);
      toks = strtok(NULL, "|");     /* name */
      strcpy(name, toks);
      toks = strtok(NULL, "|");     /* gdesc */
      strncpy(gdesc, toks, P_GDESC_SIZE - 1);
      gdesc[P_GDESC_SIZE - 1] = '\0';
      toks = strtok(NULL, "|");     /* location */
      location_id = atol(toks);
      toks = strtok(NULL, "|");     /* health */
      health = atoi(toks);
      toks = strtok(NULL, "|");     /* max_objs */
      max_objs = atoi(toks);
      toks = strtok(NULL, "|");     /* team */
      team = atol(toks);
      toks = strtok(NULL, "|");     /* objects */
      objects = atoi(toks);

      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_gdesc(player, gdesc);
        player_set_location(player, location_id);
        player_set_health(player, health);
        player_set_team(player, team);
        /*now the objects can be readed from the save file, so It has to be added to the backpack*/
        inventory_set_max_objs(player_get_backpack(player), max_objs);
        for (i = 0; i < objects; i++) {
          toks = strtok(NULL, "|");
          object_id = toks ? atol(toks) : NO_ID;
          if (object_id != NO_ID) {
            player_add_object(player, object_id);
          }
        }
        game_add_player(game, player);

        /*the same with the last space recorded in the file*/
        if (init_space == NULL) {
          init_space = game_get_space(game, location_id);
        }
        if (init_space != NULL) {
          space_set_discovered(init_space, TRUE); 
        }
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}


Status game_management_save(Game *game, char *filename) {
  FILE *file = NULL;
  Player *player = NULL;
  Space *space = NULL;
  Character *character = NULL;
  Object *object = NULL;
  Link *link = NULL;
  int i, j;

  if (!game || !filename) return ERROR; /* error control */

  file = fopen(filename, "w");
  if (file == NULL) return ERROR;

  /*PLAYERS*/
  if(game_get_num_players(game) < 0) return ERROR;

  for(i=0; i<game_get_num_players(game); i++) {
    player = game_get_player_by_index(game, i);
    if (player) {/*id name gdesc location health max_objs*/
      fprintf(file, "#p:%ld|%s|%s|%ld|%d|%d|%ld|%d|", player_get_id(player), player_get_name(player), player_get_gdesc(player), player_get_location(player), player_get_health(player), inventory_get_max_objs(player_get_backpack(player)), player_get_team(player), player_get_number_of_items_in_backpack(player));

      for(j=0; j < player_get_number_of_items_in_backpack(player); j++) {
        fprintf(file, "%ld|", player_get_object(player, j));
      }
      fprintf(file, "\n");
    }
  }
  
  fprintf(file, "\n");
  /*CHARACTERS*/
  if(game_get_num_characters(game) < 0) return ERROR;

  for(i=0; i < game_get_num_characters(game); i++){
    character = game_get_character_by_index(game,i);
    if (character) {/* parses id, name, gdesc, health, friendly, location, message and following */
      fprintf(file, "#c:%ld|%s|%s|%d|%d|%ld|%ld|%s|\n", 
        character_get_id(character),character_get_name(character),
        character_get_gdesc(character), character_get_health(character),
        character_is_friendly(character), game_get_character_location(game,character_get_id(character)),
        character_get_following(character), character_get_message(character));
    }
  }

  fprintf(file, "\n");
  /*OBJECTS*/
  if(game_get_num_objects(game) < 0) return ERROR;

  for(i=0; i < game_get_num_objects(game); i++){
    object = game_get_object_by_index(game,i);
    if (object) {/* parses id, name, gdesc, description, location, health, movable, dependency, open */
      fprintf(file, "#o:%ld|%s|%s|%s|%ld|%d|%d|%ld|%ld|\n", 
        object_get_id(object), object_get_name(object), 
        object_get_gdesc(object), object_get_description(object), 
        game_get_object_location(game,object_get_id(object)), 
        object_get_health(object), object_get_movable(object), 
        object_get_dependency(object), object_get_open(object));
    }
  }
    
  fprintf(file, "\n");
  /*SPACES*/
  if(game_get_num_spaces(game) < 0) return ERROR;

  for(i=0; i < game_get_num_spaces(game); i++){
    space = game_get_space_by_index(game,i);
    if (space) {/*id, name, discovered, gdesc*/
      fprintf(file, "#s:%ld|%s|%d|", space_get_id(space), space_get_name(space), space_get_discovered(space));
      for (j = 0; j < SPACE_GDESC_LINES; j++) {
        fprintf(file, "%s|", space_get_gdesc(space, j));
      }
      fprintf(file, "\n");
    } 
  } 

  fprintf(file, "\n");
  /*LINKS*/
  if(game_get_num_links(game) < 0) return ERROR;
    
    for(i=0; i < game_get_num_links(game); i++){
      link = game_get_link_by_index(game,i);
      if (link) {/* parses id, name, origin, destination, direction, open */
        fprintf(file,"#l:%ld|%s|%ld|%ld|%d|", 
          link_get_id(link), link_get_name(link), 
          link_get_origin(link), link_get_destination(link), 
          link_get_open(link));
        switch (link_get_direction(link)) {
          case N: fprintf(file, "N|\n"); break;
          case S: fprintf(file, "S|\n"); break;
          case E: fprintf(file, "E|\n"); break;
          case W: fprintf(file, "W|\n"); break;
          case U: fprintf(file, "U|\n"); break;
          case D: fprintf(file, "D|\n"); break;
          default: fprintf(file, "UNKNOWN|\n"); break;
        }
      }
    }
  fclose(file);     
  return OK;
}

Status game_management_load(Game *game, char *filename){
  FILE *file = NULL;

  if (!game || !filename) return ERROR; /* error control */
  
  file = fopen(filename, "r");
  if (file == NULL) return ERROR;
  fclose(file);

  if(game_clear(game) == ERROR) return ERROR; /* clears current game data */

  /* load new game data from file */
  if (game_management_load_spaces(game, filename) == ERROR) return ERROR;
  if (game_management_load_players(game, filename) == ERROR) return ERROR;
  if (game_management_load_characters(game, filename) == ERROR) return ERROR;
  if (game_management_load_objects(game, filename) == ERROR) return ERROR;
  if (game_management_load_links(game, filename) == ERROR) return ERROR;

  return OK;
}