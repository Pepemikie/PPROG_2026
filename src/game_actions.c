/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author José Miguel Romero Oubiña
 * @version 3
 * @date 01-04-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"
#include "game_management.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/**
 * @brief Pointer to the log file
*/
extern FILE *g_logfile;

/**
 * @brief Command string table
*/
extern char *cmd_to_str[N_CMD][N_CMDT];

/**
 * @brief Makes the player pick up the named object in the current space
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was picked up, ERROR otherwise
 */
Status game_actions_take(Game *game);

/**
 * @brief Makes the player drop their named carried object into the current space
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was dropped, ERROR otherwise
 */
Status game_actions_drop(Game *game);

/**
 * @brief Makes the player attack if the character in the space is not friendly
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the attack was performed, ERROR otherwise
 */
Status game_actions_attack(Game *game);

/**
 * @brief Makes the player interact with a friendly character by chat
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the chat was performed, ERROR otherwise
 */
Status game_actions_chat(Game *game);

/**
 * @brief Moves the player to the next space in the given direction if it exists and is open
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the player moved, ERROR otherwise
 */
Status game_actions_move(Game *game);

/**
 * @brief Inspects a named object in the current space or in the player's inventory
 * @author José Miguel Romero Oubiña
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was inspected, ERROR otherwise
 */
Status game_actions_inspect(Game *game);

/**
 * @brief Recruits a friendly character in the current space to follow the player
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @return OK if the character was recruited, ERROR otherwise
 */
Status game_actions_recruit(Game *game);

/**
 * @brief Abandons the character that you have previously recruited
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @return OK if the character was abandoned, ERROR otherwise
 */
Status game_actions_abandon(Game *game);

/**
 * @brief Opens a named link with a named object in the current space, if possible
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @return OK if the link was opened, ERROR otherwise
 */
Status game_actions_open(Game *game);

/**
 * @brief Uses an object on the player or a friendly character
 * @author Iñaki López Rocha
 * 
 * @param game a pointer to the Game struct
 * @return OK if the object was used, ERROR otherwise
 */
Status game_actions_use(Game *game);

/**
 * @brief Checks if an object can be taken by the player
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @return TRUE if the object can be taken, FALSE otherwise
 */
Bool can_take_object(Game *game, Object *obj);

/**
 * @brief Handles the logic of taking an object, including dependencies and links
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @param current_space a pointer to the current Space
 * @return OK if the object was taken, ERROR otherwise
 */
Status handle_take_object(Game *game, Object *obj, Space *current_space);

/**
 * @brief Handles the logic of dropping an object, including dependent objects
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @param current_space a pointer to the current Space
 * @return OK if the object was dropped, ERROR otherwise
 */
Status handle_drop_object(Game *game, Object *obj, Space *current_space);

/**
 * @brief Collaborates with another player, if both players are in the same space and have recruited each other
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @return OK if the collaboration was successful, ERROR otherwise 
 */
Status game_actions_colab(Game *game);

/**
 * @brief Saves the current game state to a file
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @param filename the name of the file where the game state will be saved
 * @return OK if the game state was saved successfully, ERROR otherwise
 */
Status save_game_state(Game *game, const char *filename);

/**
 * @brief Loads a game state from a file, replacing the current game state
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @param filename the name of the file from which the game state will be loaded
 * @return OK if the game state was loaded successfully, ERROR otherwise
 */
Status load_game_state(Game *game, const char *filename);

/**
 * @brief Gets the team player of the current player
 * @author José Miguel Romero Oubiña
 * 
 * @param game a pointer to the Game struct
 * @return a pointer to the team Player, or NULL if there is no team player
 */
Player *game_player_get_team(Game *game);

/* Implementation of auxiliary functions */

/* Gets the team player of the current player */
Player *game_player_get_team(Game *game) {
  Id player_id = NO_ID;
  Player *aux_player = NULL;
  int i = 0;

  player_id = player_get_id(game_get_player(game));

  for (i = 0; i < MAX_PLAYERS; i++) {
    aux_player = game_get_player_by_index(game, i);
    if (!aux_player) break;

    if (aux_player != game_get_player(game)) {
      if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player))
        return aux_player;
    }
  }
  return NULL;
}

