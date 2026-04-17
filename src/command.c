/**
 * @brief It implements the command interpreter
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

/**
 * @brief Maximum length of a command input string
 */
#define CMD_LENGHT 30

/**
 * @brief Lookup table mapping each CommandCode to its short and long string representations
 *
 * Indexed by CommandCode (offset by 1 due to UNKNOWN = 0). Each entry contains
 * the short form at index CMDS and the long form at index CMDL.
 */
char *cmd_to_str[N_CMD][N_CMDT] = {
  {"",  "Unknown"}, /**< UNKNOWN */
  {"e", "Exit"},    /**< EXIT */
  {"t", "Take"},    /**< TAKE */
  {"d", "Drop"},    /**< DROP */
  {"a", "Attack"},  /**< ATTACK */
  {"c", "Chat"},    /**< CHAT */
  {"m", "Move"},    /**< MOVE */
  {"i", "Inspect"}, /**< INSPECT */
  {"r", "Recruit"}  /**< RECRUIT */
};

/**
 * @brief Stores all the information related to a command
 */
struct _Command {
  char *arg;       /**< Optional argument provided alongside the command */
  CommandCode code; /**< Code identifying the type of command */
};

Command* command_create() {
  Command* newCommand = NULL;

  newCommand = (Command*)malloc(sizeof(Command));
  if (newCommand == NULL) {
    return NULL;
  }

  newCommand->code = NO_CMD;
  newCommand->arg  = NULL;

  return newCommand;
}

Status command_destroy(Command* command) {
  if (!command) {
    return ERROR;
  }

  if (command->arg) {
    free(command->arg);
    command->arg = NULL;
  }

  free(command);
  return OK;
}

Status command_set_code(Command* command, CommandCode code) {
  if (!command) {
    return ERROR;
  }

  command->code = code;
  return OK;
}

CommandCode command_get_code(Command* command) {
  if (!command) {
    return NO_CMD;
  }

  return command->code;
}

char* command_get_arg(Command* command) {
  if (!command) return NULL;
  return command->arg;
}

Status command_get_user_input(Command* command) {
  char input[CMD_LENGHT] = "", *token = NULL;
  int i = 0;
  CommandCode cmd;

  if (!command) {
    return ERROR;
  }

  if (command->arg) {
    free(command->arg);
    command->arg = NULL;
  }

  if (fgets(input, CMD_LENGHT, stdin)) {
    token = strtok(input, " \n");
    if (!token) {
      return command_set_code(command, UNKNOWN);
    }

    cmd = UNKNOWN;

    while (cmd == UNKNOWN && i < N_CMD) {
    if (cmd_to_str[i][CMDS] && cmd_to_str[i][CMDL] && (!strcasecmp(token, cmd_to_str[i][CMDS]) || !strcasecmp(token, cmd_to_str[i][CMDL]))) {
        cmd = i;
    } else {
        i++;
    }
}

    token = strtok(NULL, " \n");
    if (token) {
      command->arg = (char*)malloc(strlen(token) + 1);
      if (command->arg)
        strcpy(command->arg, token);
    }

    return command_set_code(command, cmd);
  } else {
    return command_set_code(command, EXIT);
  }
}