#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"

struct _Character {
  Id id;
  char name[WORD_SIZE];
  char gdesc[GDESC_SIZE]; /* Cadena de 6 caracteres + \0 */
  int health;             /* Puntos de vida */
  Bool friendly;          /* ¿Es amigo? */
  char message[WORD_SIZE];/* Mensaje que almacena */
};

Character* character_create(Id id) {
  Character *c = NULL;
  if (id == NO_ID) return NULL;

  c = (Character*) malloc(sizeof(Character));
  if (!c) return NULL;

  /* Inicialización por defecto */
  c->id = id;
  strcpy(c->name, "");
  strcpy(c->gdesc, "      "); /* 6 espacios */
  c->health = 10;             /* Vida inicial por defecto */
  c->friendly = TRUE;
  strcpy(c->message, "");

  return c;
}

Status character_destroy(Character* c) {
  if (!c) return ERROR;
  free(c);
  return OK;
}

/* Ejemplo de implementación de Getter/Setter */
int character_get_health(Character* c) {
  return (c) ? c->health : -1;
}

Status character_set_health(Character* c, int health) {
  if (!c || health < 0) return ERROR;
  c->health = health;
  return OK;
}

/* Función de impresión para depuración */
Status character_print(Character* c) {
  if (!c) return ERROR;
  fprintf(stdout, "--> Character [ID: %ld, Name: %s, Health: %d, Friendly: %d]\n", 
          c->id, c->name, c->health, c->friendly);
  return OK;
}

/* El resto de getters y setters siguen la misma lógica simple */