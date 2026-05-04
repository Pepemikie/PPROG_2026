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

/** @brief Width of the map area */
#define WIDTH_MAP 95 
/** @brief Width of the description area */
#define WIDTH_DES 65
/** @brief Width of the banner area */
#define WIDTH_BAN 25
/** @brief Height of the map area */
#define HEIGHT_MAP 40
/** @brief Height of the banner area */
#define HEIGHT_BAN 1
/** @brief Height of the help area */
#define HEIGHT_HLP 3
/** @brief Height of the feedback area */
#define HEIGHT_FDB 3
/** @brief Width of each room in the map */
#define ROOM_WIDTH 15

/** @brief Structure representing the graphic engine */
struct _Graphic_engine {
  Area *map, /**< Map area */
   *descript, /**< Description area */
   *banner, /**< Banner area */
   *help, /**< Help area */
   *feedback; /**< Feedback area */
};

/**
 * @brief It paints a row of three horizontally adjacent spaces centered on the given space.
 *        If show_sides is FALSE, west and east neighbours are not rendered
 * @param area a pointer to the Area where the spaces will be rendered
 * @param game a pointer to the Game struct
 * @param middle a pointer to the Space struct that will be rendered in the middle of the row
 * @param is_act a Bool indicating whether the middle space is the active space (where the player is located), which will be marked with the player's gdesc
 * @param show_sides a Bool indicating whether to render the west and east neighbours of the middle space (if FALSE, they will be treated as absent and rendered as blank columns)
 */
static void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, Bool is_act, Bool show_sides);

/*   It builds a string with the names of all objects in a given space */
/**
 * @brief It builds a string with the names of all objects in a given space
 * @param game a pointer to the Game struct
 * @param space a pointer to the Space struct
 * @param str a pointer to the character array where the string will be stored
 * @return Status of the operation
 */
static Status graphic_engine_get_objects_str(Game *game, Space *space, char *str);
/**
 * @brief It builds a string with the names of all characters in a given space
 * @param game a pointer to the Game struct
 * @param space a pointer to the Space struct
 * @param str a pointer to the character array where the string will be stored
 * @return Status of the operation
 */
static Status graphic_engine_get_characters_str(Game *game, Space *space, char *str);

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

/*   It paints a row of three horizontally adjacent spaces centered on the given space.
 *   If show_sides is FALSE, west and east neighbours are not rendered (treated as absent). */
