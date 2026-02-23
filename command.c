/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Jose Miguel Romero Oubina
 * @version 0
 * @date 14-02-2026
 * @copyright GNU Public License
 */

#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define CMD_LENGHT 30

/**
 * Dictionary with control commands and its respective job or char * for comparison, for use in command_get_user_input
 */
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"}, {"t", "Take"}, {"d", "Drop"}};

/**
 * @brief Command
 * 
 * This struct stores all the information related to a command.
 */
struct _Command {
  CommandCode code; /*!< Name of the command */
};

/** Initializes a Command struct, reserves dynamic memory for it and returns a pointer to this 
 */
Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)calloc(1,sizeof(Command));/*allocates memory*/
  if (newCommand == NULL) {/* error control*/
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;

  return newCommand;
}
/*Destroys and frees the memory occupied by a Command struct*/
Status command_destroy(Command* command) {
  if (!command) {/* error control*/
    return ERROR;
  }

  free(command);
  command = NULL;/*command = NULL just in case*/
  return OK;
}
/*Sets the CommandCode introduced as the new value for the Command pointer introduced.*/
Status command_set_code(Command* command, CommandCode code) {
  if (!command) {/*error control*/
    return ERROR;
  }

  command->code=code;

  return OK;
}
/*Obtains the contents of a Command struct pointer*/
CommandCode command_get_code(Command* command) {
  if (!command) {/*error control*/
    return NO_CMD;
  }
  return command->code;
}
/*Reads what the user types and sets the command to UNKNOWN if it doesn’t match anything, or to the correct command if it does.*/
Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;/*initializating*/
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) {/*error control*/
    return ERROR;
  }

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");/*check the command*/
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) {
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i + NO_CMD;
      } else {
        i++;
      }
    }
    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, EXIT);
}
