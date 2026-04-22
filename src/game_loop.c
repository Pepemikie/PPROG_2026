/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @copyright GNU Public License
 */


#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "graphic_engine.h"

/** @brief Global file pointer for logging */
FILE *g_logfile = NULL;

/** @brief PID of the aplay process for cleanup */

static pid_t music_pid = -1;
static volatile int music_running = 1; /* añade esta variable */

static void *music_thread(void *arg) {
    char *aplay_args[] = {"aplay", "./Main_Theme_1.wav", NULL};
    (void)arg;

    while (music_running) {   /*comprueba la variable en cada iteración */ 
        music_pid = fork();
        if (music_pid == 0) {
            int devnull = open("/dev/null", O_WRONLY);
            dup2(devnull, STDOUT_FILENO);
            dup2(devnull, STDERR_FILENO);
            close(devnull);
            execv("/usr/bin/aplay", aplay_args);
            exit(1);
        } else if (music_pid > 0) {
            waitpid(music_pid, NULL, 0);
        }
    }
    return NULL;
}

static void music_stop(void) {
    music_running = 0;  /* para el bucle primero */
    if (music_pid > 0) {
        kill(music_pid, SIGTERM);
        waitpid(music_pid, NULL, 0);
        music_pid = -1;
    }
}

/**
 * @brief It initializes the game and the graphic engine from a data file
 *
 * @param game a double pointer to the Game struct to be initialized
 * @param gengine a double pointer to the Graphic_engine struct to be initialized
 * @param file_name a string with the path to the game data file
 * @return 0 on success, 1 if game initialization failed, 2 if graphic engine creation failed
 */
int game_loop_init(Game **game, Graphic_engine **gengine, char *file_name);

/**
 * @brief It frees the memory used by the game and the graphic engine
 *
 * @param game a pointer to the Game struct to be destroyed
 * @param gengine a pointer to the Graphic_engine struct to be destroyed
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine);

/**
 * @brief It runs the main game loop, processing input and updating the game state each iteration
 *
 * @param argc number of command-line arguments
 * @param argv array of command-line argument strings
 * @return 0 on success, 1 on error
 */
int main(int argc, char *argv[]) {
  Game *game = NULL; 
  Graphic_engine *gengine = NULL;
  Command *last_cmd = NULL;
  int result;
  char *logfile = NULL;
  char *datafile = NULL;
  int i;

  pthread_t music_tid;
  pthread_attr_t music_attr;

  srand(time(NULL)); /* initializes random seed */

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-l") == 0 && i + 1 < argc) {
      logfile = argv[i + 1];
      i++;  /* skip the logfile argument */
    } else if (datafile == NULL) {
      datafile = argv[i];
    } else {
      fprintf(stderr, "Use: %s [-l logfile] <game_data_file>\n", argv[0]);
      return 1;
    }
  }

  if (datafile == NULL) {
    fprintf(stderr, "Use: %s [-l logfile] <game_data_file>\n", argv[0]);
    return 1;
  }

  if (logfile) {
    g_logfile = fopen(logfile, "w");
    if (g_logfile == NULL) {
      fprintf(stderr, "Error opening log file %s\n", logfile);
      return 1;
    }
  }
  /* Pasamos la dirección del puntero para que se asigne memoria dentro */
  result = game_loop_init(&game, &gengine, datafile);
  if (result == 1) {
    fprintf(stderr, "Error while initializing game.\n");
    return 1;
  } else if (result == 2){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    return 1;
  }

  pthread_attr_init(&music_attr);
  pthread_attr_setdetachstate(&music_attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&music_tid, &music_attr, music_thread, NULL); /* start music thread */

  /* Como 'game' ya es puntero, le quitamos el '&' en todas las llamadas */
  last_cmd = game_get_last_command(game);
  while ((command_get_code(last_cmd) != EXIT) && (game_get_finished(game) == FALSE)) { /* main loop: runs until EXIT or game finished */
    graphic_engine_paint_game(gengine, game); /* renders current game state */
    command_get_user_input(last_cmd); /* reads user input */
    game_actions_update(game, last_cmd); /* updates game according to input */
    graphic_engine_paint_game(gengine, game); /* shows result before turn change (F13, I3) */
    sleep(2);                                 /* waits 2 seconds before next player (F13, I3) */
    game_next_turn(game);                /* changes player's turn. Multiplayer (F11, I3) */
    last_cmd = game_get_last_command(game); /* actualizamos al final de cada iteración */
  }
  /*graphic_engine_paint_game(gengine, game);*/
  game_loop_cleanup(game, gengine); /* frees all resources */
  if (g_logfile) {
    fclose(g_logfile);
    g_logfile = NULL;
  }
  return 0;
}

/**
 * @brief It initializes the game and the graphic engine from a data file
 *
 * @param game a double pointer to the Game struct to be initialized
 * @param gengine a double pointer to the Graphic_engine struct to be initialized
 * @param file_name a string with the path to the game data file
 * @return 0 on success, 1 if game initialization failed, 2 if graphic engine creation failed
 */
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

/**
 * @brief It frees the memory used by the game and the graphic engine
 *
 * @param game a pointer to the Game struct to be destroyed
 * @param gengine a pointer to the Graphic_engine struct to be destroyed
 */
void game_loop_cleanup(Game *game, Graphic_engine *gengine) {
  music_stop(); /* stops background music */
  if (game) {
    game_destroy(game); /* destroys game and frees its memory */
  }
  if (gengine) {
    graphic_engine_destroy(gengine); /* destroys graphic engine and frees its memory */
  }
}