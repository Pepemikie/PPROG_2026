/**
 * @brief It defines the game interface
 *
 * @file game.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GAME_H
#define GAME_H

#include "object.h"
#include "player.h"
#include "command.h"
#include "space.h"
#include "types.h"
#include "character.h"
#include "link.h"

#define MAX_SPACES 100 /**< Maximum number of spaces in the game */
#define MAX_OBJECTS 30 /**< Maximum number of objects in the game */
#define MAX_CHARACTERS 8 /**< Maximum number of characters in the game */
#define MAX_LINKS 400 /**< Maximum number of links in the game */
#define MAX_PLAYERS 2 /**< Maximum number of players in the game */

/** @brief It defines the Game struct */
typedef struct _Game Game;

/*
GAME
*/
/**
 * @brief It creates a new Game, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @return a new pointer to a Game struct, initialized
 */
Game* game_create();

/**
 * @brief It creates a Game and loads its data from a file
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param filename a string with the name of the file to read from
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_create_from_file(Game *game, char *filename);

/**
 * @brief It destroys a Game, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_destroy(Game *game);

/**
 * @brief It gets the current turn index 
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @return the index of the active player
 */
int game_get_turn(Game *game);

/**
 * @brief It sets the current turn
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @param turn the index to set as active turn
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_turn(Game *game, int turn);

/**
 * @brief It advances the turn to the next player 
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_next_turn(Game *game);

/**
 * @brief It gets the last command introduced by the user
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return a pointer to the last Command struct
 */
Command* game_get_last_command(Game *game);

/**
 * @brief It sets the last command introduced by the user
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param command a pointer to the Command struct to be stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_command(Game *game, Command *command);

/**
 * @brief It gets the status of the last command executed
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return OK or ERROR depending on the result of the last command
 */
Status game_get_last_status(Game *game);

/**
 * @brief It sets the status of the last command executed
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param status the status to be stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_status(Game *game, Status status);

/**
 * @brief It gets whether the game has finished
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return TRUE if the game is finished, FALSE otherwise
 */
Bool game_get_finished(Game *game);

/**
 * @brief It sets the finished state of the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param finished TRUE to mark the game as finished, FALSE otherwise
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_finished(Game *game, Bool finished);


/*
SPACE
*/

/**
 * @brief It gets a space from the game by its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param id the id of the space to retrieve
 * @return a pointer to the Space with the given id, or NULL if not found
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It adds a space to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space a pointer to the Space to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_space(Game *game, Space *space);





/*
PLAYER
*/
/**
 * @brief It gets the actual player of the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return a pointer to the Player struct
 */
Player *game_get_player(Game *game);

/**
 * @brief It adds a player to the game
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @param player a pointer to the Player to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_player(Game *game, Player *player);

/**
 * @brief It gets the number of players in the game 
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @return the number of players
 */
int game_get_num_players(Game *game);

/**
 * @brief It gets the current location of the player
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return the id of the space where the player is located
 */
Id game_get_player_location(Game *game);

/**
 * @brief It sets the location of the player
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param id the id of the space where the player is going to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_player_location(Game *game, Id id);

/**
 * @brief It gets a player from the game by its index (F13, I3)
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @param index the index of the player in the players array
 * @return a pointer to the Player at the given index, or NULL if not found
 */
Player *game_get_player_by_index(Game *game, int index);






/*
OBJECT
*/
/**
 * @brief It gets an object from the game by its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param id the id of the object to retrieve
 * @return a pointer to the Object with the given id, or NULL if not found
 */
Object* game_get_object(Game* game, Id id);

/**
 * @brief It gets an object from the game by its index
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param index the position of the object in the game's object array
 * @return a pointer to the Object at the given index, or NULL if not found
 */
Object* game_get_object_by_index(Game *game, int index);

/**
 * @brief It gets the location of an object by its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param object_id the id of the object whose location is retrieved
 * @return the id of the space where the object is located
 */
Id game_get_object_location(Game *game, Id object_id);

