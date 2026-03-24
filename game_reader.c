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
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
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
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);

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
      printf("Leidos:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif

      space = space_create(id);
      if (space != NULL) { /* sets all space attributes and adds it to the game */
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
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