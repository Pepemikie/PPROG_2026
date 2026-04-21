/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Jorge Garcia Garrido
 * @version 1
 * @date 10-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

/**
 * @brief Stores all the information related to a game character
 */
struct _Character {
  Id id;                   /**< The unique identifier of the character */
  char name[WORD_SIZE];    /**< The name of the character */
  char gdesc[GDESC_SIZE];  /**< Graphic description: a string of 6 characters plus null terminator */
  int health;              /**< Life points of the character */
  Bool friendly;           /**< Whether the character is friendly towards the player */
  char message[WORD_SIZE]; /**< Message displayed when the player interacts with the character */
  Id following;            /**< The ID of the player that this character is following, or NO_ID if not following anyone */
};

Character* character_create(Id id) {
  Character *new_character = NULL;
  if (id == NO_ID) return NULL;

  new_character = (Character*) malloc(sizeof(Character));
  if (!new_character) return NULL;

  new_character->id = id;
  strcpy(new_character->name, "");
  strcpy(new_character->gdesc, "      ");
  new_character->health = 10;
  new_character->friendly = TRUE;
  strcpy(new_character->message, "");
  new_character->following = NO_ID;

  return new_character;
}

Status character_destroy(Character* c) {
  if (!c) return ERROR;
  free(c);
  return OK;
}

Id character_get_id(Character* c) {
  if (!c) return NO_ID;
  return c->id;
}

const char* character_get_name(Character* c) {
  if (!c) return NULL;
  return c->name;
}

Status character_set_name(Character* c, char* name) {
  if (!c || !name) return ERROR;
  strncpy(c->name, name, WORD_SIZE);
  c->name[WORD_SIZE - 1] = '\0';
  return OK;
}

char* character_get_gdesc(Character* c) {
  if (!c) return NULL;
  return c->gdesc;
}

Status character_set_gdesc(Character* c, char* gdesc) {
  if (!c || !gdesc) return ERROR;
  strcpy(c->gdesc, gdesc);
  return OK;
}

int character_get_health(Character* c) {
  if (!c) return NO_ID;
  return c->health;
}

Status character_set_health(Character* c, int health) {
  if (!c || health < 0) return ERROR;
  c->health = health;
  return OK;
}

Bool character_is_friendly(Character* c) {
  if (!c) return FALSE;
  return c->friendly;
}

Status character_set_friendly(Character* c, Bool friendly) {
  if (!c) return ERROR;
  c->friendly = friendly;
  return OK;
}

const char* character_get_message(Character* c) {
  if (!c) return NULL;
  return c->message;
}

Status character_set_message(Character* c, char* message) {
  if (!c || !message) return ERROR;
  strncpy(c->message, message, WORD_SIZE - 1);
  c->message[WORD_SIZE - 1] = '\0';
  return OK;
}

Status character_set_following(Character* c, Id player_id) {
  if (!c) return ERROR;
  c->following = player_id;
  return OK;
}

Id character_get_following(Character* c) {
  if (!c) return NO_ID;
  return c->following;
}

#ifdef DEBUG
Status character_print(Character* c) {
  if (!c) return ERROR;
  fprintf(stdout, "--> Character [ID: %ld, Name: %s, Desc: %s, Health: %d, Friendly: %d, Message: %s, Following: %ld]\n",
          c->id, c->name, c->gdesc, c->health, c->friendly, c->message, c->following);
  return OK;
}
#endif