/**
 * @brief It sets the location of an object in the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space_id the id of the space where the object is going to be placed
 * @param object_id the id of the object to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_object_location(Game *game, Id space_id, Id object_id);

/**
 * @brief It adds an object to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param object a pointer to the Object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_object(Game *game, Object *object);

/**
 * @brief It sets the last object description displayed in the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param description a string with the description to be stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_object_description(Game *game, const char *description);

/**
 * @brief It gets the last object description displayed in the game
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @return a string with the last object description stored in the game
 */
const char *game_get_last_object_description(Game *game);







/*
CHARACTER
*/

/**
 * @brief It gets a character from the game by its id
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param id the id of the character to retrieve
 * @return a pointer to the Character with the given id, or NULL if not found
 */
Character* game_get_character(Game* game, Id id);

/**
 * @brief It gets a character from the game by its index
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param index the position of the character in the game's character array
 * @return a pointer to the Character at the given index, or NULL if not found
 */
Character* game_get_character_by_index(Game *game, int index);

/**
 * @brief It gets the location of a character by its id
 * @author Jose Miguel Romero Oubina
 *
 * @param game a pointer to the Game struct
 * @param character_id the id of the character whose location is retrieved
 * @return the id of the space where the character is located
 */
Id game_get_character_location(Game *game, Id character_id);

/**
 * @brief It sets the location of a character in the game
 * 
 * @param game a pointer to the Game struct
 * @param space_id the id of the space where the character is going to be placed
 * @param object_id the id of the character to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_character_location(Game *game, Id space_id, Id character_id);

/**
 * @brief It adds a character to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param character a pointer to the Character to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It sets the last message displayed in the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param message a string with the message to be stored
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_last_message(Game* game, const char* message);

/**
 * @brief It gets the last message displayed in the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return a string with the last message stored in the game
 */
const char* game_get_last_message(Game* game);

/**
 * @brief It gets a character from the game by its name
 * @author Jose Miguel Romero Oubina
 * 
 * @param game a pointer to the Game struct
 * @param name the name of the character to retrieve
 * @return Character* a pointer to the Character with the given name, or NULL if not found
 */
Character *game_get_character_by_name(Game *game, const char *name);

/**
 * @brief It gets the character located in a given space
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space_id the id of the space to search in
 * @return a pointer to the Character in that space, or NULL if there is none
 */
Character* game_get_character_in_space(Game* game, Id space_id);





/*
LINKS
*/
/**
 * @brief It adds a link to the game
 * @author Jose Miguel Romero Oubina
 * 
 * @param game a pointer to the Game struct
 * @param link a pointer to the Link to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_link(Game *game, Link *link);

/**
 * @brief It gets the id of the destination space given an origin space and a direction
 * @author Jose Miguel Romero Oubina
 * 
 * @param game a pointer to the Game struct
 * @param space_id the id of the origin space
 * @param direction the direction of the link
 * @return the id of the destination space, or NO_ID if not found
 */
Id game_get_connection(Game *game, Id space_id, Direction direction);

/**
 * @brief It checks if the link in a given direction from a space is open
 * @author Jose Miguel Romero Oubina
 * 
 * @param game a pointer to the Game struct
 * @param space_id the id of the origin space
 * @param direction the direction of the link
 * @return TRUE if the link is open, FALSE otherwise
 */
Bool game_connection_is_open(Game *game, Id space_id, Direction direction);

/**
 * @brief It gets a link from the game by its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param id the id of the link
 * @return a pointer to the Link or NULL if not found
 */
Link* game_get_link(Game *game, Id id);

/**
 * @brief It marks a Space as discovered (F12, I3)
 * @author Rodrigo Cruz Asensio
 *
 * @param game a pointer to the Game struct
 * @param space_id the id of the space to discover
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_discover_space(Game *game, Id space_id);

#ifdef DEBUG
/**
 * @brief It prints the data of the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 */
void game_print(Game *game);
#endif
#endif