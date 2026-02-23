/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/* Prototipos actualizados para usar punteros */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

int main(int argc, char *argv[]) {
  /* ARREGLO F1: Game ahora es un puntero */
  Game *game = NULL; 
  Graphic_engine *gengine = NULL;
  Command *last_cmd = NULL;
  int result;

  if (argc < 2) {
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);
    return 1;
  }

  /* Pasamos la dirección del puntero para que se asigne memoria dentro */
  result = game_loop_init(&game, &gengine, argv[1]);

  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  /* Como 'game' ya es puntero, le quitamos el '&' en todas las llamadas */
  last_cmd = game_get_last_command(game);

  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) {
    graphic_engine_paint_game(gengine, game);
    command_get_user_input(last_cmd);
    game_actions_update(game, last_cmd);
  }

  game_loop_cleanup(game, gengine);

  return 0;
}

int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  /* ARREGLO F1: Creamos el objeto dinámicamente */
  *game = game_create(); 
  if (*game == NULL) return 1;

  if (game_create_from_file(*game, file_name) == ERROR) {
    return 1;
  }

  if ((*gengine = graphic_engine_create()) == NULL) {
    game_destroy(*game);
    return 2;
  }

  return 0;
}

/* ARREGLO F1: Ahora recibe un puntero simple Game* */
void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  if (game) {
    game_destroy(game);
  }
  if (gengine) {
    graphic_engine_destroy(gengine);
  }
}