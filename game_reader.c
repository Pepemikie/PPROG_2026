/**
 *   It implements the game_reader interpreter
 *
 * @file game_reader.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 12-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_reader.h"
#include "game.h"
#include "space.h"
#include "object.h"
#include "character.h"

/*   It reads the spaces from a file, creates each space with its name and connections, and adds them to the game */
Status game_reader_load_spaces(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1];
  char *toks = NULL;
  Id id = NO_ID;
  Space *space = NULL;
  Status status = OK;
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
      toks = strtok(NULL, "|"); /* north */
      toks = strtok(NULL, "|"); /* east */
      toks = strtok(NULL, "|"); /* south */
      toks = strtok(NULL, "|"); /* west */

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
      printf("Leidos:%ld|%s\n", id, name);
#endif

      space = space_create(id);
      if (space != NULL) { /* sets all space attributes and adds it to the game */
        space_set_name(space, name);
        space_set_gdesc(space, gdesc);
        game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/*   It reads the objects from a file, creates each object with its name and id, and adds them to the game */
Status game_reader_load_objects(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, space_id = NO_ID;
  Object *obj = NULL;
  Status status = OK;

  if (!game || !filename) return ERROR; /* error control */

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) { /* identifies object lines */
      toks = strtok(line + 3, "|"); /* parses id, name and location */
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      space_id = atol(toks);
#ifdef DEBUG
      printf("Leido: o:%ld|%s|%ld\n", id, name, space_id);
#endif
      if ((obj = object_create(id))) { /* sets object attributes and places it in the game */
        object_set_name(obj, name);
        game_add_object(game, obj);
        game_set_object_location(game, space_id, id);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/*   It reads the characters from a file, creates each character with its name, description and other attributes, and adds them to the game */
Status game_reader_load_characters(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[GDESC_SIZE] = "";
  char message[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location_id = NO_ID;
  int health = 0;
  int friendly = 0;
  Character *character = NULL;
  Status status = OK;

  if (!game || !filename) return ERROR; /* error control */

  if (!(file = fopen(filename, "r"))) return ERROR;

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#c:", line, 3) == 0) { /* identifies character lines */
      toks = strtok(line + 3, "|"); /* parses id, name, gdesc, health, friendly, location and message */
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
      location_id = atol(toks);
      toks = strtok(NULL, "|");
      if (toks) {
        strncpy(message, toks, WORD_SIZE - 1);
        message[WORD_SIZE - 1] = '\0';
      }
#ifdef DEBUG
      printf("Leido: c:%ld|%s|%s|%d|%d|%ld|%s\n", id, name, gdesc, health, friendly, location_id, message);
#endif
      if ((character = character_create(id))) { /* sets all character attributes and places it in the game */
        character_set_name(character, name);
        character_set_gdesc(character, gdesc);
        character_set_health(character, health);
        character_set_friendly(character, (Bool)friendly);
        game_set_character_location(game, location_id, id);
        character_set_message(character, message);
        game_add_character(game, character);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/*   It reads the links from a file, creates each link with its attributes, and adds them to the game */
Status game_reader_load_links(Game *game, char *filename) {
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
      toks = strtok(line + 3, "|"); /* parses id, name, origin, destination, direction, open */
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      origin = atol(toks);
      toks = strtok(NULL, "|");
      destination = atol(toks);
      toks = strtok(NULL, "|");
      if (strcmp(toks, "N") == 0)
      direction = N;
      else if (strcmp(toks, "S") == 0)
      direction = S;
      else if (strcmp(toks, "E") == 0)
      direction = E;
      else if (strcmp(toks, "W") == 0)
      direction = W;
      else
      direction = UNKNOWN_DIR;
      toks = strtok(NULL, "|");
      open = (Bool)atoi(toks);
#ifdef DEBUG
      printf("Leido: l:%ld|%s|%ld|%ld|%d|%d\n", id, name, origin, destination, direction, open);
#endif
      if ((link = link_create(id))) { /* sets all link attributes and adds it to the game */
        link_set_name(link, name);
        link_set_origin(link, origin);
        link_set_destination(link, destination);
        link_set_direction(link, direction);
        link_set_open(link, open);
        game_add_link(game, link);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}

/* It reads the players from a file, creates each player and adds them to the game. Multiplayer (F11, I3) */
Status game_reader_load_players(Game *game, char *filename) {
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char gdesc[P_GDESC_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, location_id = NO_ID;
  int health = 0, max_objs = 0;
  Player *player = NULL;
  Status status = OK;

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

      player = player_create(id);
      if (player != NULL) {
        player_set_name(player, name);
        player_set_gdesc(player, gdesc);
        player_set_location(player, location_id);
        player_set_health(player, health);
        player_set_max_objs(player, max_objs);      /* sets backpack size from file */
        game_add_player(game, player);
      }
    }
  }

  if (ferror(file)) status = ERROR;

  fclose(file);
  return status;
}