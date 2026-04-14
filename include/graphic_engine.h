/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2026
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/** @brief It defines the Graphic_engine struct */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief It creates a new Graphic_engine, allocating memory and initializing its members
 * @author Profesores PPROG
 *
 * @return a new pointer to a Graphic_engine struct, initialized
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief It destroys a Graphic_engine, freeing the allocated memory
 * @author Profesores PPROG
 *
 * @param ge a pointer to the Graphic_engine that must be destroyed
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief It renders the current state of the game on screen
 * @author Jose Miguel Romero Oubina
 *
 * @param ge a pointer to the Graphic_engine struct
 * @param game a pointer to the Game struct to be rendered
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif