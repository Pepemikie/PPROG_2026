/**
 * @brief It implements a textual graphic engine
 *
 * @file graphic_engine.c
 * @author Profesores PPROG
 * @version 0
 * @date 24-01-2026
 * @copyright GNU Public License
 */

#include "graphic_engine.h"

#include <stdio.h>
#include <stdlib.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "player.h"
#include "types.h"

#define WIDTH_MAP 60
#define WIDTH_DES 29
#define WIDTH_BAN 25
#define HEIGHT_MAP 13
#define HEIGHT_BAN 1
#define HEIGHT_HLP 2
#define HEIGHT_FDB 3

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

Graphic_engine *graphic_engine_create() {
  static Graphic_engine *ge = NULL;

  if (ge) {
    return ge;
  }

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3);
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) {
    return NULL;
  }

  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID,id_east = NO_ID, id_west = NO_ID, obj_loc = NO_ID;
  Space *space_act = NULL;
  char obj = '\0';
  char str[255];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];

  /* Paint the in the map area */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);
    id_east = space_get_east(space_act);
    id_west = space_get_west(space_act);
    obj_loc = game_get_object_location(game);

    if (game_get_object_location(game) == id_back)
      obj = '+';
    else
      obj = ' ';

    if (id_back != NO_ID) {
      sprintf(str, "                      |         %2d|", (int)id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "                      |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "                      +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                            ^");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game) == id_act)
      obj = '+';
    else
      obj = ' ';

    if (id_act != NO_ID) {
      char obj_west = ' ';
      char obj_east = ' ';
      if (game_get_object_location(game) == id_west)
        obj_west = '+';
      if (game_get_object_location(game) == id_east)
        obj_east = '+';

      /* If there is a west neighbor -> draw west then center */
      if (id_west != NO_ID) {
        sprintf(str, "  +-----------+       +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "  |       %2d |   <   | ^C>     %2d|", (int)id_west, (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "  |     %c     |       |     %c     |", obj_west, (game_get_object_location(game) == id_act) ? '+' : ' ');
        screen_area_puts(ge->map, str);
        sprintf(str, "  +-----------+       +-----------+");
        screen_area_puts(ge->map, str);
      }
      /* else if there is an east neighbor -> draw center then east */
      else if (id_east != NO_ID) {
        sprintf(str, "                      +-----------+       +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                      | ^C>     %2d|   >   |        %2d|", (int)id_act, (int)id_east);
        screen_area_puts(ge->map, str);
        sprintf(str, "                      |     %c     |       |     %c     |", (game_get_object_location(game) == id_act) ? '+' : ' ', obj_east);
        screen_area_puts(ge->map, str);
        sprintf(str, "                      +-----------+       +-----------+");
        screen_area_puts(ge->map, str);
      }
      /* else only center */
      else {
        sprintf(str, "                      +-----------+");
        screen_area_puts(ge->map, str);
        sprintf(str, "                      | ^C>     %2d|", (int)id_act);
        screen_area_puts(ge->map, str);
        sprintf(str, "                      |     %c     |", (game_get_object_location(game) == id_act) ? '+' : ' ');
        screen_area_puts(ge->map, str);
        sprintf(str, "                      +-----------+");
        screen_area_puts(ge->map, str);
      }
    }

    if (game_get_object_location(game) == id_next)
      obj = '+';
    else
      obj = ' ';

    if (id_next != NO_ID) {
      sprintf(str, "                            v");
      screen_area_puts(ge->map, str);
      sprintf(str, "                      +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "                      |         %2d|", (int)id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "                      |     %c     |", obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "                      +-----------+       ");
      screen_area_puts(ge->map, str);
    }
    /* west handled with center above */
  }

  /* Paint in the description area */
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game)) != NO_ID) {
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }

  /* Paint in the banner area */
  screen_area_puts(ge->banner, " The haunted castle game ");

 
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, "  The commands you can use are:");
  screen_area_puts(ge->help, "  next (n), back (b), take (t), drop (d), exit (e)");

  /* 2. Limpiar y pintar el área de descripción (DESCRIPT) */
  
  screen_area_clear(ge->descript); 
  if (player_get_object(game_get_player(game)) != NO_ID) {
    screen_area_puts(ge->descript, "  Object location: player has it");
  } else if (obj_loc != NO_ID) {
    sprintf(str, "  Object location: %d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  } else {
    screen_area_puts(ge->descript, "  Object: not available");
  }

  /* 3. Limpiar y pintar el área de feedback (donde sale el último comando) */
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, "  %s (%s)", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS]);
  screen_area_puts(ge->feedback, str);

  /* 4. Dibujar todo en la terminal */
  screen_paint();
  printf("prompt:> ");
}
