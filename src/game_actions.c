/**
 * @brief It implements the game update through user actions
 *
 * @file game_actions.c
 * @author Jose Miguel Romero Oubina
 * @version 3
 * @date 01-04-2026
 * @copyright GNU Public License
 */

#include "game_actions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/** @brief Pointer to the log file */
extern FILE *g_logfile;

/** @brief Command string table */
extern char *cmd_to_str[N_CMD][N_CMDT];

/**
 * @brief Does nothing when the command is not recognized
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 */
void game_actions_unknown(Game *game);

/**
 * @brief Handles exiting the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 */
void game_actions_exit(Game *game);

/**
 * @brief Makes the player pick up the named object in the current space
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was picked up, ERROR otherwise
 */
Status game_actions_take(Game *game);

/**
 * @brief Makes the player drop their named carried object into the current space
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was dropped, ERROR otherwise
 */
Status game_actions_drop(Game *game);

/**
 * @brief Makes the player attack if the character in the space is not friendly
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the attack was performed, ERROR otherwise
 */
Status game_actions_attack(Game *game);

/**
 * @brief Makes the player interact with a friendly character by chat
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the chat was performed, ERROR otherwise
 */
Status game_actions_chat(Game *game);

/**
 * @brief Moves the player to the next space in the given direction if it exists and is open
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the player moved, ERROR otherwise
 */
Status game_actions_move(Game *game);

/**
 * @brief Inspects a named object in the current space or in the player's inventory
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return OK if the object was inspected, ERROR otherwise
 */
Status game_actions_inspect(Game *game);

/**
 * @brief Recruits a friendly character in the current space to follow the player
 * 
 * @param game a pointer to the Game struct
 * @return OK if the character was recruited, ERROR otherwise
 */
Status game_actions_recruit(Game *game);

/**
 * @brief Abandons the character that you have previously recruited
 * 
 * @param game a pointer to the Game struct
 * @return OK if the character was abandoned, ERROR otherwise
 */
Status game_actions_abandon(Game *game);

/**
 * @brief Uses an object on the player or a friendly character
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

/* Implementation of auxiliary functions */

/**
 * @brief Checks if an object can be taken by the player
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @return TRUE if the object can be taken, FALSE otherwise
 */
Bool can_take_object(Game *game, Object *obj) {
  if (!game || !obj) return FALSE;
  
  /* Check if object is movable */
  if (!object_get_movable(obj)) return FALSE;
  
  /* Check dependency */
  if (object_get_dependency(obj) != NO_ID) {
    if (!inventory_has_object(player_get_backpack(game_get_player(game)), object_get_dependency(obj))) return FALSE;
  }
  
  return TRUE;
}

/**
 * @brief Handles the logic of taking an object, including dependencies and links
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @param current_space a pointer to the current Space
 * @return OK if the object was taken, ERROR otherwise
 */
Status handle_take_object(Game *game, Object *obj, Space *current_space) {
  Id object_id;
  
  if (!game || !obj || !current_space) return ERROR;
  
  object_id = object_get_id(obj);
  
  if (player_add_object(game_get_player(game), object_id) == ERROR) return ERROR;
  space_del_object(current_space, object_id);
  
  /* Add health to player */
  player_modify_health(game_get_player(game), object_get_health(obj));
  
  /* Open link if applicable */
  if (object_get_open(obj) != NO_ID) {
    Link *link = game_get_link(game, object_get_open(obj));
    if (link) link_set_open(link, TRUE);
  }
  
  return OK;
}

/**
 * @brief Handles the logic of dropping an object, including dependent objects
 * @author Iñaki López Rocha
 *
 * @param game a pointer to the Game struct
 * @param obj a pointer to the Object
 * @param current_space a pointer to the current Space
 * @return OK if the object was dropped, ERROR otherwise
 */
