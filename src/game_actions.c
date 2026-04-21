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

    default:
      break;
  }

  return OK;
}

/*///////////////////////////////////////////////////////////////////////*/
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
        if (player_add_object(game_get_player(game), object_id) == ERROR) return ERROR;
        space_del_object(current_space, object_id);
        return OK;
      }
    }
  }

  return ERROR;
}

/*///////////////////////////////////////////////////////////////////////////////*/
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

  if (player_del_object(game_get_player(game), carried_object_id) == ERROR) return ERROR;

  space_add_object(current_space, carried_object_id);
  game_set_object_location(game, player_location, carried_object_id);

  return OK;
}

/*///////////////////////////////////////////////////////////////////////////////*/
/*Moves the player to the space in the direction specified by the command argument if there is one */
Status game_actions_move(Game *game) {
  Id current_space = NO_ID;
  Id next_space = NO_ID;
  Direction dir = UNKNOWN_DIR;
  char *arg = NULL;
  Command *cmd = NULL;

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
  else
    return ERROR;

  current_space = game_get_player_location(game);

  if (!game_connection_is_open(game, current_space, dir))
    return ERROR;

  next_space = game_get_connection(game, current_space, dir);

  if (next_space == NO_ID)
    return ERROR;

  return game_set_player_location(game, next_space);
}

/*///////////////////////////////////////////////////////////////////////////////*/
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
  Id loc = NO_ID;
  Command *cmd = NULL;
  char *arg = NULL;
  int r;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  p = game_get_player(game);
  loc = game_get_player_location(game);
  /* Buscamos al personaje en la sala actual */
  c = game_get_character_by_name(game, arg);

  if(!c /*Y NO ESTA EN EL MISMO ESPACIO*/) return ERROR;
  if(character_is_friendly(c) || character_get_health(c) <= 0) return ERROR; /*error control: el personaje es amigo, no se puede atacar*/
  
  r = rand() % 10; /* Número entre 0 y 9 */
    
  if (r >= 0 && r <= 4) {
  /* Gana el adversario: pierde el jugador */
    player_set_health(p, player_get_health(p) - 1);
  
  /* Si el jugador llega a 0, termina el juego */
    if (player_get_health(p) <= 0) {
      game_set_finished(game, TRUE); /* marks game as finished */
    }
  } else {
  /* Gana el jugador: pierde el personaje */
    if (character_get_following(c) != NO_ID) {
    
      character_set_health(c, character_get_health(c) - 2);
    }
    else
      character_set_health(c, character_get_health(c) - 1);
    }
  return OK;
}
/*/////////////AÑADIR ESPECIFICO PERSONAJE*/
/*   Makes the player interact with a friendly character by chat */
Status game_actions_chat(Game *game) {
  Character *c = NULL;
  Id loc = NO_ID;
  Command *cmd = NULL;
  char *arg = NULL;

  int num_characters = 0;
  int i = 0;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  loc = game_get_player_location(game);

  c = game_get_character_by_name(game, arg);

  if (!c /*Y NO ESTA EN EL MISMO ESPACIO*/|| !character_is_friendly(c)) return ERROR;

  game_set_last_message(game, character_get_message(c));
  
  return OK;
}
/*////////////AÑADIR ESPECIFICO PERSONAJE CON EL SET DE LA F5*/
/*   Recruits a friendly character in the current space to follow the player */
Status game_actions_recruit(Game *game) {
  Character *c = NULL;
  Id player_loc = NO_ID;
  Command *cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  player_loc = game_get_player_location(game);

  c = game_get_character_by_name(game, arg);
  if(!c /*Y NO ESTA EN EL MISMO ESPACIO*/) return ERROR; /*error control: el personaje no está en la sala*/
  if(!character_is_friendly(c)) return ERROR; /*error control: el personaje no es amigo*/ 

  character_set_following(c, player_get_id(game_get_player(game)));

  return OK;
}

/*  Abandons the character that you have previously recruited*/
Status game_actions_abandon(Game *game) {
  Character *c = NULL;
  Id player_loc = NO_ID;
  Id player_id = NO_ID;
  Command *cmd = NULL;
  char *arg = NULL;

  if (!game) return ERROR;

  cmd = game_get_last_command(game);
  if (!cmd) return ERROR;

  arg = command_get_arg(cmd);
  if (!arg || arg[0] == '\0') return ERROR;

  player_loc = game_get_player_location(game);
  player_id = player_get_id(game_get_player(game));

  /* Get the character in the player's current space */
  c = game_get_character_by_name(game, arg);

  if (!c /*Y NO ESTA EN EL MISMO ESPACIO*/) return ERROR;

  /* Check if the character is friendly and following the player */
  if (!character_is_friendly(c) || character_get_following(c) != player_id) return ERROR;
  
  /* Make the character stop following the player */
  character_set_following(c, NO_ID);

  return OK;
}