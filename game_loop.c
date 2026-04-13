/**
 *   It defines the game loop
 *
 * @file game_loop.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @copyright GNU Public License
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/* Prototipos actualizados para usar punteros */

/**
 *   It initializes the game and the graphic engine from a data file
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 *   It frees the memory used by the game and the graphic engine
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/*   It runs the main game loop, processing input and updating the game state each iteration */
int main(int argc, char *argv[]) {
  Game *game = NULL; 
  Graphic_engine *gengine = NULL;
  Command *last_cmd = NULL;
  int result;
  char *data_file = NULL;
  char *log_file = NULL;
  srand(time(NULL)); /* initializes random seed */
  
  /* Parse command line arguments */
  if (argc == 2) {
    data_file = argv[1];
  } else if (argc == 4 && strcmp(argv[2], "-l") == 0) {
    data_file = argv[1];
    log_file = argv[3];
  } else {
    fprintf(stderr, "Use: %s <game_data_file> [-l <log_file>]\n", argv[0]);
    return 1;
  }
  
  /* Redirect output to log file if specified */
  if (log_file != NULL) {
    if (freopen(log_file, "w", stdout) == NULL) {
      fprintf(stderr, "Error opening log file: %s\n", log_file);
      return 1;
    }
    if (freopen(log_file, "w", stderr) == NULL) {
      fprintf(stderr, "Error opening log file for stderr: %s\n", log_file);
      return 1;
    }
  }
  
  /* Pasamos la dirección del puntero para que se asigne memoria dentro */
  result = game_loop_init(&game, &gengine, data_file);
  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }
  /* Como 'game' ya es puntero, le quitamos el '&' en todas las llamadas */
  last_cmd = game_get_last_command(game);
  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) { /* main loop: runs until EXIT or game finished */
    graphic_engine_paint_game(gengine, game); /* renders current game state */
    command_get_user_input(last_cmd); /* reads user input */
    game_actions_update(game, last_cmd); /* updates game according to input */
    last_cmd = game_get_last_command(game); /* actualizamos al final de cada iteración */
  }
  graphic_engine_paint_game(gengine, game);
  game_loop_cleanup(game, gengine); /* frees all resources */
  return 0;
}

/*   It initializes the game and the graphic engine from a data file */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name) {
  /* ARREGLO F1: Creamos el objeto dinámicamente */
  *game = game_create(); 
  if (*game == NULL) return 1; /* error control */
  if (game_create_from_file(*game, file_name) == ERROR) {
    game_destroy(*game);
    return 1;
  }
  if ((*gengine = graphic_engine_create()) == NULL) { /* error control: graphic engine creation failed */
    game_destroy(*game);
    return 2;
  }
  return 0;
}

/*   It frees the memory used by the game and the graphic engine */
/* ARREGLO F1: Ahora recibe un puntero simple Game* */
void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  if (game) {
    game_destroy(game); /* destroys game and frees its memory */
  }
  if (gengine) {
    graphic_engine_destroy(gengine); /* destroys graphic engine and frees its memory */
  }
}