Status handle_drop_object(Game *game, Object *obj, Space *current_space) {
  Id object_id, player_location;
  Set *inv_set = NULL;
  Id *ids = NULL;
  int n = 0, i = 0, num_to_drop = 0, j = 0;
  Id *to_drop = NULL;
  Object *dep_obj = NULL;
  
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
  if (!ids || n <= 0) return OK;
  
  /* Count dependent objects */
  for (i = 0; i < n; i++) {
    dep_obj = game_get_object(game, ids[i]);
    if (dep_obj && object_get_dependency(dep_obj) == object_id) {
      num_to_drop++;
    }
  }
  
  if (num_to_drop == 0) return OK;
  
  to_drop = (Id*)malloc(sizeof(Id) * num_to_drop);
  if (!to_drop) return OK; /* Memory error, but object was dropped */
  
  /* Collect ids of dependent objects */
  j = 0;
  for (i = 0; i < n; i++) {
    dep_obj = game_get_object(game, ids[i]);
    if (dep_obj && object_get_dependency(dep_obj) == object_id) {
      to_drop[j++] = ids[i];
    }
  }
  
  /* Drop dependent objects */
  for (i = 0; i < num_to_drop; i++) {
    player_del_object(game_get_player(game), to_drop[i]);
    space_add_object(current_space, to_drop[i]);
    game_set_object_location(game, player_location, to_drop[i]);
  }
  
  free(to_drop);
  return OK;
}

Status game_actions_update(Game *game, Command *command) {
  CommandCode cmd;

  game_set_last_command(game, command);

  cmd = command_get_code(command);

  switch (cmd) {
    case UNKNOWN:
      game_set_last_status(game, OK);
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

    case USE:
      game_set_last_status(game, game_actions_use(game));
      break;

    default:
      break;
  }

  /* Log the command if logging is enabled */
  if (g_logfile != NULL && cmd != UNKNOWN && cmd != NO_CMD) {
    char arg[WORD_SIZE] = "";
    if (command_get_arg(command) != NULL) {
      strcpy(arg, command_get_arg(command));
    }
    if (arg[0] != '\0') {
      fprintf(g_logfile, "%s %s: %s\n", cmd_to_str[cmd][CMDL], arg, game_get_last_status(game) == OK ? "OK" : "ERROR");
    } else {
      fprintf(g_logfile, "%s: %s\n", cmd_to_str[cmd][CMDL], game_get_last_status(game) == OK ? "OK" : "ERROR");
    }
    fflush(g_logfile);
  }

  return OK;
}

/*   Makes the player pick up the named object in the current space */
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

/*   Makes the player drop the named object into the current space */
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

/*Moves the player to the space in the direction specified by the command argument if there is one */
Status game_actions_move(Game *game) {
  Id current_space = NO_ID;
  Id next_space = NO_ID;
  Direction dir = UNKNOWN_DIR;
  char *arg = NULL;
  Command *cmd = NULL;
  Character *aux = NULL;
  Character *follower = NULL;
  Id player_id = NO_ID;
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

  if (!game_connection_is_open(game, current_space, dir))
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
    aux = game_get_character_by_index(game, i);
    if (!aux) break;
    if (character_get_following(aux) == player_id && character_get_health(aux) > 0) {
      follower = aux;
      space_del_character(game_get_space(game, current_space), character_get_id(follower));
      space_add_character(game_get_space(game, next_space), character_get_id(follower));
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

  if (!game) return ERROR; /*error control*/

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg) return ERROR;

  /*get player location*/
  current_space = game_get_space(game, game_get_player_location(game));
  if (!current_space) return ERROR;

  /*gets the description of the object is it is located in the current space*/
  n_objs = space_get_number_of_objects(current_space);
  objs = space_get_objects(current_space);

  for (i = 0; i < n_objs; i++) {
    obj = game_get_object(game, objs[i]);
    if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
      game_set_last_object_description(game, object_get_description(obj));
      return OK;
    }
  }

  /*if the object is not in the current space, checks if it is in the player's inventory*/
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

  return ERROR; /*did not find the object neither in the space nor in the inventory*/
}

