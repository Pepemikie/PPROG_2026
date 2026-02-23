/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG
 * @version 0
 * @date 27-01-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

/*
 * Standard string size in the programme
 */
#define WORD_SIZE 1000
/*
 * Alias or macro to return ‘NO_ID’ 
 * which is internally processed as -1
 */
#define NO_ID -1

/*
 * Encapsulator for long, which ‘renames’ it to Id
 */
typedef long Id;

/*
 * Enumerated used instead of 0 and 1
 * to determine whether something is positive or negative
 */
typedef enum { FALSE, TRUE } Bool;

/*
 * Enumerated value that determines whether the function 
 * or call ended in error, or successfully
 */
typedef enum { ERROR, OK } Status;

/*
 * Enumerated value that determines the direction
 */
typedef enum { N, S, E, W } Direction;

#endif
