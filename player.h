/**
 * @brief Define la interfaz para el manejo de jugadores
 * @file player.h
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

/* Definición de la estructura como un tipo opaco */
typedef struct _Player Player;

/**
 * @brief Crea un nuevo jugador
 * @param id el identificador del jugador
 * @return un puntero al jugador o NULL en caso de error
 */
Player* player_create(Id id);

/**
 * @brief Destruye un jugador y libera su memoria
 * @param player puntero al jugador
 * @return OK si se destruye correctamente, ERROR en caso contrario
 */
Status player_destroy(Player* player);

/* Getters y Setters */

Id player_get_id(Player* player);

Status player_set_name(Player* player, char* name);
const char* player_get_name(Player* player);

Status player_set_location(Player* player, Id location);
Id player_get_location(Player* player);

Status player_set_object(Player* player, Id object);
Id player_get_object(Player* player);

/**
 * @brief Imprime los datos del jugador (para depuración)
 * @param player puntero al jugador
 * @return OK o ERROR
 */
Status player_print(Player* player);

#endif