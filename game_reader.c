/**
 * @brief It implements the game reader structure
 *
 * @file game_reader.c
 * @author Abraham Darkal García & Jose Miguel Romero Oubina
 * @version 1
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game_reader.h"

/*Reads the spaces from a file, creates each space with its name and connections, and adds them to the game.*/
Status game_load_spaces(Game *game, char *filename) {
  /* Variables to store file data, parsed tokens, space properties, and the created space */
  FILE *file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char *toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space *space = NULL;
  Status status = OK;

  if (!filename) {
    return ERROR;
  }
/* Opens the spaces file in read mode */
  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }
/* Reads the file line by line */
  while (fgets(line, WORD_SIZE, file)) {
    /* Checks if the line contains space data (lines starting with "#s:") */
    if (strncmp("#s:", line, 3) == 0) {
      /* Extracts the space ID from the line */
      toks = strtok(line + 3, "|");
      id = atol(toks);
      /* Extracts and stores the space name */
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      /* Extracts the IDs of the connected spaces in each direction */
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
#ifdef DEBUG
      printf("Leidos:%ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);
#endif
/* Creates a new space with the given ID */
      space = space_create(id);
      if (space != NULL) {
        /* Sets the space name and its directional connections */
        space_set_name(space, name);
        space_set_north(space, north);
        space_set_east(space, east);
        space_set_south(space, south);
        space_set_west(space, west);
        /* Adds the created space to the game */
        game_add_space(game, space);
      }
    }
  }
/* Checks if an error occurred while reading the file */
  if (ferror(file)) {
    status = ERROR;
  }
  
/* Closes the file after reading */
  fclose(file);

  return status;
}