/* Checks if an object can be taken by the player */
Bool can_take_object(Game *game, Object *obj) {
  Player *aux_player = NULL;
  int i = 0;

  if (!game || !obj) return FALSE;
  
  /* Check if object is movable */
  if (!object_get_movable(obj)) return FALSE;
  
  /* Check dependency */
  if (object_get_dependency(obj) != NO_ID) {
    if (!inventory_has_object(player_get_backpack(game_get_player(game)), object_get_dependency(obj))) {

      if (player_get_team(game_get_player(game)) == NO_ID)
        return FALSE;
      for (i = 0; i < MAX_PLAYERS; i++) {
        aux_player = game_get_player_by_index(game, i);
        if (!aux_player) break;

        if (aux_player != game_get_player(game)) {
          if (player_get_team(aux_player) == player_get_id(game_get_player(game)) || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {
            if (!inventory_has_object(player_get_backpack(aux_player), object_get_dependency(obj)))
              return FALSE;
          }
        }
      }
    }
  }
  
  return TRUE;
}

/* It handles the logic of taking an object, including dependencies and links */
Status handle_take_object(Game *game, Object *obj, Space *current_space) {
  Id object_id;
  
  if (!game || !obj || !current_space) return ERROR;
  
  object_id = object_get_id(obj);
  
  if (player_add_object(game_get_player(game), object_id) == ERROR) return ERROR;
  space_del_object(current_space, object_id);

  return OK;
}

/* It handles the logic of dropping an object, including dependent objects */
Status handle_drop_object(Game *game, Object *obj, Space *current_space) {
  Id object_id, player_location;
  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0, i = 0, num_to_drop = 0, num_to_drop1 = 0, num_to_drop2 = 0, j = 0;
  Id *to_drop = NULL;
  Object *dep_obj = NULL;
  Player *team = NULL;
  Set *inv_team = NULL;
  Id *ids_team = NULL;
  int n_team = 0;
  Bool team_drop = FALSE;

  if (!game || !obj || !current_space) return ERROR;
  
  object_id = object_get_id(obj);
  player_location = game_get_player_location(game);
  
  if (player_del_object(game_get_player(game), object_id) == ERROR) return ERROR;

  space_add_object(current_space, object_id);
  game_set_object_location(game, player_location, object_id);

  /* Drop dependent objects */
  inv_set = inventory_get_objects(player_get_backpack(game_get_player(game)));
  if (!inv_set) return OK; /* No inventory, nothing to drop */
  
  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);

  /* Count dependent objects */
  for (i = 0; i < n; i++) {
    dep_obj = game_get_object(game, ids[i]);
    if (dep_obj && object_get_dependency(dep_obj) == object_id) {
      num_to_drop1++;
    }
  }

  /* Count dependent objects in team player */
  team = game_player_get_team(game);
  if (team) {
    team_drop = TRUE;
    inv_team = inventory_get_objects(player_get_backpack(team));
    if (inv_team) {
      n_team = set_get_n_ids(inv_team);
      ids_team = set_get_ids(inv_team);
      if (ids_team && n_team > 0) {
        for (i = 0; i < n_team; i++) {
          dep_obj = game_get_object(game, ids_team[i]);
          if (dep_obj && object_get_dependency(dep_obj) == object_id) {
            num_to_drop2++;
          }
        }
      }
    }
  }

  num_to_drop = num_to_drop1 + num_to_drop2;

  if (num_to_drop == 0){
    return OK;
  }
  
  to_drop = (Id*)malloc(sizeof(Id) * num_to_drop);
  if (!to_drop) return OK; /* Memory error, but object was dropped */
  
  /* Collect ids of dependent objects */
  j = 0;
  for (i = 0; i < num_to_drop1; i++) {
    dep_obj = game_get_object(game, ids[i]);
    if (dep_obj && object_get_dependency(dep_obj) == object_id) {
      to_drop[j++] = ids[i];
    }
  }

  /* Collect ids of dependent objects in team player */
  if (team_drop) {
    for (i = 0; i < num_to_drop2; i++) {
      dep_obj = game_get_object(game, ids_team[i]);
      if (dep_obj && object_get_dependency(dep_obj) == object_id) {
        to_drop[j++] = ids_team[i];
      }
    }
  }

  /* Drop dependent objects */
  for (i = 0; i < num_to_drop1; i++) {
    object_id = to_drop[i];
    player_del_object(game_get_player(game), object_id);
    space_add_object(current_space, object_id);
    game_set_object_location(game, player_location, to_drop[i]);
  }

  /* Drop dependent objects in team player */
  if (team_drop) {
    for (i = num_to_drop1; i < num_to_drop; i++) {
      object_id = to_drop[i];
      player_del_object(team, object_id);
      space_add_object(current_space, object_id);
      game_set_object_location(game, player_location, to_drop[i]);

      if (i == num_to_drop-1) break;

    }
  }

  free(to_drop);
  return OK;
}

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;
  Status st;
  int fails;
  char fails_message[128];

  game_set_last_message(game, ""); /* Reinicio de message e inspect si hay nuevo comando */
  game_set_last_object_description(game, "");

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_set_last_status(game, ERROR);
      break;

    case EXIT:
      game_set_last_status(game, OK);
      break;
    
    case TAKE:
      game_set_last_status(game, game_actions_take(game));
      break;

    case DROP:
      game_set_last_status(game, game_actions_drop(game));
      break;

    case ATTACK:
      game_set_last_status(game, game_actions_attack(game));
      break;

    case CHAT:
      game_set_last_status(game, game_actions_chat(game));
      break;

    case MOVE:
      game_set_last_status(game, game_actions_move(game));
      break;

    case INSPECT:
      game_set_last_status(game, game_actions_inspect(game));
      break;

    case RECRUIT:
      game_set_last_status(game, game_actions_recruit(game));
      break;

    case ABANDON:
      game_set_last_status(game, game_actions_abandon(game));
      break;

    case OPEN:
      game_set_last_status(game, game_actions_open(game));
      break;

    case USE:
      game_set_last_status(game, game_actions_use(game));
      break;

    case SAVE:
      game_set_last_status(game, save_game_state(game, command_get_arg(command)));
      break;

    case LOAD:
      game_set_last_status(game, load_game_state(game, command_get_arg(command)));
      break;

    case COLAB:
      game_set_last_status(game, game_actions_colab(game));
      break;

    default:
      game_set_last_status(game, ERROR);
      break;
  }

  st = game_get_last_status(game);

  if (st == ERROR) {
    fails = game_get_failure_count(game) + 1;
    game_set_failure_count(game, fails);

    if (fails < 3) {
      sprintf(fails_message, "Command Error. Try again %d/3.", fails);
      game_set_last_message(game, fails_message);
      game_set_must_keep_turn(game, TRUE);
    } else {
      game_set_last_message(game, "Maximum number of attempts reached. You pass your turn.");
      game_set_failure_count(game, 0);
      game_set_must_keep_turn(game, FALSE);
    }
  } else {
    game_set_failure_count(game, 0);
    game_set_must_keep_turn(game, FALSE);
  }

  /* Log the command if logging is enabled */
  if (g_logfile != NULL && cmd != UNKNOWN && cmd != NO_CMD) {
    char arg[WORD_SIZE] = "";
    char player_str[16] = "";

    if (command_get_arg(command) != NULL) {
      strcpy(arg, command_get_arg(command));
    }

    sprintf(player_str, "P%d", game_get_turn(game) + 1); /* P1, P2, P3... */

    if (arg[0] != '\0') {
      fprintf(g_logfile, "%s %s: %s (%s)\n", cmd_to_str[cmd][CMDL], arg, game_get_last_status(game) == OK ? "OK" : "ERROR", player_str);
    } else {
      fprintf(g_logfile, "%s: %s (%s)\n", cmd_to_str[cmd][CMDL], game_get_last_status(game) == OK ? "OK" : "ERROR", player_str);
    }
    fflush(g_logfile);
  }
  return OK;
}

