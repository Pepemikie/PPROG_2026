/**
 * @brief It defines the game update interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "game.h"
#include "types.h"

/**
* @brief Checks the command code and calls the corresponding action function to update the game.
*
*@author Jose Miguel Romero Oubina
*@param Game struct
*@param Command struct
*@return OK
*/
Status game_actions_update(Game *game, Command *cmd);

#endif
