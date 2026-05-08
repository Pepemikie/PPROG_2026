/**
 * @brief It defines the game rules interface
 *
 * @file game_rules.h
 * @author Rodrigo Cruz Asensio
 * @version 1
 * @date 08-05-2026
 * @copyright GNU Public License
 */

#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"

/**
 * @brief It executes the non-deterministic game rules and random events
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * 
 * This function is called once per turn to apply automatic
 * random events and game rules.
 */
void game_rules_update(Game *game);

#endif