/* Makes the player pick up the named object in the current space */
Status game_actions_take(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Space *current_space = NULL;
  Object *obj = NULL;
  int num_objects = 0;
  int i=0;
  Id *objects = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;

  player_location = game_get_player_location(game);
  if(player_location == NO_ID) return ERROR;

  current_space = game_get_space(game, player_location);
  if(!current_space) return ERROR;

  last_cmd = game_get_last_command(game);
  if(!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if(!arg || arg[0] == '\0') return ERROR;

  if (inventory_is_full(player_get_backpack(game_get_player(game)))) return ERROR;

  num_objects = space_get_number_of_objects(current_space);

  if (num_objects > 0) {
    objects = space_get_objects(current_space);

    if (objects) {
      for (i = 0; i < num_objects; i++) {
        obj = game_get_object(game, objects[i]);

        if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
          object_id = objects[i];
          break;
        }
      }

      if (object_id != NO_ID) {
        obj = game_get_object(game, object_id);
        if (!obj) return ERROR;
        
        /* Check if object can be taken */
        if (!can_take_object(game, obj)) return ERROR;
        
        /* Handle taking the object */
        return handle_take_object(game, obj, current_space);
      }
    }
  }

  return ERROR;
}

/* Makes the player drop the named object into the current space */
Status game_actions_drop(Game *game) {
  Id player_location = NO_ID;
  Id carried_object_id = NO_ID;
  Space *current_space = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  Set *inv_set = NULL;
  Object *obj = NULL;
  Id *ids = NULL;
  int n = 0;
  int i = 0;

  if (!game) return ERROR;
  
  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  current_space = game_get_space(game, player_location);
  if (!current_space) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  inv_set = inventory_get_objects(player_get_backpack(game_get_player(game)));
  if (!inv_set) return ERROR;

  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);
  if (!ids || n <= 0) return ERROR;

  for (i = 0; i < n; i++) {
    obj = game_get_object(game, ids[i]);
    if (obj != NULL && strcasecmp(object_get_name(obj), arg) == 0) {
      carried_object_id = ids[i];
      break;
    }
  }

  if (carried_object_id == NO_ID) return ERROR;

  obj = game_get_object(game, carried_object_id);
  if (!obj) return ERROR;

  return handle_drop_object(game, obj, current_space);
}

