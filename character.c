/**
 * @brief It implements the character module
 *
 * @file character.c
 * @author Jorge Garcia Garrido 
 * @version 0
 * @date 23-02-2026
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
  Id location; /*The location of the character*/
};

/*Initialises everything by default and allocates memory for a character*/
Character* character_create(Id id) {
  Character *c = NULL;
  if (id == NO_ID) return NULL;/*Error control*/

  c = (Character*) malloc(sizeof(Character));/*Allocates memory for the character*/
  if (!c) return NULL;/*Error control*/

  /*Initialises the character Id, the description, the life points, the friendly mood and the message by default*/
  c->id = id;
  strcpy(c->name, "");
  strcpy(c->gdesc, "      "); /* 6 spacebars */
  c->health = 10;             /* Initial health points */
  c->friendly = TRUE;
  strcpy(c->message, "");

  return c;/*returns the pointer of the struct with all initilizated*/
}

/*Frees the character information*/
Status character_destroy(Character* c) {
  if (!c) return ERROR;/*Checks if the character exists*/
  free(c);/*frees the character*/
  return OK;
}

/*Example of the implementation of Getter/Setter*/

/*Checks if the character exists and retur its health*/
int character_get_health(Character* c) {
  return (c) ? c->health : -1;/*Checks if Character exists, if it is so, returns c->health; otherwise, return -1*/
}

/*Sets the characters health to the health passed by arguments*/
Status character_set_health(Character* c, int health) {
  if (!c || health < 0) return ERROR;/*Error control*/
  c->health = health;/*Gives the life points passed by argyment to the character's health */
  return OK;
}

#ifdef DEBUG
Status character_print(Character* c) {
  if (!c) return ERROR;
  fprintf(stdout, "--> Character [ID: %ld, Name: %s, Health: %d, Friendly: %d]\n", 
          c->id, c->name, c->health, c->friendly);
  return OK;
}
#endif

/* Implementación de los getters que faltan en character.c */
Bool character_get_is_friendly(Character* c) {
  return (c) ? c->friendly : FALSE;
}

const char* character_get_message(Character* c) {
  return (c) ? c->message : NULL;
}

Bool character_is_friendly(Character* character) {
  if (!character) return FALSE;
  return character->friendly;
}

Status character_set_friendly(Character* c, Bool friendly) {
  if (!c) return ERROR;
  c->friendly = friendly;
  return OK;
}

Status character_set_message(Character* c, char* message) {
  if (!c || !message) return ERROR;
  strncpy(c->message, message, WORD_SIZE - 1);
  return OK;
}
Id character_get_location(Character* c) {
  if (!c) return NO_ID;
  return c->location; 
}