static void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, Bool is_act, Bool show_sides) {
  Space *west = NULL, *east = NULL;
  Player *active_player = NULL;
  const char *active_player_gdesc = "   ";
  const char *wg = NULL, *mg = NULL, *eg = NULL;
  char str[512], west_str[128], middle_str[128], east_str[128];
  char obj_list[ROOM_WIDTH + 1], char_list[ROOM_WIDTH + 1];
  Status obj_list_status, char_list_status;
  int i;
  Bool west_discovered = FALSE, middle_discovered = FALSE, east_discovered = FALSE;

  if (!area || !middle) return;

  if (show_sides == TRUE) {
    west = game_get_space(game, game_get_connection(game, space_get_id(middle), W));
    east = game_get_space(game, game_get_connection(game, space_get_id(middle), E));
  }

  middle_discovered = space_get_discovered(middle);
  if (west) west_discovered = space_get_discovered(west);
  if (east) east_discovered = space_get_discovered(east);

  /* TOP LINE*/
  sprintf(str, "%s  +-------------------------+  %s",
      !west ? "                           " : "+-------------------------+",
      !east ? "                           " : "+-------------------------+");
  screen_area_puts(area, str);

  /* CHARACTER + ID LINE*/
  if (!west) {
    sprintf(west_str, "                           ");
  } else {
    if (west_discovered == TRUE) {
      char_list_status = graphic_engine_get_characters_str(game, west, char_list);
    } else {
      char_list_status = ERROR;
    }
    sprintf(west_str, "| %-15s      %3d|",
        char_list_status == ERROR ? "               " : char_list,
        (int)space_get_id(west));
  }

  if (middle_discovered == TRUE) {
    char_list_status = graphic_engine_get_characters_str(game, middle, char_list);
  } else {
    char_list_status = ERROR;
  }

  if (is_act == TRUE) {
    active_player = game_get_player(game);
    if (active_player && player_get_gdesc(active_player) && player_get_gdesc(active_player)[0] != '\0') {
      active_player_gdesc = player_get_gdesc(active_player);
    } else {
      active_player_gdesc = "^C>";
    }
  }

  sprintf(middle_str, "  | %s %-15s  %3d|  ",
      is_act == TRUE ? active_player_gdesc : "   ",
      char_list_status == ERROR ? "               " : char_list,
      (int)space_get_id(middle));

  if (!east) {
    sprintf(east_str, "                           ");
  } else {
    if (east_discovered == TRUE) {
      char_list_status = graphic_engine_get_characters_str(game, east, char_list);
    } else {
      char_list_status = ERROR;
    }
    sprintf(east_str, "| %-15s      %3d|",
        char_list_status == ERROR ? "               " : char_list,
        (int)space_get_id(east));
  }

  sprintf(str, "%s%s%s", west_str, middle_str, east_str);
  screen_area_puts(area, str);

  /* GDESC LINES*/
  for (i = 0; i < SPACE_GDESC_LINES; i++) {
    wg = (!west || west_discovered == FALSE) ? NULL : space_get_gdesc(west, i);
    mg = (middle_discovered == FALSE) ? "         " : space_get_gdesc(middle, i);
    eg = (!east || east_discovered == FALSE) ? NULL : space_get_gdesc(east, i);

    if (!west) {
      sprintf(west_str, "                             ");
    } else {
      sprintf(west_str, "|%-9s                |  ", wg ? wg : "         ");
    }

    sprintf(middle_str, "|%-9s                | ", mg ? mg : "         ");

    if (!east) {
      sprintf(east_str, "                           ");
    } else {
      sprintf(east_str, " |%-9s                |", eg ? eg : "         ");
    }

    sprintf(str, "%s%s%s", west_str, middle_str, east_str);
    screen_area_puts(area, str);
  }

  /* OBJECTS + ARROWS LINE*/
  if (!west) {
    sprintf(west_str, "                           ");
  } else {
    if (west_discovered == FALSE) {
      sprintf(west_str, "|%-25s|", "");
    } else {
      obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
      sprintf(west_str, "|%-25s|", obj_list_status == ERROR ? "" : obj_list);
    }
  }

  if (middle_discovered == FALSE) {
    sprintf(middle_str, " %s|%-25s|%s ",
        west ? "<" : " ",
        "",
        east ? ">" : " ");
  } else {
    obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);
    sprintf(middle_str, " %s|%-25s|%s ",
        west ? "<" : " ",
        obj_list_status == ERROR ? "" : obj_list,
        east ? ">" : " ");
  }

  if (!east) {
    sprintf(east_str, "                           ");
  } else {
    if (east_discovered == FALSE) {
      sprintf(east_str, "|%-25s|", "");
    } else {
      obj_list_status = graphic_engine_get_objects_str(game, east, obj_list);
      sprintf(east_str, "|%-25s|", obj_list_status == ERROR ? "" : obj_list);
    }
  }

  sprintf(str, "%s%s%s", west_str, middle_str, east_str);
  screen_area_puts(area, str);

  /* BOTTOM LINE */
  sprintf(str, "%s  +-------------------------+  %s",
      !west ? "                           " : "+-------------------------+",
      !east ? "                           " : "+-------------------------+");
  screen_area_puts(area, str);
}

