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

#define MAX_SPACES 100
#define MAX_OBJECTS 5
#define MAX_CHARACTERS 2

typedef struct _Game Game;

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
 * @brief It gets a space from the game by its id
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param id the id of the space to retrieve
 * @return a pointer to the Space with the given id, or NULL if not found
 */
Space *game_get_space(Game *game, Id id);

/**
 * @brief It gets the player of the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @return a pointer to the Player struct
 */
Player *game_get_player(Game *game);

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

/**
 * @brief It adds a space to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space a pointer to the Space to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_space(Game *game, Space *space);

/**
 * @brief It adds an object to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param object a pointer to the Object to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_object(Game *game, Object *object);

Id game_get_character_location(Game *game, Id character_id);

/**
 * @brief It gets the character located in a given space
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space_id the id of the space to search in
 * @return a pointer to the Character in that space, or NULL if there is none
 */
Character* game_get_character_in_space(Game* game, Id space_id);

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
 * @brief It adds a character to the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param character a pointer to the Character to be added
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_add_character(Game *game, Character *character);

/**
 * @brief It sets the location of a character in the game
 * @author Profesores PPROG
 *
 * @param game a pointer to the Game struct
 * @param space_id the id of the space where the character is going to be placed
 * @param character_id the id of the character to be placed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status game_set_character_location(Game *game, Id space_id, Id character_id);
/*/////////////////////REVISAR//////////////////*/
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