/* Moves the player to the space in the direction specified by the command argument if there is one */
Status game_actions_move(Game *game) {
  Id current_space = NO_ID;
  Id next_space = NO_ID;
  Direction dir = UNKNOWN_DIR;
  char *arg = NULL;
  Command *cmd = NULL;
  Character *aux_character = NULL;
  Character *follower = NULL;
  Id player_id = NO_ID;
  Player *aux_player = NULL;
  int i = 0;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg) return ERROR;

  if (strcasecmp(arg, "north") == 0 || strcasecmp(arg, "n") == 0)
    dir = N;
  else if (strcasecmp(arg, "south") == 0 || strcasecmp(arg, "s") == 0)
    dir = S;
  else if (strcasecmp(arg, "east") == 0 || strcasecmp(arg, "e") == 0)
    dir = E;
  else if (strcasecmp(arg, "west") == 0 || strcasecmp(arg, "w") == 0)
    dir = W;
  else if (strcasecmp(arg, "up") == 0 || strcasecmp(arg, "u") == 0)
    dir = U;
  else if (strcasecmp(arg, "down") == 0 || strcasecmp(arg, "d") == 0)
    dir = D;
  else
    return ERROR;

  current_space = game_get_player_location(game);

  if (!game_get_connection_status(game, current_space, dir))
    return ERROR;

  next_space = game_get_connection(game, current_space, dir);

  if (next_space == NO_ID)
    return ERROR;

  /* Mover al jugador */
  if (game_set_player_location(game, next_space) == ERROR)
    return ERROR;
  
  /* Buscar follower y moverlo al mismo espacio */
  player_id = player_get_id(game_get_player(game));

  for (i = 0; i < MAX_CHARACTERS; i++) {
    aux_character = game_get_character_by_index(game, i);
    if (!aux_character) break;
    if (character_get_following(aux_character) == player_id && character_get_health(aux_character) > 0) {
      follower = aux_character;
      space_del_character(game_get_space(game, current_space), character_get_id(follower));
      space_add_character(game_get_space(game, next_space), character_get_id(follower), character_is_friendly(follower));
    }
  }

  /* Buscar team mate y moverlo al mismo espacio */
  for (i = 0; i < MAX_PLAYERS; i++) {
    aux_player = game_get_player_by_index(game, i);
    if (!aux_player) break;

    if (aux_player == game_get_player(game)) continue; /* No mover al jugador activo otra vez */

    if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {
      player_set_location(aux_player, next_space);

      /* Mover followers del team mate */
      for (i = 0; i < MAX_CHARACTERS; i++) {
        aux_character = game_get_character_by_index(game, i);
        if (!aux_character) break;
        if (character_get_following(aux_character) == player_get_id(aux_player) && character_get_health(aux_character) > 0) {
          follower = aux_character;
          space_del_character(game_get_space(game, current_space), character_get_id(follower));
          space_add_character(game_get_space(game, next_space), character_get_id(follower), character_is_friendly(follower));
        }
      }
    }
  }
  return OK;
}

