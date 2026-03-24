/**
 *   It implements the character module
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

/*Defined Character struct*/
struct _Character {
  Id id; /*The ID of the character*/
  char name[WORD_SIZE]; /*The name given to the character*/
  char gdesc[GDESC_SIZE];/*String of 6 characters + \0*/
  int health;             /* Life points*/
  Bool friendly;          /*Defines if the character is your friend or not*/
  char message[WORD_SIZE];/*Storage the message*/
};

/*   It creates a new character, allocating memory and initializing its members */
Character* character_create(Id id) {
  Character *new_character = NULL;
  if (id == NO_ID) return NULL;/*Error control*/

  new_character = (Character*) malloc(sizeof(Character));/*Allocates memory for the character*/
  if (! new_character) return NULL;/*Error control*/

  /*Initialises the character Id, the description, the life points, the friendly mood and the message by default*/
  new_character->id = id;
  strcpy( new_character->name, "");
  strcpy( new_character->gdesc, "      "); /* 6 spacebars */
  new_character->health = 10;             /* Initial health points */
  new_character->friendly = TRUE;
  strcpy( new_character->message, "");

  return new_character;/*returns the pointer of the struct with all initilizated*/
}

/*   It destroys a character, freeing the allocated memory */
Status character_destroy(Character* c) {
  if (!c) return ERROR;/*Checks if the character exists*/
  free(c);/*frees the character*/
  return OK;
}

/*   It gets the id of a character */
Id character_get_id(Character* c){
  if(!c)
    return -1;

  return c->id;
}

/*   It gets the name of a character */
const char* character_get_name(Character* c){
  if(!c)
    return NULL;

  return c->name;
}

/*   It sets the name of a character */
Status character_set_name(Character* c, char* name){
    if (!c) return ERROR;
    strncpy(c->name, name, WORD_SIZE); /* Copies name safely */
    c->name[WORD_SIZE - 1] = '\0'; /*to guarantee strncpy*/
  return OK;
}

/*   It gets the description of a character */
char *character_get_gdesc(Character *c) {
    if (!c) {
        return NULL;
    }
    return c->gdesc;
}

/*   It sets the description of a character */
Status character_set_gdesc(Character *c, char *gdesc) {
    if (!c || !gdesc) { /* Error control */
        return ERROR;
    }
    strcpy(c->gdesc, gdesc); /* Copies the description into the struct */

    return OK;
}

/*   It gets the health of a character */
int character_get_health(Character* c) {
  if(!c)
    return -1;

  return c->health;/*Checks if Character exists, if it is so, returns c->health; otherwise, return -1*/
}

/*   It sets the health of the character */
Status character_set_health(Character* c, int health) {
  if (!c || health < 0) return ERROR;/*Error control*/
  c->health = health;/*Gives the life points passed by argyment to the character's health */
  return OK;
}

/*   It gets the mood of a character */
Bool character_is_friendly(Character* c) {
  if(!c)
    return FALSE;

  return c->friendly;
}

/*   It sets the mood of the character */
Status character_set_friendly(Character* c, Bool friendly) {
  if (!c) return ERROR;
  c->friendly = friendly; /* Assigns the friendly value to the character */
  return OK;
}

/*   It gets the message of a character */
const char* character_get_message(Character* c) {
    if(!c)
    return NULL;

  return c->message;
}

/*   It sets the message of the character */
Status character_set_message(Character* c, char* message) {
  if (!c || !message) return ERROR;
  strncpy(c->message, message, WORD_SIZE - 1); /* Copies message safely */
  c->message[WORD_SIZE - 1] = '\0'; /*to guarantee strncpy*/
  return OK;
}

#ifdef DEBUG
/*   It prints the data of a character */
Status character_print(Character* c) {
  if (!c) return ERROR;
  fprintf(stdout, "--> Character [ID: %ld, Name: %s, Desc: %s, Health: %d,  Friendly: %d, Message: %s]\n", 
          c->id, c->name, c->gdesc,  c->health, c->friendly, c->message);
  return OK;
}
#endif