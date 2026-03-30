/**
 *   It implements a textual graphic engine
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
#include <string.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "character.h"
#include "player.h"
#include "object.h"
#include "game.h"


#define WIDTH_MAP 55
#define WIDTH_DES 55
#define WIDTH_BAN 25
#define HEIGHT_MAP 30
#define HEIGHT_BAN 1
#define HEIGHT_HLP 3
#define HEIGHT_FDB 3
#define ROOM_WIDTH 15

struct _Graphic_engine {
  Area *map, *descript, *banner, *help, *feedback;
};

/*   It paints a row of three horizontally adjacent spaces centered on the given space */
static void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, Bool is_act);

/*   It builds a string with the names of all objects in a given space */
static Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);

/*   It creates a new Graphic_engine, allocating memory and initializing its members */
Graphic_engine *graphic_engine_create() {
  Graphic_engine *ge = NULL;

  screen_init(HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 4, WIDTH_MAP + WIDTH_DES + 3); /* initializes screen with total dimensions */
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) return NULL;

  /* initializes each display area with its position and dimensions */
  ge->map      = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP);
  ge->banner   = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + 2, WIDTH_BAN, HEIGHT_BAN);
  ge->help     = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + 2, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_BAN + HEIGHT_HLP + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);

  return ge;
}

/*   It paints a row of three horizontally adjacent spaces centered on the given space */
static void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, Bool is_act) {
  Space *west = NULL, *east = NULL;
  Character *character = NULL;
  const char *character_gdesc = NULL;
  const char *wg = NULL, *mg = NULL, *eg = NULL;
  char str[512], west_str[85], middle_str[85], east_str[85], obj_list[ROOM_WIDTH + 1];
  Status obj_list_status;
  int i;

  if (!area || !middle) return;

  west = game_get_space(game, game_get_connection(game, space_get_id(middle), W)); /* retrieves adjacent spaces */
  east = game_get_space(game, game_get_connection(game, space_get_id(middle), E));

  /* TOP LINE — cell width = 17 chars, empty = 17 chars */
  sprintf(str, "%s  +---------------+  %s",
      !west ? "                 " : "+---------------+",
      !east ? "                 " : "+---------------+");
  screen_area_puts(area, str);

  /* CHARACTER + ID LINE */
  if (!west) {
    sprintf(west_str, "                 ");
  } else {
    character = game_get_character_in_space(game, space_get_id(west));
    character_gdesc = !character ? "      " : character_get_gdesc(character);
    sprintf(west_str, "|     %s %3d|", character_gdesc, (int)space_get_id(west));
  }

  character = game_get_character_in_space(game, space_get_id(middle));
  character_gdesc = !character ? "      " : character_get_gdesc(character);
  sprintf(middle_str, "  | %s %s %3d|  ",
      is_act == TRUE ? "^C>" : "   ", /* marks the active space with an indicator */
      character_gdesc,
      (int)space_get_id(middle));

  if (!east) {
    sprintf(east_str, "                 ");
  } else {
    character = game_get_character_in_space(game, space_get_id(east));
    character_gdesc = !character ? "      " : character_get_gdesc(character);
    sprintf(east_str, "|     %s %3d|", character_gdesc, (int)space_get_id(east));
  }

  sprintf(str, "%s%s%s", west_str, middle_str, east_str);
  screen_area_puts(area, str);

  /* GDESC LINES — SPACE_GDESC_LINES rows of SPACE_GDESC_LENGTH chars */
  for (i = 0; i < SPACE_GDESC_LINES; i++) { /* prints each graphic description line for all three spaces */
    wg = (!west) ? NULL : space_get_gdesc(west,   i);
    mg =                  space_get_gdesc(middle, i);
    eg = (!east) ? NULL : space_get_gdesc(east,   i);

    if (!west) {
      sprintf(west_str, "                 ");
    } else {
      sprintf(west_str, "|%-9s      |", wg ? wg : "         ");
    }

    sprintf(middle_str, "  |%-9s      |  ", mg ? mg : "         ");

    if (!east) {
      sprintf(east_str, "                 ");
    } else {
      sprintf(east_str, "|%-9s      |", eg ? eg : "         ");
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);
  }

  /* OBJECTS + ARROWS LINE */
  if (!west) {
    sprintf(west_str, "                 ");
  } else {
    obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
    sprintf(west_str, "|%s|", obj_list_status == ERROR ? "               " : obj_list);
  }

  obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);
  sprintf(middle_str, " %s|%s|%s ",
      west ? "<" : " ", /* shows navigation arrows if adjacent spaces exist */
      obj_list_status == ERROR ? "               " : obj_list,
      east ? ">" : " ");

  if (!east) {
    sprintf(east_str, "                 ");
  } else {
    obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
    sprintf(east_str, "|%s|", obj_list_status == ERROR ? "               " : obj_list);
  }

  sprintf(str, "%s%s%s", west_str, middle_str, east_str);
  screen_area_puts(area, str);

  /* BOTTOM LINE */
  sprintf(str, "%s  +---------------+  %s",
      !west ? "                 " : "+---------------+",
      !east ? "                 " : "+---------------+");
  screen_area_puts(area, str);
}

/*   It builds a string with the names of all objects in a given space */
static Status graphic_engine_get_objects_str(Game *game, Space *space, char *str) {
  Id *n = NULL;
  int i, cont;
  char car[ROOM_WIDTH + 1];

  car[0] = '\0';

  if (!game || !space || !str) return ERROR;

  n = space_get_objects(space);
  if (!n) return ERROR;

  cont = space_get_number_of_objects(space);
  if (cont <= 0) return ERROR;

  for (i = 0; i < cont; i++) { /* concatenates object names into a single string */
    Object *obj = game_get_object(game, n[i]);
    if (!obj) continue;
    if (strlen(car) + strlen(object_get_name(obj)) < (size_t)ROOM_WIDTH)
      strcat(car, object_get_name(obj));
    if (i < cont - 1) strcat(car, ", ");
  }

  while ((int)strlen(car) < 15) strcat(car, " "); /* pads string to fixed width */
  strcpy(str, car);
  return OK;
}

/*   It destroys a Graphic_engine, freeing the allocated memory */
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  /* destroys each display area */
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/*   It renders the current state of the game on screen */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_top = NO_ID, id_next = NO_ID;
  Id obj_loc = NO_ID, char_loc = NO_ID;
  Space *act = NULL;
  char str[512];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  Player *player = NULL;
  Character *character = NULL;
  Object *obj = NULL;

  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0;
  char obj_line[512];

  if (!ge || !game) return;

  /* 1. MAP AREA */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    act = game_get_space(game, id_act);
    if (!act) return;

    id_back = game_get_connection(game, space_get_id(act), N); /* retrieves north and south neighbours */
    id_next = game_get_connection(game, space_get_id(act), S);

    /* paints up to three rows of spaces depending on available neighbours */
    if (id_next == NO_ID && id_back != NO_ID) {
      id_top = game_get_connection(game, id_back, N);
      if (id_top != NO_ID) {
        graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_top), FALSE);
        screen_area_puts(ge->map, " ");
      }
    }

    if (id_back != NO_ID) {
      graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE);
      screen_area_puts(ge->map, "                           ^");
    }

    graphic_engine_paint_spaces_row(ge->map, game, act, TRUE); /* paints active space */

    if (id_next != NO_ID) {
      screen_area_puts(ge->map, "                           v");
      graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
    }

    if (id_back == NO_ID && id_next != NO_ID) {
      id_next = game_get_connection(game, id_next, S);
      if (id_next != NO_ID) {
        screen_area_puts(ge->map, " ");
        graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE);
      }
    }
  }

  /* 2. DESCRIPTION AREA */
  screen_area_clear(ge->descript);

  /* Objects — prints each object name and its location */
  screen_area_puts(ge->descript, " Objects:");
  for (i = 0; i < MAX_OBJECTS; i++) {
    obj = game_get_object_by_index(game, i);
    if (!obj) break;
    obj_loc = game_get_object_location(game, object_get_id(obj));
    sprintf(str, "  %-10s: %d", object_get_name(obj), (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }
  screen_area_puts(ge->descript, " ");

  /* Characters — prints each character name, location and health */
  screen_area_puts(ge->descript, " Characters:");
  for (i = 0; i < MAX_CHARACTERS; i++) {
    character = game_get_character_by_index(game, i);
    if (!character) break;
    char_loc = game_get_character_location(game, character_get_id(character));
    if (char_loc != NO_ID) {
      int health = character_get_health(character);
      if (health > 0)
        sprintf(str, "  %-10s: %d (%d hp)", character_get_name(character), (int)char_loc, health);
      else
        sprintf(str, "  %-10s: %d (DEAD)", character_get_name(character), (int)char_loc);
      screen_area_puts(ge->descript, str);
    }
  }
  screen_area_puts(ge->descript, " ");

  /* Player — prints location, health and carried object */
  player = game_get_player(game);
  sprintf(str, " Player: %d (%d hp)", (int)player_get_location(player), player_get_health(player));
  screen_area_puts(ge->descript, str);

  inv_set = inventory_get_objects(player_get_backpack(player));
  if(inv_set != NULL){/*gets number of objects in inventory */
    n = set_get_n_ids(inv_set);
  }else{
    n = 0;/*no objects in inventory */
  }

  if (n <= 0) {
    screen_area_puts(ge->descript, " Player has no objects");
  } else {
    ids = set_get_ids(inv_set);
    strcpy(obj_line, " Player has:");
    for (i = 0; i < n; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj) {
        strcat(obj_line, " ");
        strcat(obj_line, object_get_name(obj));
        if (i < n - 1) strcat(obj_line, ",");
      }
    }
    screen_area_puts(ge->descript, obj_line);
  }

  /* Chat message — displays and clears last message if present */
  screen_area_puts(ge->descript, " ");
  if (game_get_last_message(game) && game_get_last_message(game)[0] != '\0') {
    sprintf(str, " Message: %s", game_get_last_message(game));
    screen_area_puts(ge->descript, str);
    game_set_last_message(game, ""); /* clears message after displaying */
  }

  /* 3. BANNER */
  screen_area_puts(ge->banner, " The haunted castle game ");

  /* 4. HELP — lists all available commands */
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " The commands you can use are:");
  screen_area_puts(ge->help, "  next or n, back or b, left or l, right or r, take or t, drop or d, attack or a, chat or c, exit or e");

  /* 5. FEEDBACK — shows last command and its result status */
  screen_area_clear(ge->feedback);
  last_cmd = command_get_code(game_get_last_command(game));
  sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd - NO_CMD][CMDL], cmd_to_str[last_cmd - NO_CMD][CMDS], game_get_last_status(game) == OK ? "OK" : "ERROR");
  screen_area_puts(ge->feedback, str);

  /* 6. Render */
  screen_paint(BLACK);
  printf("prompt:> ");
}