/* Inspects an object in the current space*/
Status game_actions_inspect(Game *game) {
  Command *cmd = NULL;
  char *arg = NULL;
  Space *current_space = NULL;
  Id *objs = NULL;
  int i = 0;
  Object *obj = NULL;
  int n_objs = 0;
  Set *inv = NULL;
  Id *ids = NULL;
  int n_ids = 0;

  Id player_id = NO_ID;
  Player *aux_player = NULL;

  if (!game) return ERROR; /* Error control */

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg) return ERROR;

  /* Gets player location */
  current_space = game_get_space(game, game_get_player_location(game));
  if (!current_space) return ERROR;

  /* Gets the description of the object if it is located in the current space */
  n_objs = space_get_number_of_objects(current_space);
  objs = space_get_objects(current_space);

  for (i = 0; i < n_objs; i++) {
    obj = game_get_object(game, objs[i]);
    if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
      game_set_last_object_description(game, object_get_description(obj));
      return OK;
    }
  }

  /* If the object is not in the current space, checks if it is in the player's inventory */
  inv = inventory_get_objects(player_get_backpack(game_get_player(game)));
  if (inv) {
    ids = set_get_ids(inv);
    n_ids = set_get_n_ids(inv);

    for (i = 0; i < n_ids; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
        game_set_last_object_description(game, object_get_description(obj));
        return OK;
      }
    }
  }
  
  /* If the object is not in the player's inventory, check if it is in the team's inventory */
  player_id = player_get_id(game_get_player(game));

  for (i = 0; i < MAX_PLAYERS; i++) {
    aux_player = game_get_player_by_index(game, i);
    if (!aux_player) break;

    if (aux_player != game_get_player(game)) {
      if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {

        inv = inventory_get_objects(player_get_backpack(aux_player));
        if (inv) {
          ids = set_get_ids(inv);
          n_ids = set_get_n_ids(inv);

          for (i = 0; i < n_ids; i++) {
            obj = game_get_object(game, ids[i]);
            if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
              game_set_last_object_description(game, object_get_description(obj));
              return OK;
            }
          }
        }
      }
    }
  }

  return ERROR; /* Did not find the object neither in the space nor in the inventory */
}