/*   Makes the player attack the enemy character in the current space */
Status game_actions_attack(Game *game) {
  Player *p = NULL;
  Character *c = NULL;
  Character *follower = NULL;
  Character *followers[MAX_CHARACTERS];
  Character *aux = NULL;
  Command *cmd = NULL;
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

  /* Buscar automáticamente si hay un follower */
  for (i = 0; i < MAX_CHARACTERS; i++) {
    aux = game_get_character_by_index(game, i);
    if(!aux) break;
    if (aux && character_get_following(aux) == player_id && character_get_health(aux) > 0) {
      followers[n_followers++] = aux;
    }
  }

  player_enemy    = rand() % 10; /* 0-9 */
  player_character = rand() % 2; /* 0 o 1 */

  if (player_enemy <= 4) {
    /* Gana el enemigo: inflige daño al jugador o al follower (50/50) */
    if (n_followers > 0 && player_character == 1) {
      follower = followers[rand() % n_followers];
      /* Daño al follower que toca*/
      character_set_health(follower, character_get_health(follower) - 1);
    } else {
      /* Daño al jugador */
      player_set_health(p, player_get_health(p) - 1);
    }

    /* Si el jugador muere, fin del juego */
    if (player_get_health(p) <= 0) {
      game_set_finished(game, TRUE);
    }
  } else {
    /* Gana el jugador: el follower ayuda si existe */
      damage = 1 + n_followers;
      character_set_health(c, character_get_health(c) - damage);
  }

  return OK;
}

/*   Makes the player interact with a friendly character by chat */
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

/*   Recruits a friendly character in the current space to follow the player */
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
  /*if(character_get_following(c) != NO_ID) return ERROR;*/

  character_location = game_get_character_location(game, character_get_id(c));
  if (character_location != player_location) return ERROR;

  character_set_following(c, player_get_id(game_get_player(game)));

  return OK;
}

/*  Abandons the character that you have previously recruited*/
Status game_actions_abandon(Game *game) {
  Character *c = NULL;
  Command *last_cmd = NULL;
  char *arg = NULL;
  Id current_player_id = NO_ID;

  if (!game) return ERROR;

  current_player_id = player_get_id(game_get_player(game));
  if (current_player_id == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  c = game_get_character_by_name(game, arg);

  if(!c || character_get_following(c) == NO_ID) return ERROR;
  if(character_get_following(c) != current_player_id) return ERROR;

  character_set_following(c, NO_ID);

  return OK;
}

/*  Uses an object on the player or a friendly character */
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

  if (!game) return ERROR;

  p = game_get_player(game);
  if (!p) return ERROR;

  player_location = game_get_player_location(game);
  if (player_location == NO_ID) return ERROR;

  last_cmd = game_get_last_command(game);
  if (!last_cmd) return ERROR;

  arg = command_get_arg(last_cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  /* Get the object from the player's inventory */
  inv_set = inventory_get_objects(player_get_backpack(p));
  if (!inv_set) return ERROR;

  n = set_get_n_ids(inv_set);
  ids = set_get_ids(inv_set);
  
  if (!ids || n <= 0) return ERROR;

  /* Find the object with the given name */
  for (i = 0; i < n; i++) {
    obj = game_get_object(game, ids[i]);
    if (obj && strcasecmp(object_get_name(obj), arg) == 0) {
      object_id = ids[i];
      break;
    }
  }

  if (object_id == NO_ID || !obj) return ERROR;

  /* Check if object is usable (health != 0) */
  if (object_get_health(obj) == 0) return ERROR;

  /* Get the optional second argument (character name) */
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
    character_set_health(c, character_get_health(c) + object_get_health(obj));
  } else {
    /* Use object on the player */
    player_modify_health(p, object_get_health(obj));
  }

  /* Remove the object from the player's inventory and the game */
  player_del_object(p, object_id);

  return OK;
}