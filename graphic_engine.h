/**
 * @brief It defines the textual graphic engine interface
 *
 * @file graphic_engine.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#include "game.h"

/** 
 * Graphic engine's Struct 
 * Inside counts with:
 * All Area* pointers with names:
 *
 * map
 * descript
 * banner
 * help
 * feedback
 * 
 */
typedef struct _Graphic_engine Graphic_engine;

/**
 * @brief Reserves space for the graphic engine struct and initializes the graphic_engine struct to zero and default values.
 * @author Profesores PPROG
 * @check Comprobador inicial ¿redundante?
 * @param Game*
 * @return Graphic_engine* or NULL
 */
Graphic_engine *graphic_engine_create();

/**
 * @brief Frees the memory occupied by the Graphic_engine struct
 * @author Profesores PPROG
 *
 * @param Graphic_engine *ge
 * @return
 */
void graphic_engine_destroy(Graphic_engine *ge);

/**
 * @brief Updates or paints the game status / interface / map
 * @author Profesores PPROG
 *
 * @param Graphic_engine*
 * @param Game*
 * @return
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game);

#endif