/* Makes the player attack the enemy character in the current space */
Status game_actions_attack(Game *game) {
  Player *p = NULL;
  Player *mate[MAX_PLAYERS];
  Character *c = NULL;
  Character *follower = NULL;
  Character *followers[MAX_CHARACTERS];
  Character *aux = NULL;
  Command *cmd = NULL;
  Player *aux_player = NULL;
  char *arg = NULL;
  Id player_id = NO_ID;
  int player_enemy, player_character;
  int i = 0;
  int n_followers = 0;
  int damage = 0;

  if (!game) return ERROR;
  
  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  p = game_get_player(game);
  if (!p) return ERROR;

  player_id = player_get_id(p);
  if (player_id == NO_ID) return ERROR;

  /* Buscar al enemigo por nombre */
  c = game_get_character_by_name(game, arg);
  if (!c) return ERROR;

  /* Verificar que el enemigo está en el mismo espacio que el jugador */
  if (game_get_character_location(game, character_get_id(c)) != game_get_player_location(game))
    return ERROR;

  /* No se puede atacar a personajes amigos o muertos */
  if (character_is_friendly(c) || character_get_health(c) <= 0) return ERROR;

  /* Buscar si hay un follower */
  for (i = 0; i < MAX_CHARACTERS; i++) {
    aux = game_get_character_by_index(game, i);
    if(!aux) break;
    if (aux && character_get_following(aux) == player_id && character_get_health(aux) > 0) {
      followers[n_followers++] = aux;
    }
  }

  player_enemy = rand() % 10; /* 0-9 */
  player_character = rand() % 2; /* 0 o 1 */

  if (player_enemy <= 4) {
    /* Gana el enemigo: inflige daño al jugador o al follower (50/50) */
    if (n_followers > 0 && player_character == 1) {
      follower = followers[rand() % n_followers];
      /* Daño al follower del jugador actual que toca*/
      character_set_health(follower, character_get_health(follower) - 1);


    } else {
      /* Daño al jugador */
      if (player_get_team(p) != NO_ID) {
        for (i = 0; i < MAX_PLAYERS; i++) {
          aux_player = game_get_player_by_index(game, i);
          if (!aux_player) break;
          if (aux_player != game_get_player(game)) {
            if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {
              mate[0] = p;
              mate[1] = aux_player;
              p = mate[rand() % 2];

              player_set_health(p, player_get_health(p) - 1);
              break;
            }
          }
        }
      }
      else {
        player_set_health(p, player_get_health(p) - 1);
      }
    }

    /* Si el jugador muere, fin del juego */
    if (player_get_health(p) <= 0) {
      game_set_finished(game, TRUE);
    } else {
      Player *team = game_player_get_team(game);
      if (team != NULL && player_get_health(team) <= 0) {
        game_set_finished(game, TRUE);
      }
    }
  } else {
    /* Gana el jugador: el follower del jugador actual ayuda si existe */
    damage = 1 + n_followers;
    
    if (player_get_team(p) != NO_ID) damage++; /* Bonus por tener team */

    if (character_get_health(c) < damage)
      damage = character_get_health(c);

    character_set_health(c, character_get_health(c) - damage);
  }

  return OK;
}

/* Makes the player interact with a friendly character by chat */
Status game_actions_chat(Game *game) {
  Character *c = NULL;
  Id player_location = NO_ID;
  Command *last_cmd = NULL;
  Id character_location = NO_ID;
  char *arg = NULL;

  if (!game) return ERROR;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  c = game_get_character_by_name(game, arg);

  if(!c || character_is_friendly(c) == FALSE || character_get_health(c) <= 0) return ERROR;

  character_location = game_get_character_location(game, character_get_id(c));
  if (character_location != player_location) return ERROR;

  game_set_last_message(game, character_get_message(c));
  
  return OK;
}

/* Recruits a friendly character in the current space to follow the player */
Status game_actions_recruit(Game *game) {
  Character *c = NULL;
  Id player_location = NO_ID;
  Command *last_cmd = NULL;
  Id character_location = NO_ID;
  Id current_player_id = NO_ID;
  char *arg = NULL;

  if (!game) return ERROR;

  current_player_id = player_get_id(game_get_player(game));
  if (current_player_id == NO_ID) return ERROR;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  c = game_get_character_by_name(game, arg);

  if(!c || character_is_friendly(c) == FALSE) return ERROR;
  if(character_get_following(c) != NO_ID) return ERROR;

  character_location = game_get_character_location(game, character_get_id(c));
  if (character_location != player_location) return ERROR;

  character_set_following(c, player_get_id(game_get_player(game)));

  return OK;
}

