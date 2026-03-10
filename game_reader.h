#ifndef GAME_READER_H
#define GAME_READER_H

#include "types.h"

typedef struct _Game Game;

Status game_load_spaces(Game *game, char *filename);
Status game_load_objects(Game *game, char *filename);

#endif