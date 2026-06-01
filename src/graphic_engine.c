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
#include <string.h>
#include <unistd.h>

#include "command.h"
#include "libscreen.h"
#include "space.h"
#include "types.h"
#include "character.h"
#include "player.h"
#include "object.h"
#include "game.h"

/**
 * @brief Width of the map area
*/
#define WIDTH_MAP 85

/**
 * @brief Width of the description area
*/
#define WIDTH_DES 65

/**
 * @brief Width of the banner area
*/
#define WIDTH_BAN 25

/**
 * @brief Height of the map area
*/
#define HEIGHT_MAP 29 /* en total deben ser 54, hasta que se quiten los characters de la derecha para que no colapse */

/**
 * @brief Height of the banner area
*/
#define HEIGHT_BAN 1

/**
 * @brief Height of the help area
*/
#define HEIGHT_HLP 4

/**
 * @brief Height of the feedback area
*/
#define HEIGHT_FDB 3

/**
 * @brief Width of each room in the map
*/
#define ROOM_WIDTH 15

/**
 * @brief Number of char for the P1 and P2 specification
*/
#define PLAYER_ACTION 3

/**
 * @brief Width of the character information that is under the map
*/
#define HEIGHT_CHAR 11

/*
 * hp > HP_HIGH -> green (healthy)
 * HP_LOW < hp <= HP_HIGH -> yellow (wounded)
 * hp <= HP_LOW -> red (critical)
 */

/**
 * @brief HP healty
*/
#define HP_HIGH 6

/**
 * @brief HP critial
*/
#define HP_LOW  3