/*   It builds a string with the names of all objects in a given space */
static Status graphic_engine_get_objects_str(Game *game, Space *space, char *str) {
  Id *n = NULL;
  int i, obj_cont;
  char car[ROOM_WIDTH + 1];

  car[0] = '\0';

  if (!game || !space || !str) return ERROR;

  n = space_get_objects(space);
  if (!n) return ERROR;

  obj_cont = space_get_number_of_objects(space);
  if (obj_cont <= 0) return ERROR;

  for (i = 0; i < obj_cont; i++) { /* concatenates object names into a single string */
    Object *obj = game_get_object(game, n[i]);
    if (!obj) continue;
    if (strlen(car) + strlen(object_get_name(obj)) < (size_t)ROOM_WIDTH)
      strcat(car, object_get_name(obj));
    if (i < obj_cont - 1) strcat(car, ", ");
  }

  while ((int)strlen(car) < ROOM_WIDTH) strcat(car, " "); /* pads string to fixed width */
  strcpy(str, car);
  return OK;
}

/*   It builds a string with the names of all characters in a given space */
static Status graphic_engine_get_characters_str(Game *game, Space *space, char *str) {
  Id *n = NULL;
  int i, char_cont, written;
  char car[ROOM_WIDTH + 1];
  const char *name = NULL;
  int name_len, separator_len;

  car[0] = '\0';
  written = 0;

  if (!game || !space || !str) return ERROR;

  n = space_get_character(space);
  if (!n) return ERROR;

  char_cont = space_get_number_of_characters(space);
  if (char_cont <= 0) return ERROR;

  for (i = 0; i < char_cont; i++) {
    Character *c = game_get_character(game, n[i]);
    if (!c) continue;

    name = character_get_gdesc(c);
    name_len = strlen(name);
    separator_len = (written > 0) ? 2 : 0; /* ", " only if not first */

    if (written + separator_len + name_len >= ROOM_WIDTH) break; /* no cabe, para */

    if (written > 0) {
      strcat(car, ", ");
      written += 2;
    }
    strcat(car, name);
    written += name_len;
  }

  /* trunca por seguridad y rellena hasta ROOM_WIDTH exacto */
  car[ROOM_WIDTH] = '\0';
  while ((int)strlen(car) < ROOM_WIDTH) strcat(car, " ");
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
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Id obj_loc = NO_ID, char_loc = NO_ID;
  Space *act = NULL;
  Space *obj_space = NULL;         /* F12, I3: only show objects if space is discovered */
  Space *char_space = NULL;        /* F12, I3: only show characters if space is discovered */
  char str[512];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  int i;
  Player *player = NULL;
  Player *p = NULL;                /* F13, I3: used to iterate all players */
  Character *character = NULL;
  Object *obj = NULL;
  Space *p_space = NULL;           /* F13, I3: space of each player for discovered check */

  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0;
  char obj_line[512];
  int health = 0;
  int turn = 0;
  int last_cmd_player = -1;
  const char *player_label = "P?";

  if (!ge || !game) return;

  /* 1. MAP AREA */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    act = game_get_space(game, id_act);
    if (!act) return;

    id_back = game_get_connection(game, space_get_id(act), N); /* retrieves north and south neighbours */
    id_next = game_get_connection(game, space_get_id(act), S);

    if (id_back != NO_ID) {
      /* North row: show_sides=FALSE — don't reveal its E/W neighbours */
      graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE, FALSE);
      screen_area_puts(ge->map, "                                 ^");
    }
    else {
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
    }

    /* Active row: show_sides=TRUE — player is here, reveal E/W neighbours */
    graphic_engine_paint_spaces_row(ge->map, game, act, TRUE, TRUE);

    if (id_next != NO_ID) {
      screen_area_puts(ge->map, "                                 v");
      /* South row: show_sides=FALSE — don't reveal its E/W neighbours */
      graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_next), FALSE, FALSE);
    }
    else {
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
      screen_area_puts(ge->map, " ");
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
    obj_space = game_get_space(game, obj_loc);                      /* F12, I3: only show objects that are in discovered spaces */
    if (!obj_space || space_get_discovered(obj_space) == FALSE) continue;
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
    char_space = game_get_space(game, char_loc);                            /* F12, I3: only show characters that are in discovered spaces */
    if (!char_space || space_get_discovered(char_space) == FALSE) continue; 
      health = character_get_health(character);
      if (health > 0)
        sprintf(str, "  %-10s: %d (%d hp) [%s] %s", character_get_name(character), (int)char_loc, health, character_get_gdesc(character), character_get_following(character) == player_get_id(p) ? "(Not Recluted)" : "(Recluted)");
      else
        sprintf(str, "  %-10s: %d (DEAD) [%s]", character_get_name(character), (int)char_loc, character_get_gdesc(character));
      screen_area_puts(ge->descript, str);
    }
  screen_area_puts(ge->descript, " ");

  /* Players — prints each player name, location and health (F13, I3) */
  screen_area_puts(ge->descript, " Players:");
  for (i = 0; i < game_get_num_players(game); i++) {
    p = game_get_player_by_index(game, i);
    if (!p) continue;
    p_space = game_get_space(game, player_get_location(p));
    if (!p_space || space_get_discovered(p_space) == FALSE) continue; /* only show discovered players */
    sprintf(str, "  %-8s: %d (%d hp) [%s]", player_get_name(p),
            (int)player_get_location(p), player_get_health(p), player_get_gdesc(p));
    screen_area_puts(ge->descript, str);
  }
  screen_area_puts(ge->descript, " ");

  /* Player — prints location, health and carried object and character recruited */
  player = game_get_player(game);
  sprintf(str, " Player: %s at %d (%d hp)", player_get_name(player), (int)player_get_location(player), player_get_health(player));
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

  /* Inspect message — displays and clears last message if present */
  screen_area_puts(ge->descript, " ");
  if (game_get_last_object_description(game) && game_get_last_object_description(game)[0] != '\0') {
    sprintf(str, " Description: %s", game_get_last_object_description(game));
    screen_area_puts(ge->descript, str);
    game_set_last_object_description(game, ""); /* clears description after displaying */
  }

  /* 3. BANNER */
  sprintf(str, "    Player: %s ", player_get_name(game_get_player(game)));
  screen_area_puts(ge->banner, str);

  /* 4. HELP — lists all available commands */
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " The commands you can use are:");
  screen_area_puts(ge->help, "  move <dir> or m <n|s|e|w>, take or t, drop or d, attack or a, chat or c, exit or e, inspect or i,");
  screen_area_puts(ge->help, "  recruit or r, abandon or b, open <link> with <object>, use <object> [over <character>],");

  /* 5. FEEDBACK — shows last command and its result status */
  screen_area_clear(ge->feedback);
  if(game_get_last_command(game) != NULL && command_get_code(game_get_last_command(game)) != NO_CMD){
    last_cmd = command_get_code(game_get_last_command(game));
    last_cmd_player = game_get_last_command_player(game);
    player_label = "P?";

    if (last_cmd_player == 0) {
      player_label = "P1";
    } else if (last_cmd_player == 1) {
      player_label = "P2";
    }

    sprintf(str, " %s: %s (%s)", cmd_to_str[last_cmd][CMDL], game_get_last_status(game) == OK ? "OK" : "ERROR", player_label);
    screen_area_puts(ge->feedback, str);
  }
  else{
    screen_area_puts(ge->feedback, " No command inserted");
  }
  
/* 6. Render with player color (F13, I3) */
  turn = game_get_turn(game);
  if (turn == 0) {
    screen_paint(BLUE);   /* player 0 gets blue border */
  } else if (turn == 1) {
    screen_paint(GREEN);  /* player 1 gets green border */
  } else {
    screen_paint(BLACK);  /* fallback for more players */
  }
  printf("prompt:> ");
}