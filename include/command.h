/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 06-03-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

/**
 * @brief Number of command types (short and long)
 */
#define N_CMDT 2

/**
 * @brief Number of commands available in the game
 */
#define N_CMD 10

/**
 * @brief Defines the type of command input: short (CMDS) or long (CMDL)
 */
typedef enum {
  CMDS, /**< Short version of the command (e.g. "e") */
  CMDL  /**< Long version of the command (e.g. "Exit") */
} CommandType;

/**
 * @brief Identifies each possible command in the game
 */
typedef enum {
  NO_CMD  = -1, /**< No command assigned */
  UNKNOWN,      /**< Unknown or unrecognized command */
  EXIT,         /**< Exit the game */
  TAKE,         /**< Take an object */
  DROP,         /**< Drop an object */
  ATTACK,       /**< Attack a character */
  CHAT,         /**< Chat with a character */
  MOVE,         /**< Move to an adjacent space */
  INSPECT,      /**< Inspect a space or object */
  RECRUIT,      /**< Recruit a character to follow the player */
  ABANDON       /**< Abandon a character following the player */ 
} CommandCode;

/**
 * @brief Stores all the information related to a command
 */
typedef struct _Command Command;

/**
 * @brief It creates a new Command, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @return a pointer to the new Command, initialized, or NULL if allocation failed
 */
Command* command_create();

/**
 * @brief It destroys a Command, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command that must be destroyed
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status command_destroy(Command* command);

/**
 * @brief It sets the code of a Command
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @param code the CommandCode to be assigned to the Command
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the code of a Command
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @return the CommandCode stored in the Command, or NO_CMD if the pointer is NULL
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It gets the argument of a Command
 * @author Jose Miguel Romero Oubina
 *
 * @param command a pointer to the Command
 * @return a string with the argument stored in the Command, or NULL if there is none
 */
char* command_get_arg(Command* command);

/**
 * @brief It reads the user input and sets the corresponding CommandCode in the Command struct
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @return OK if everything goes well, or ERROR if there was some mistake
 */
Status command_get_user_input(Command* command);

#endif /* COMMAND_H */