/**
 * @brief Structure representing the graphic engine
*/
struct _Graphic_engine {
  Area *map, /**< Map area */
   *descript, /**< Description area */
   *banner, /**< Banner area */
   *help, /**< Help area */
   *feedback, /**< Feedback area */
   *char_info; /**< Character area */
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

/**
 * @brief Returns the Color_attr that matches a given hp value.
 *
 * hp > HP_HIGH  -> COLOR_ATTR_BOLD_GREEN
 * HP_LOW < hp <= HP_HIGH -> COLOR_ATTR_BOLD_YELLOW
 * hp <= HP_LOW  -> COLOR_ATTR_BOLD_RED
 */
static Color_attr hp_to_color(int hp) {
  if (hp > HP_HIGH) return COLOR_ATTR_BOLD_GREEN;
  if (hp > HP_LOW) return COLOR_ATTR_BOLD_YELLOW;
  return COLOR_ATTR_BOLD_RED;
}

/**
 * @brief Returns the Frame_color that corresponds to a player turn index.
 *
 * turn 0 -> BLUE
 * turn 1 -> GREEN
 * others -> BLACK
 */
static Frame_color turn_to_frame_color(int turn) {
  if (turn == 0) return BLUE;
  if (turn == 1) return GREEN;
  if( turn == 2) return YELLOW;
  return BLACK;
}

/**
 * @brief Returns the Color_attr that matches the active player's frame color.
 *
 * turn 0 -> COLOR_ATTR_BOLD_BLUE
 * turn 1 -> COLOR_ATTR_BOLD_GREEN
 * others -> COLOR_ATTR_BOLD
 */
static Color_attr turn_to_text_color(int turn) {
  if (turn == 0) return COLOR_ATTR_BOLD_BLUE;
  if (turn == 1) return COLOR_ATTR_BOLD_GREEN;
  return COLOR_ATTR_BOLD;
}

/* It creates a new Graphic_engine, allocating memory and initializing its members */
Graphic_engine *graphic_engine_create() {
  Graphic_engine *ge = NULL;

  screen_init(HEIGHT_MAP + HEIGHT_CHAR + HEIGHT_BAN + HEIGHT_HLP + HEIGHT_FDB + 5, WIDTH_MAP + WIDTH_DES + 3); /* initializes screen with total dimensions */
  ge = (Graphic_engine *)calloc(1, sizeof(Graphic_engine));
  if (ge == NULL) return NULL;

  /* initializes each display area with its position and dimensions */
  ge->map = screen_area_init(1, 1, WIDTH_MAP, HEIGHT_MAP);
  ge->descript = screen_area_init(WIDTH_MAP + 2, 1, WIDTH_DES, HEIGHT_MAP + HEIGHT_CHAR + 1);
  ge->char_info = screen_area_init(1, HEIGHT_MAP + 2, WIDTH_MAP, HEIGHT_CHAR);
  ge->banner = screen_area_init((int)((WIDTH_MAP + WIDTH_DES + 1 - WIDTH_BAN) / 2), HEIGHT_MAP + HEIGHT_CHAR + 3, WIDTH_BAN, HEIGHT_BAN);
  ge->help = screen_area_init(1, HEIGHT_MAP + HEIGHT_CHAR + HEIGHT_BAN + 3, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_HLP);
  ge->feedback = screen_area_init(1, HEIGHT_MAP + HEIGHT_CHAR + HEIGHT_BAN + HEIGHT_HLP + 4, WIDTH_MAP + WIDTH_DES + 1, HEIGHT_FDB);
  
  return ge;
}

/* It destroys a Graphic_engine, freeing the allocated memory */
void graphic_engine_destroy(Graphic_engine *ge) {
  if (!ge) return;

  /* destroys each display area */
  screen_area_destroy(ge->map);
  screen_area_destroy(ge->char_info);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}

/* It renders the current state of the game on screen */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game) {
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID;
  Id obj_loc = NO_ID, char_loc = NO_ID;
  Space *act = NULL;
  Space *obj_space = NULL;
  Space *char_space = NULL;
  char str[WORD_SIZE];
  CommandCode last_cmd = UNKNOWN;
  extern char *cmd_to_str[N_CMD][N_CMDT];
  Player *player = NULL;
  Player *p = NULL;
  Character *character = NULL;
  Object *obj = NULL;
  Space *p_space = NULL;
  Set *inv_set = NULL;
  Set *inv_set_team = NULL;
  Id *ids = NULL;
  Id *ids_team = NULL;
  int n = 0;
  char obj_line[512];
  char char_line[1024];
  int health = 0;
  int turn = 0;
  int last_cmd_player = -1;
  char player_label[PLAYER_ACTION];
  char player_num = '0';
  Bool cmd_ok = FALSE;
  int i;

  char room_name[498];

  /* offsets used to highlight hp numbers inside a formatted string */
  int hp_offset = 0;
  int hp_len = 0;
  Color_attr hp_col;

  Bool has_access_n = TRUE, has_access_s = TRUE;

  if (!ge || !game) return;

  turn = game_get_turn(game);

  /* 1. MAP AREA */
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID) {
    act = game_get_space(game, id_act);
    if (!act) return;

    id_back = game_get_connection(game, space_get_id(act), N); /* retrieves north and south neighbours */
    id_next = game_get_connection(game, space_get_id(act), S);

    has_access_n = game_get_connection_status(game, id_act, N);
    has_access_s = game_get_connection_status(game, id_act, S);

    if (id_back != NO_ID) {
      /* North row: show_sides=FALSE — don't reveal its E/W neighbours */
      graphic_engine_paint_spaces_row(ge->map, game, game_get_space(game, id_back), FALSE, FALSE);

      if (has_access_n)
        screen_area_puts(ge->map, "                                 ^");
      else
        screen_area_puts(ge->map, "                                 x");
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
      if (has_access_s)
        screen_area_puts(ge->map, "                                 v");
      else
        screen_area_puts(ge->map, "                                 x");

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
  screen_area_clear(ge->char_info);
  screen_area_puts(ge->descript, " ");
  screen_area_puts(ge->char_info, " ");

  /* Players Room name Location*/
  strcpy(room_name, space_get_name(game_get_space(game, game_get_player_location(game))));
  sprintf(str, " Room's name: %s", room_name);
  screen_area_puts(ge->descript, str);
  screen_area_puts(ge->descript, " ");

  /* Prints each player name, location and health */
  screen_area_puts(ge->descript, " Players:");
  for (i = 0; i < game_get_num_players(game); i++) {
    p = game_get_player_by_index(game, i);
    if (!p) continue;
    p_space = game_get_space(game, player_get_location(p));
    if (!p_space || space_get_discovered(p_space) == FALSE) continue; /* only show discovered players */
    health = player_get_health(p);
    {
      char prefix_hp[128];
      char hp_str2[12];
      int  hp_off2, hp_len2;

      sprintf(prefix_hp, "  %-8s: %-3d (", player_get_name(p), (int)player_get_location(p));
      hp_off2 = (int)strlen(prefix_hp);
      sprintf(hp_str2, "%d", health);
      hp_len2 = (int)strlen(hp_str2);

      sprintf(str, "  %-8s: %-3d (%d hp) [%s] (%d/%d inv)",
              player_get_name(p), (int)player_get_location(p),
              health, player_get_gdesc(p), player_get_number_of_items_in_backpack(p),
              inventory_get_max_objs(player_get_backpack(p)));

      hp_col = hp_to_color(health);
      screen_area_puts_bold_color_at(ge->descript, str, hp_off2, hp_len2, hp_col);
    }
  }
  screen_area_puts(ge->descript, " ");

  /* Prints location, health and carried object and character recruited */
  player = game_get_player(game);
  health = player_get_health(player);
  {
    char prefix_hp[128];
    char hp_str3[12];
    int  hp_off3, hp_len3;

    sprintf(prefix_hp, " Player: %s at %d (", player_get_name(player), (int)player_get_location(player));
    hp_off3 = (int)strlen(prefix_hp);
    sprintf(hp_str3, "%d", health);
    hp_len3 = (int)strlen(hp_str3);

    sprintf(str, " Player: %s at %d (%d hp)",
            player_get_name(player), (int)player_get_location(player), health);

    hp_col = hp_to_color(health);
    screen_area_puts_bold_color_at(ge->descript, str, hp_off3, hp_len3, hp_col);
  }

  inv_set = inventory_get_objects(player_get_backpack(player));
  if(inv_set != NULL){ /* gets number of objects in inventory */
    n = set_get_n_ids(inv_set);
  }else{
    n = 0; /* no objects in inventory */
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

  if (player_get_team(player) != NO_ID) {
    inv_set_team = inventory_get_objects(player_get_backpack(game_get_player_by_id(game, player_get_team(player))));
    if(inv_set_team != NULL){ /* gets number of objects in inventory */
      n = set_get_n_ids(inv_set_team);
    }else{
      n = 0; /* no objects in inventory */
    }

    if (n <= 0) {
      screen_area_puts(ge->descript, " Team-Mate has no objects");
    } else {
      ids_team = set_get_ids(inv_set_team);
      strcpy(obj_line, " Team-Mate has:");
      for (i = 0; i < n; i++) {
        obj = game_get_object(game, ids_team[i]);
        if (obj) {
          strcat(obj_line, " ");
          strcat(obj_line, object_get_name(obj));
          if (i < n - 1) strcat(obj_line, ",");
        }
      }
      screen_area_puts(ge->descript, obj_line);
    }
  }
  screen_area_puts(ge->descript, " ");

  /* health movable dependency */
  /* Prints each object name and its location */
  screen_area_puts(ge->descript, " Objects:");
  for (i = 0; i < MAX_OBJECTS; i++) {
    obj = game_get_object_by_index(game, i);
    if (!obj) break;
    obj_loc = game_get_object_location(game, object_get_id(obj));
    obj_space = game_get_space(game, obj_loc); /* Only show objects that are in discovered spaces */
    if (!obj_space || space_get_discovered(obj_space) == FALSE) continue;

    sprintf(str, "  %-13s   [ %s ] at %d (%d hp, %s, %s)", object_get_name(obj), object_get_gdesc(obj),(int)obj_loc, object_get_health(obj), object_get_movable(obj) ? "mov" : "fix", object_get_dependency(obj) != NO_ID ? "dep" : "indep");

    screen_area_puts(ge->descript, str);
  }
  screen_area_puts(ge->descript, " ");

  /* Prints each character name, location and health (hp coloured green/yellow/red) */
  screen_area_puts(ge->char_info, " Characters:");
  for (i = 0; i < MAX_CHARACTERS; i++) {
    character = game_get_character_by_index(game, i);
    if (!character) break;
    char_loc = game_get_character_location(game, character_get_id(character));
    char_space = game_get_space(game, char_loc); /* Only show characters that are in discovered spaces */
    if (!char_space || space_get_discovered(char_space) == FALSE) continue; 
    health = character_get_health(character);
    if (health > 0) {
      char prefix[128];
      char hp_str[12];
      sprintf(prefix, "  %-10s: %d (", character_get_name(character), (int)char_loc);
      hp_offset = (int)strlen(prefix);
      sprintf(hp_str, "%d", health);
      hp_len = (int)strlen(hp_str);

      strcpy(char_line, "[");
      if (character_is_friendly(character) == TRUE) {
        strcat(char_line, "Ally");
        strcat(char_line, "]");

        if (character_get_following(character) == NO_ID){
          strcat(char_line, " (Not Recruited)");
        }
        else {
          strcat(char_line, " (Recruited by ");
          strcat(char_line, player_get_name(game_get_player_by_id(game, character_get_following(character))));
          strcat(char_line, ")");
        }

      } else {
        strcat(char_line, "Enemy");
        strcat(char_line, "]");
      }

      sprintf(str, "  %-10s: %d (%d hp)  [%s] %s",
              character_get_name(character), (int)char_loc, health,
              character_get_gdesc(character), char_line);
   
      hp_col = hp_to_color(health);
      screen_area_puts_bold_color_at(ge->char_info, str, hp_offset, hp_len, hp_col);
    } else {
      sprintf(str, "  %-10s: %d (DEAD)  [%s]", character_get_name(character), (int)char_loc, character_get_gdesc(character));
      screen_area_puts_red(ge->char_info, str);
      sleep(1);
      space_del_character(act, character_get_id(character));
    }
  }
  screen_area_puts(ge->char_info, " ");

  /* Displays and clears last message if present */
  if (game_get_last_message(game) && game_get_last_message(game)[0] != '\0') {
    sprintf(str, " Message: %s", game_get_last_message(game));
    screen_area_puts(ge->char_info, str);
  }
  /* Displays and clears last message if present */
  if (game_get_last_object_description(game) && game_get_last_object_description(game)[0] != '\0') {
    sprintf(str, " Description: %s", game_get_last_object_description(game));
    screen_area_puts(ge->descript, str);
  }

  /* 3. BANNER — coloured with active player's colour */
  {
    int bname_off = (int)strlen("    Player: ");
    int bname_len = (int)strlen(player_get_name(game_get_player(game)));
    sprintf(str, "    Player: %s ", player_get_name(game_get_player(game)));
    screen_area_puts_bold_color_at(ge->banner, str, bname_off, bname_len, turn_to_text_color(turn));
  }

  /* 4. HELP — lists all available commands */
  screen_area_clear(ge->help);
  screen_area_puts(ge->help, " Player Commands:  move <dir> or m <n|s|e|w|u|d>, colab <player> or k <player>");
  screen_area_puts(ge->help, " Object Commands:  take <obj> or t <obj>, drop <obj> or d <obj>, inspect <obj> or i <obj>, open <link> with <obj>, use <obj> over <char>");
  screen_area_puts(ge->help, " Character Commands:  attack <char> or a <char>, char <char> or c <har>, recruit <char> or r <char>, abandon <char> or b <char>");
  screen_area_puts(ge->help, " Other Commands:  save <file> or s <file>, load <file> or l <file>, exit or e");

  /* 5. FEEDBACK — shows last command; OK coloured with player colour, ERROR in red */
  screen_area_clear(ge->feedback);
  screen_area_puts(ge->feedback, " ");
  if(game_get_last_command(game) != NULL && command_get_code(game_get_last_command(game)) != NO_CMD){
    last_cmd = command_get_code(game_get_last_command(game));
    last_cmd_player = game_get_last_command_player(game);

    player_label[0] = 'P';
    player_num = (char)(last_cmd_player + 1 + '0');
    player_label[1] = player_num;
    player_label[2] = '\0';

    cmd_ok = (game_get_last_status(game) == OK);
    sprintf(str, " %s (%s): %s", cmd_to_str[last_cmd][CMDL], player_label, cmd_ok ? "OK" : "ERROR");
    if (cmd_ok) {
      int ok_offset = (int)strlen(str) - 2; /* points at "OK" */
      screen_area_puts_bold_color_at(ge->feedback, str, ok_offset, 2, turn_to_text_color(last_cmd_player));
    } else {
      screen_area_puts_red(ge->feedback, str);
    }
  }
  else{
    screen_area_puts(ge->feedback, " No command inserted");
  }

  /* 6. Render with player color */
  screen_paint(turn_to_frame_color(turn));
  printf("prompt:> ");
}

/* It paints a row of three horizontally adjacent spaces centered on the given space.
 * If show_sides is FALSE, west and east neighbours are not shown */
static void graphic_engine_paint_spaces_row(Area *area, Game *game, Space *middle, Bool is_act, Bool show_sides) {
  Space *west = NULL, *east = NULL, *up = NULL, *down = NULL;
  Player *active_player = NULL;
  const char *active_player_gdesc = "   ";
  const char *wg = NULL, *mg = NULL, *eg = NULL;
  char str[512], west_str[128], middle_str[128], east_str[128];
  char obj_list[ROOM_WIDTH + 1], char_list[ROOM_WIDTH + 1];
  Status obj_list_status, char_list_status;
  int i;
  Bool west_discovered = FALSE, middle_discovered = FALSE, east_discovered = FALSE;
  char floor_arrow[3];

  Id id_act = NO_ID;
  Bool has_access_w = TRUE, has_access_e = TRUE;
  Bool has_access_u = TRUE, has_access_d = TRUE;


  if (!area || !middle) return;

  if (show_sides == TRUE) {
    west = game_get_space(game, game_get_connection(game, space_get_id(middle), W));
    east = game_get_space(game, game_get_connection(game, space_get_id(middle), E));
    up = game_get_space(game, game_get_connection(game, space_get_id(middle), U));
    down = game_get_space(game, game_get_connection(game, space_get_id(middle), D));
  }

  id_act = game_get_player_location(game);
  has_access_w = game_get_connection_status(game, id_act, W);
  has_access_e = game_get_connection_status(game, id_act, E);
  has_access_u = game_get_connection_status(game, id_act, U);
  has_access_d = game_get_connection_status(game, id_act, D);


  middle_discovered = space_get_discovered(middle);
  if (west) west_discovered = space_get_discovered(west);
  if (east) east_discovered = space_get_discovered(east);

  /* TOP LINE */
  sprintf(str, "%s  +-------------------------+  %s",
      !west ? "                           " : "+-------------------------+",
      !east ? "                           " : "+-------------------------+");
  screen_area_puts(area, str);

  /* CHARACTER + ID LINE */
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

  /* Se mira si tiene up o down para imprimir una flecha */
  if(up && !down) {
    if (has_access_u)
      strcpy(floor_arrow, "^ ");
    else
      strcpy(floor_arrow, "x ");
  }
  else if(down && !up) {
    if (has_access_d)
      strcpy(floor_arrow, " v");
    else
      strcpy(floor_arrow, " x");
  }
  else if(down && up) {
    if (has_access_u && has_access_d)
      strcpy(floor_arrow, "^v");
    else if (has_access_u && !has_access_d)
      strcpy(floor_arrow, "^x");
    else if (!has_access_u && has_access_d)
      strcpy(floor_arrow, "xv");
    else
      strcpy(floor_arrow, "xx");
  }
  else strcpy(floor_arrow, "  ");

  sprintf(middle_str, "  | %s %-9s%s%3d|  ",
      is_act == TRUE ? active_player_gdesc : "   ",
      char_list_status == ERROR ? "               " : char_list,
      floor_arrow,
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
  if (is_act == TRUE) {
    int bold_start = strlen(west_str) + 4;
    int bold_len = (int)strlen(active_player_gdesc);
    screen_area_puts_bold_at(area, str, bold_start, bold_len);
  } else {
    screen_area_puts(area, str);
  }

  /* GDESC LINES */
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

  /* OBJECTS + ARROWS LINE */
  if (!west) {
    sprintf(west_str, "                           ");
  } else {
    if (west_discovered == FALSE) {
      sprintf(west_str, "|%-25s|", "");
    } else {
      obj_list_status = graphic_engine_get_objects_str(game, west, obj_list);
      sprintf(west_str, "| %-24s|", obj_list_status == ERROR ? "" : obj_list);
    }
  }

  if (middle_discovered == FALSE) {
    if (has_access_e && has_access_w)
      sprintf(middle_str, " %s|%-25s|%s ",
          west ? "<" : " ",
          "",
          east ? ">" : " ");
    else if (has_access_e && !has_access_w)
      sprintf(middle_str, " %s|%-25s|%s ",
          west ? "x" : " ",
          "",
          east ? ">" : " ");
    else if (!has_access_e && has_access_w)
      sprintf(middle_str, " %s|%-25s|%s ",
          west ? "<" : " ",
          "",
          east ? "x" : " ");
    else
      sprintf(middle_str, " %s|%-25s|%s ",
          west ? "x" : " ",
          "",
          east ? "x" : " ");
  } else {
    obj_list_status = graphic_engine_get_objects_str(game, middle, obj_list);

    if (has_access_e && has_access_w)
      sprintf(middle_str, " %s| %-24s|%s ",
          west ? "<" : " ",
          obj_list_status == ERROR ? "" : obj_list,
          east ? ">" : " ");
    else if (has_access_e && !has_access_w)
      sprintf(middle_str, " %s| %-24s|%s ",
          west ? "x" : " ",
          obj_list_status == ERROR ? "" : obj_list,
          east ? ">" : " ");
    else if (!has_access_e && has_access_w)
      sprintf(middle_str, " %s| %-24s|%s ",
          west ? "<" : " ",
          obj_list_status == ERROR ? "" : obj_list,
          east ? "x" : " ");
    else
      sprintf(middle_str, " %s| %-24s|%s ",
          west ? "x" : " ",
          obj_list_status == ERROR ? "" : obj_list,
          east ? "x" : " ");
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

/* It builds a string with the names of all objects in a given space */
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
    if (strlen(car) + strlen(object_get_gdesc(obj)) < (size_t)ROOM_WIDTH)
      strcat(car, object_get_gdesc(obj));
    if (i < obj_cont - 1) strcat(car, ", ");
  }

  while ((int)strlen(car) < ROOM_WIDTH) strcat(car, " ");
  strcpy(str, car);
  return OK;
}

/* It builds a string with the names of all characters in a given space */
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

  /* se trunca por seguridad y rellena hasta ROOM_WIDTH exacto */
  car[ROOM_WIDTH] = '\0';
  while ((int)strlen(car) < ROOM_WIDTH) strcat(car, " ");
  strcpy(str, car);
  return OK;
}