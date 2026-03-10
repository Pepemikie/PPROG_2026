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
#include "player.h"
#include "object.h"
#include "game.h"
#include "types.h"

/**
 * @brief Updates the action choosed by the user, it checks the command and calls the corresponding function to update the game
 * @author Jorge Garcia Garrido
 *
 * @param game   : pointer to an existing Game struct pointer
 * @param cmd   : pointer to an existing Command struct pointer
 * @return Status : OK
 */
Status game_actions_update(Game *game, Command *cmd);

#endif
