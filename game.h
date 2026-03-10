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
#include "character.h"
#include "game_reader.h"


#define MAX_SPACES 100
#define MAX_OBJECTS 5
#define MAX_CHARACTERS 2

typedef struct _Game Game;




Game* game_create();

Status game_create_from_file(Game *game, char *filename);

Status game_destroy(Game *game);

Space *game_get_space(Game *game, Id id);

Player *game_get_player(Game *game);

Object* game_get_object(Game* game, Id id);

Id game_get_player_location(Game *game);

Status game_set_player_location(Game *game, Id id);

Id game_get_object_location(Game *game);

Status game_set_object_location(Game *game, Id space_id, Id object_id);

Command* game_get_last_command(Game *game);

Status game_set_last_command(Game *game, Command *command);

Bool game_get_finished(Game *game);

Status game_set_finished(Game *game, Bool finished);

void game_print(Game *game);

Status game_add_space(Game *game, Space *space);

Status game_set_player_character(Game *game, Id id);

Id game_get_object_character(Game *game);

Status game_add_object(Game *game, Object *object);

Character* game_get_character_in_space(Game* game, Id space_id);


Status game_set_last_message(Game* game, const char* message);





#endif
