/**
 * @brief It defines the command interpreter interface
 *
 * @file command.h
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 02-03-2026
 * @copyright GNU Public License
 */

#ifndef COMMAND_H
#define COMMAND_H

#include "types.h"

#define N_CMDT 2
#define N_CMD 7

/**
 * To diferentiate between types of commands
 */
typedef enum { CMDS, CMDL } CommandType;

/**
 * Enum to store the specific command and facilitate it's comparison
 */
typedef enum { NO_CMD = -1, UNKNOWN, EXIT, NEXT, BACK , TAKE, DROP} CommandCode;

/**
 * @brief Command struct
 *
 * This struct stores all the information related to a command.
 */
typedef struct _Command Command;

/**
 * @brief Initializes a Command struct, reserves dynamic memory for it and returns a pointer to this 
 * initialized Command
 * @author Profesores PPROG
 *
 * @return Command*   : a new pointer to a Command struct
 */
Command* command_create();

/**
 * @brief Destroys and frees the memory occupied by a Command struct
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if removed, it will
 * return OK
 */
Status command_destroy(Command* command);

/**
 * @brief Sets the CommandCode introduced as the new value for the Command pointer introduced.
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @param Command Code : new CommandCode to set on the Command struct
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if setted, it will
 * return OK
 */
Status command_set_code(Command* command, CommandCode code);

/**
 * @brief Obtains the contents of a Command struct pointer
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if removed, it will
 * return OK
 */
CommandCode command_get_code(Command* command);

/**
 * @brief Obtains the argument of a Command struct pointer
 * @author Jose Miguel Romero Oubina
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Char*: a char string with the argument
 */
char *command_get_arg (Command *command);

/**
 * @brief Will take a pointer to an initialized Command struct, it tries to get user input and checks if that input has new line characters, 
 * if it doesn't have it, it will use command_set_code(Command *, UNKNOWN) to set the Command struct as UNKNOWN abd then it will return an OK Status code;
 * If it has at least one token, it will check the list of commands using (#define N_CMDT as the amount of correlations a command has, by default 2, and #define N_CMD 5 as the amount 
 * of possible commands the game can take from text) then it will set the adecuate command enum for the Command struct.
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Status : OK, ERROR, if the Command pointer does not exist or hasn't been initialized it returns ERROR, if it has user input retrieved , it will
 * return OK
 */
Status command_get_user_input(Command* command);

#endif
