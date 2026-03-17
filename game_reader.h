/**
 * @brief It defines the game reader interface
 *
 * @file game_reader.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 12-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief It reads the spaces from a file, creates each space with its name and connections, and adds them to the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param filename a string with the name of the file to read from
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_spaces(Game *game, char *filename);

/**
 * @brief It reads the objects from a file, creates each object with its name and id, and adds them to the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param filename a string with the name of the file to read from
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_objects(Game *game, char *filename);

/**
 * @brief It reads the characters from a file, creates each character with its name, description and other attributes, and adds them to the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param filename a string with the name of the file to read from
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_reader_load_characters(Game *game, char *filename);

#endif