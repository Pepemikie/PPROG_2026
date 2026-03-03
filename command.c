/**
 * @brief It implements the command interpreter
 *
 * @file command.c
 * @author Jose Miguel Romero Oubina
 * @version 0
 * @date 02-03-2026
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
char *cmd_to_str[N_CMD][N_CMDT] = {{"", "No command"}, {"", "Unknown"}, {"e", "Exit"}, {"n", "Next"}, {"b", "Back"},{"t", "Take"},{"d", "Drop"}};

/**
 * @brief Command
 *
 * This struct stores all the information related to a command.
 */
struct _Command {
 /* char *arg;*/
  CommandCode code; /*!< Name of the command */
};

/*command: create*/
/**
 * @brief Initializes a Command struct, reserves dynamic memory for it and returns a pointer to this 
 * initialized Command
 * @author Profesores PPROG
 *
 * @return Command* : a new pointer to a Command struct
 */
Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)malloc(sizeof(Command));/*allocates memory*/
  if (newCommand == NULL) {/* error control*/
    return NULL;
  }

  /* Initialization of an empty command*/
  newCommand->code = NO_CMD;
  /*newCommand->arg = NULL;*/
  return newCommand;
}

/*command: destroy*/
/**
 * @brief Destroys and frees the memory occupied by a Command struct
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if removed, it will
 * return OK
 */
Status command_destroy(Command* command) {
  if (!command) {/* error control*/
    return ERROR;
  }

  free(command);
  command = NULL;/*command = NULL just in case*/
  return OK;
}

/*command: setter*/
/**
 * @brief Sets the CommandCode introduced as the new value for the Command pointer introduced.
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @param CommandCode Code : new CommandCode to set on the Command struct
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if setted, it will
 * return OK
 */
Status command_set_code(Command* command, CommandCode code) {
  if (!command) {/*error control*/
    return ERROR;
  }

  command->code=code;

  return OK;
}

/*command: getter*/
/**
 * @brief Obtains the contents of a Command struct pointer
 * @author Profesores PPROG
 *
 * @param Command*   : pointer to an existing Command struct pointer
 * @return Status : OK, ERROR, if the Command does not exist or is false it returns ERROR, if removed, it will
 * return OK
 */
CommandCode command_get_code(Command* command) {
  if (!command) {/*error control*/
    return NO_CMD;
  }
  return command->code;
}

/*
char *command_get_arg (Command *command) {
return command->arg;
}
*/

/*command: get user input*/
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
Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;/*initializating*/
  int i = UNKNOWN - NO_CMD + 1;
  CommandCode cmd;

  if (!command) {/*error control*/
    return ERROR;
  }

/*if(command->arg){
  free(command->arg);
  command->arg = NULL;
}*/

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
    /*token = strtok(NULL, " \n");
    if(token){
      command->arg = strdup(token);  
    }
    */

    return command_set_code(command, cmd);
  }
  else
    return command_set_code(command, EXIT);
  
}
