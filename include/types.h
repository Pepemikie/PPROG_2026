/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2026
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000 /**< Maximum size of strings for names and descriptions */
#define NO_ID -1 /**< Constant representing an invalid or uninitialized Id */

/** @brief It defines the Id type */
typedef long Id;

/** @brief It defines the Bool type */
typedef enum { FALSE, TRUE } Bool;

/** @brief It defines the Status type */
typedef enum { ERROR, OK } Status;

/** @brief It defines the Direction type */
typedef enum {N, S, E, W, U, D, UNKNOWN_DIR} Direction;

#endif
