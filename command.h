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

#define N_CMDT 2
#define N_CMD 8
/**
 * To diferentiate between types of commands
 */
typedef enum { CMDS, CMDL } CommandType;
/**
 * Enum to store the specific command and facilitate it's comparison
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, TAKE, DROP, ATTACK, CHAT, MOVE, INSPECT} CommandCode;
/**
 * @brief Command struct
 *
 * This struct stores all the information related to a command.
 */
typedef struct _Command Command;

/**
 * @brief It creates a new Command, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @return a new pointer to a Command struct, initialized
 */
Command* command_create();

/**
 * @brief It destroys a Command, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command that must be destroyed
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_destroy(Command* command);

/**
 * @brief It sets the code of a Command
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @param code the CommandCode to be assigned to the Command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief It gets the code of a Command
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @return the CommandCode stored in the Command struct
 */
CommandCode command_get_code(Command* command);

/**
 * @brief It gets the argument of a Command
 * @author Jose Miguel Romero Oubina
 *
 * @param command a pointer to the Command
 * @return a string with the argument stored in the Command struct
 */
char *command_get_arg(Command *command);

/**
 * @brief It reads the user input and sets the corresponding CommandCode in the Command struct
 * @author Profesores PPROG
 *
 * @param command a pointer to the Command
 * @return OK, if everything goes well or ERROR if there was some mistake
 */
Status command_get_user_input(Command* command);

#endif