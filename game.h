/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "object.h"
#include "player.h"
#include "command.h"
#include "space.h"
#include "types.h"


#define MAX_SPACES 100

typedef struct _Game Game;




Game* game_create();

Status game_create_from_file(Game *game, char *filename);

Status game_destroy(Game *game);

Space *game_get_space(Game *game, Id id);

Player *game_get_player(Game *game);

Object* game_get_object(Game* game);

Id game_get_player_location(Game *game);

Status game_set_player_location(Game *game, Id id);

Id game_get_object_location(Game *game);

Status game_set_object_location(Game *game, Id id);

Command* game_get_last_command(Game *game);

Status game_set_last_command(Game *game, Command *command);

Bool game_get_finished(Game *game);

Status game_set_finished(Game *game, Bool finished);

void game_print(Game *game);

Status game_add_space(Game *game, Space *space);

#endif
