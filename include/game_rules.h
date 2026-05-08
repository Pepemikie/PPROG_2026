#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "game.h"

/**
 * @brief Ejecuta las reglas no deterministas del juego
 * @param game Puntero al juego actual
 * @author Rodrigo Cruz Asensio
 * 
 * Esta función debe ser llamada una vez por turno para aplicar
 * los eventos aleatorios y reglas automáticas del museo.
 */
void game_rules_update(Game *game);

#endif