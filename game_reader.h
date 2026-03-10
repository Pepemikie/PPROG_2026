/**
 * @brief It defines the game reader interface
 *
 * @file game_reader.h
 * @author Equipo 
 * @version 1
 * @date 04-02-2025
 * @copyright GNU Public License
 */

 #ifndef GAME_READER_H
 #define GAME_READER_H
 
 #include "game.h"
 #include "game.h"
 #include "types.h"
 #include "space.h"
 #include "command.h"

 
 /**
  * @brief It loads the objects of the game from a file and initializes them with their respective attributes
  * @author Farly Posso
  *
  * @param game pointer to the game structure to which the spaces will be added
  * @param filename the name of the file containing the game spaces data
  * @return OK, if everything goes well or ERROR if there was some mistake
  */
 Status game_reader_load_spaces(Game *game, char *filename);

 #endif