/* Abandons a recruited character or a team mate */
Status game_actions_abandon(Game *game) {
  Character *c = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;
  Player *player = NULL;
  Id current_player_id = NO_ID;

  if (!game) return ERROR;

  player = game_get_player(game);
  if (!player) return ERROR;

  current_player_id = player_get_id(player);
  if (current_player_id == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  /* First character */
  c = game_get_character_by_name(game, arg);
  if (c) {
    if (character_get_following(c) == NO_ID) return ERROR;
    if (character_get_following(c) != current_player_id) return ERROR;
    character_set_following(c, NO_ID);
    return OK;
  }

  return ERROR; /* No se encontró un personaje con ese nombre, o no es un seguidor del jugador */
}

/* Opens a named link with a named object in the current space, if possible */
Status game_actions_open(Game *game) {
  Command *last_cmd = NULL;
  char *link_name = NULL;
  char *obj_name = NULL;
  Player *player = NULL;
  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0;
  int i = 0;
  Object *obj = NULL;
  Link *link = NULL;
  Id object_id = NO_ID;
  Id player_location = NO_ID;

  Id player_id = NO_ID;
  Player *aux_player = NULL;
  Bool has_team = FALSE;
  Set *inv_team = NULL;
  Id *ids_team = NULL;
  int n_team = 0;

  Bool not_inventory = FALSE;

  if (!game) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  link_name = command_get_arg(last_cmd);
  obj_name = command_get_arg2(last_cmd);
  if (!link_name || link_name[0] == '\0' || !obj_name || obj_name[0] == '\0')
    return ERROR;

  player = game_get_player(game);
  if (!player) return ERROR;

  player_location = game_get_player_location(game); 
  if (player_location == NO_ID) return ERROR;

  inv_set = inventory_get_objects(player_get_backpack(player));
  if (!inv_set)
    not_inventory = TRUE;

  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);


  player_id = player_get_id(game_get_player(game));

  for (i = 0; i < MAX_PLAYERS; i++) {
    aux_player = game_get_player_by_index(game, i);
    if (!aux_player) break;

    if (aux_player != game_get_player(game)) {
      if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {

        inv_team = inventory_get_objects(player_get_backpack(aux_player));
        if (inv_team) {
          ids_team = set_get_ids(inv_team);
          n_team = set_get_n_ids(inv_team);
        }
        has_team = TRUE;
      }
    }
  }
  
  if (!ids || n <= 0)
    not_inventory = TRUE;
  else {
    for (i = 0; i < n; i++) { 
      obj = game_get_object(game, ids[i]);
      if (obj != NULL && strcasecmp(object_get_name(obj), obj_name) == 0) {
        object_id = ids[i];
        break;
      }
    }
  }

  if (not_inventory == TRUE || object_id == NO_ID || !obj) {
    /* The player does not have the object. We look in the team inventory */
    if (has_team == FALSE) return ERROR;

    n = n_team;
    ids = ids_team;

    for (i = 0; i < n; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj != NULL && strcasecmp(object_get_name(obj), obj_name) == 0) {
        object_id = ids[i];
        break;
      }
    }
  }

  if (object_id == NO_ID || !obj) return ERROR;

  /* The player has the object */
  if (object_get_open(obj) == NO_ID) return ERROR;

  link = game_get_link_by_name(game, link_name);
  if (!link) return ERROR;

  if (link_get_origin(link) != player_location && link_get_destination(link) != player_location)
    return ERROR;

  if (object_get_open(obj) != link_get_id(link)) return ERROR;

  return link_set_open(link, TRUE);

}

