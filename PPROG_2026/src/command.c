/**
 *   It implements the command interpreter
 *
 * @file command.c
 * @author Jose Miguel Romero Oubina
 * @version 1
 * @date 02-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "command.h"

#define CMD_LENGHT 30

/**
 * Dictionary with control commands and its respective job or char * for comparison, for use in command_get_user_input
 */
char *cmd_to_str[N_CMD][N_CMDT] = {
 {"", "Unknown"},   /* 0 → UNKNOWN*/
 {"e", "Exit"},     /* 1 → EXIT */
 {"t", "Take"},     /* 2 → TAKE */
 {"d", "Drop"},     /* 3 → DROP */
 {"a", "Attack"},   /* 4 → ATTACK */
 {"c", "Chat"},     /* 5 → CHAT */
 {"m", "Move"},      /* 6 → MOVE */
 {"i", "Inspect"}    /* 7 → INSPECT */
};
/*Command struct*/
struct _Command {
  char *arg;
  CommandCode code; /* Name of the command */
};

/*   It creates a new Command, allocating memory and initializing its members */
Command* command_create() {
  Command* newCommand = NULL;
  newCommand = (Command*)malloc(sizeof(Command));/*allocates memory*/
  if (newCommand == NULL) {/* error control*/
    return NULL;
  }
  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  newCommand->arg = NULL;
  return newCommand;
}

/*   It destroys a Command, freeing the allocated memory */
Status command_destroy(Command* command) {
  if (!command) {/* error control*/
    return ERROR;
  }
  if (command->arg) {
    free(command->arg); /* frees the argument if it exists */
    command->arg = NULL;/*command->arg = NULL just in case*/
  }
free(command);
return OK;
}

/*   It sets the code of a Command */
Status command_set_code(Command* command, CommandCode code) {
  if (!command) {/*error control*/
    return ERROR;
  }
  command->code=code; /* assigns the code to the command */
  return OK;
}

/*   It gets the code of a Command */
CommandCode command_get_code(Command* command) {
  if (!command) {/*error control*/
    return NO_CMD;
  }
return command->code;
}

/*   It gets the argument of a Command */
char *command_get_arg (Command *command) {
  if(!command)
    return NULL;

  return command->arg;
}

/*   It reads the user input and sets the corresponding CommandCode in the Command struct */
Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;/*initializating*/
  int i = 0;
  CommandCode cmd;
  if (!command) {/*error control*/
    return ERROR;
  }
  if(command->arg){
    free(command->arg); /* frees previous argument if exists */
    command->arg = NULL;/*command->arg = NULL just in case*/
}
  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");/*check the command*/
      if (!token) {
        return command_set_code(command, UNKNOWN);/*Error control*/
      }
    cmd = UNKNOWN;
    while (cmd == UNKNOWN && i < N_CMD) { /* iterates through the command dictionary */
      if (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL])) {
        cmd = i; /* match found, assigns the command */
      } else {
        i++;
      }
    }
    token = strtok(NULL, " \n"); /* reads the argument if present */
    if(token){
      command->arg = (char*)malloc(strlen(token) + 1); /* allocates memory for the argument */
      if (command->arg) 
        strcpy(command->arg, token); 
    }
    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, EXIT); /* EOF reached, sets EXIT */
}