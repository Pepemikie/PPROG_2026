/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 05-02-2026
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "command.h"
#include "space.h"
#include "types.h"
#include "object.h"
#include "player.h"

#define MAX_SPACES 100

typedef struct _Game {
  Player *player;
  Object *object;
  Space *spaces[MAX_SPACES];
  int n_spaces;
  Command *last_cmd;
  Bool finished;
} Game;

/**
 * @brief Initializes the introduced Game struct and returns OK if it has been created and ERROR if there have been errors
 * @author Profesores PPROG
 * @param Game*  
 * @return Status
 */
Status game_create(Game *game);

/**
 * @brief Initializes the introduced Game struct, loads the spaces as described in the introduced (char * filename), positions the game and the object; returns OK if it has done it and ERROR if there have been errors
 * @author Profesores PPROG
 * @param Game*  
 * @param char * filename
 * @return Status
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief Frees the spaces and the Command struct from game then returns OK
 * @author Profesores PPROG
 * @param Game*  
 * @return OK
 */
Status game_destroy(Game *game);

/**
 * @brief Adds the introduced Space to the list of Spaces currently in game
 * @author Profesores PPROG
 * @param Game*  , Space *
 * @return Status
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief Obtains a Space currently in the game using its Id 
 * @author Profesores PPROG
 * @param Game*  
 * @param Id 
 * @return Space
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief Obtains the player's current position as an Id
 * @author Profesores PPROG
 * @param Game*  
 * @return Id
 */
Id game_get_player_location(Game *game);

/**
 * @brief Obtains the Player object/struct in game
 * @author Jose Miguel Romero Oubina 
 * @param Game*
 * @return Player*
 */
Player *game_get_player(Game *game);

/**
 * @brief Assigns id to game->player_location 
 * @author Profesores PPROG
 * @param Game*  
 * @param Id
 * @return Status: OK, ERROR
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief Getter : Returns the Id for game->object_location
 * @author Profesores PPROG
 * @param Game*  
 * @return Id
 */
Id game_get_object_location(Game *game);

/**
 * @brief Setter : Assigns the location of the object in the game
 * As long as the code supports only one object per game
 * @author Profesores PPROG
 * @param Game*  
 * @param Id
 * @return Status :OK, ERROR
 */
Status game_set_object_location(Game *game, Id id);

/**
 * @brief Returns the object in game
 * @author Jose Miguel Romero Oubina
 * @param Game*
 * @return Object
 */
Object *game_get_object(Game *game);

/**
 * @brief Getter: gets the last command ran in game
 * @author Profesores PPROG
 * @param Game*  
 * @return Command*  
 */
Command* game_get_last_command(Game *game);

/**
 * @brief Setter: sets the last command ran in game
 * @author Profesores PPROG
 * @param Game*  
 * @param Command*  
 * @return Status
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief Getter : Returns if the game's finished on game->finished
 * @author Profesores PPROG
 * @param Game*  
 * @return Bool, TRUE / FALSE
 */
Bool game_get_finished(Game *game);

/**
 * @brief Setter : Sets game->finished as TRUE and returns OK when done
 * @author Profesores PPROG
 * @param Game*  
 * @param Bool finished
 * @return Status, OK
 */
Status game_set_finished(Game *game, Bool finished);

/**
 * @brief Prints the spaces individualy through (space.c) space_print(game->spaces[i]) and then prints in console the location of the object
 * @author Profesores PPROG
 * @param Game*  
 * @return 
 */
void game_print(Game *game);

#endif