/* Uses an object on the player or a friendly character */
Status game_actions_use(Game *game) {
  Id player_location = NO_ID;
  Id object_id = NO_ID;
  Object *obj = NULL;
  Player *p = NULL;
  Character *c = NULL;
  int i = 0;
  Command *last_cmd = NULL;
  char *arg = NULL;
  char *arg2 = NULL;
  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0;
  Id char_location = NO_ID;

  Id player_id = NO_ID;
  Player *aux_player = NULL;
  Player *object_owner = NULL;
  Bool has_team = FALSE;
  Set *inv_team = NULL;
  Id *ids_team = NULL;
  int n_team = 0;
  
  Bool not_inventory = FALSE;

  if (!game) return ERROR;

  p = game_get_player(game);
  if (!p) return ERROR;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  player_id = player_get_id(game_get_player(game));

  for (i = 0; i < MAX_PLAYERS; i++) {
    aux_player = game_get_player_by_index(game, i);
    if (!aux_player) break;

    if (aux_player != game_get_player(game)) {
      if (player_get_team(aux_player) == player_id || player_get_team(game_get_player(game)) == player_get_id(aux_player)) {

        inv_team = inventory_get_objects(player_get_backpack(aux_player));
        if (inv_team) {
          ids_team = set_get_ids(inv_team);
          n_team = set_get_n_ids(inv_team);
        }
        has_team = TRUE;
        break;
      }
    }
  }
  
  /* Get the object from the player's inventory */
  inv_set = inventory_get_objects(player_get_backpack(p));
  if (!inv_set)
    not_inventory = TRUE;

  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);
  
  if (!ids || n <= 0)
    not_inventory = TRUE;
  else {
    /* Find the object with the given name */
    for (i = 0; i < n; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
        object_id = ids[i];
        object_owner = p;
        break;
      }
    }
  }

  if (not_inventory == TRUE || object_id == NO_ID || !obj) {
    /* The player does not have the object. We look in the team inventory */
    if (has_team == FALSE) return ERROR;

    n = n_team;
    ids = ids_team;

    for (i = 0; i < n; i++) {
      obj = game_get_object(game, ids[i]);
      if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
        object_id = ids[i];
        object_owner = aux_player;
        break;
      }
    }
  }

  if (object_id == NO_ID || !obj || !object_owner) return ERROR;

  /* Check if object is usable (health != 0) */
  if (object_get_health(obj) == 0) return ERROR;

  /* Get the optional second argument */
  arg2 = command_get_arg2(last_cmd);

  /* Determine who will be affected by the object */
  if (arg2 && arg2[0] != '\0') {
    /* Use object on a character */
    c = game_get_character_by_name(game, arg2);
    if (!c) return ERROR;

    /* Verify the character is in the same space and is friendly */
    char_location = game_get_character_location(game, character_get_id(c));
    if (char_location != player_location) return ERROR;

    if (!character_is_friendly(c)) return ERROR;

    /* Check if character is following the player */
    if (character_get_following(c) != player_get_id(p)) return ERROR;

    /* Apply health to the character */
    if (character_get_health(c) + object_get_health(obj) <= 0){
      character_set_health(c, 0);
    }
    else
      character_set_health(c, character_get_health(c) + object_get_health(obj));

  } else {
    /* Use object on the player */
    player_modify_health(p, object_get_health(obj));
    if (player_get_health(p) <= 0){
      game_set_finished(game, TRUE);
    }
  }

  /* Remove the object from the owner's inventory and the game */
  player_del_object(object_owner, object_id);

  return OK;
}

Status game_actions_colab(Game *game) {
  Player *player1 = NULL;
  Player *player2 = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  player1 = game_get_player(game);
  if (!player1) return ERROR;

  player2 = game_get_player_by_name(game, arg);
  if (!player2) return ERROR;

  if (strcasecmp(player_get_name(player1), player_get_name(player2)) == 0) return ERROR;

  if (player_get_location(player1) != player_get_location(player2)) return ERROR;

  if (player_get_team(player1) != NO_ID || player_get_team(player2) != NO_ID) return ERROR;

  player_set_team(player1, player_get_id(player2));
  player_set_team(player2, player_get_id(player1));

  if (player_get_team(player1) == NO_ID || player_get_team(player2) == NO_ID) return ERROR;

  return OK;
}

Status save_game_state(Game *game, const char *filename) {
  if (!game || !filename || filename[0] == '\0') return ERROR;

  return game_management_save(game, (char *) filename);
}

Status load_game_state(Game *game, const char *filename) {
  if (!game || !filename || filename[0] == '\0') return ERROR;

  return game_management_load(game, (char *) filename);
}