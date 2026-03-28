/**
 * @brief It defines the game update interface
 *
 * @file game_actions.h
 * @author Jorge Garcia Garrido
 * @version 4
 * @date 16-03-2026
 * @copyright GNU Public License
 */

#ifndef GAME_ACTIONS_H
#define GAME_ACTIONS_H

#include "command.h"
#include "player.h"
#include "object.h"
#include "game.h"
#include "types.h"
#include "inventory.h"

/**
 * @brief It updates the game state according to the command introduced by the user
 * @author Jorge Garcia Garrido & Jose Miguel Romero Oubina
 
 *
 * @param game a pointer to the Game struct
 * @param cmd a pointer to the Command struct with the user input
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_actions_update(Game *game, Command *cmd);

#endif