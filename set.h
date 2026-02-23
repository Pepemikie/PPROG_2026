/**
 * @brief Define la interfaz para el manejo de conjuntos (sets)
 * @file set.h
 */

#ifndef SET_H
#define SET_H

#include "types.h"

/* Definimos el número máximo de elementos en el conjunto */
#define MAX_SET 10

/* Definición del tipo para el conjunto como una estructura opaca */
typedef struct _Set Set;

/**
 * @brief Crea un nuevo conjunto vacío
 * @return un puntero al nuevo conjunto o NULL en caso de error
 */
Set* set_create();

/**
 * @brief Destruye un conjunto y libera su memoria
 * @param set puntero al conjunto a destruir
 * @return OK si se destruye correctamente, ERROR en caso contrario
 */
Status set_destroy(Set* set);

/**
 * @brief Añade un elemento al conjunto si no existe ya
 * @param set puntero al conjunto
 * @param id el identificador a añadir
 * @return OK si se añade o ya existía, ERROR si está lleno o hay error
 */
Status set_add(Set* set, Id id);

/**
 * @brief Elimina un elemento del conjunto
 * @param set puntero al conjunto
 * @param id el identificador a eliminar
 * @return OK si se elimina, ERROR si no se encuentra o hay error
 */
Status set_del(Set* set, Id id);

/**
 * @brief Busca si un ID está en el conjunto
 * @param set puntero al conjunto
 * @param id el identificador a buscar
 * @return El índice del elemento (0 a n-1) o -1 si no se encuentra
 */
int set_find(Set* set, Id id);

/**
 * @brief Devuelve cuántos elementos hay en el conjunto
 * @param set puntero al conjunto
 * @return El número de elementos o -1 si hay error
 */
int set_get_n_ids(Set* set);

/**
 * @brief Imprime el contenido del conjunto (para depuración)
 * @param set puntero al conjunto
 * @return OK o ERROR
 */
Status set_print(Set* set);

#endif