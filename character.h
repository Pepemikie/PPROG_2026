#ifndef CHARACTER_H
#define CHARACTER_H

#include "types.h"

/* Definimos el tamaño de la descripción gráfica según el enunciado */
#define GDESC_SIZE 7

typedef struct _Character Character;

Character* character_create(Id id);
Status character_destroy(Character* c);

/* Getters y Setters necesarios para el F4 */
Id character_get_id(Character* c);
const char* character_get_name(Character* c);
Status character_set_name(Character* c, char* name);

int character_get_health(Character* c);
Status character_set_health(Character* c, int health);

Bool character_is_friendly(Character* c);
Status character_set_friendly(Character* c, Bool friendly);

const char* character_get_message(Character* c);
Status character_set_message(Character* c, char* message);

Status character_print(Character* c);

#endif