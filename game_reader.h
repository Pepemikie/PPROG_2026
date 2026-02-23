/**
 * @brief It defines the game reader interpreter interface
 *
 * @file game_reader.h
 * @author Abraham Darkal García & Jose Miguel Romero Oubina
 * @version 1
 * @date 04-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_READER_H
#define GAME_READER_H

#include "game.h"

/**
 * @brief Reads the spaces from a file, 
 * creates each space with its name and connections, and adds them to the game
 * @param Game struct for the directions
 * @param filename is use to open the file
 * @return status if everything is alright or ERROR if is there any problem
 */
Status game_load_spaces(Game *game, char *filename);

#endif
