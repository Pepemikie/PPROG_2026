/**
 * @brief It declares the tests for the Set module
 * @file set_test.h
 * @author Profesores Pprog
 * @version 0.0
 * @date 17-02-2026
 * @copyright GNU Public License
 */

#ifndef SET_TEST_H
#define SET_TEST_H

/**
 * @brief Tests the creation of a set
 * @author Profesores Pprog
 */
void test1_set_create();

/**
 * @brief Tests adding an element to a set
 * @author Profesores Pprog
 */
void test1_set_add();

/**
 * @brief Tests adding a duplicate element
 * @author Profesores Pprog
 */
void test2_set_add();

/**
 * @brief Tests adding to a full set
 * @author Profesores Pprog
 */
void test3_set_add();

/**
 * @brief Tests deleting an element from a set
 * @author Profesores Pprog
 */
void test1_set_del();

/**
 * @brief Tests deleting a non-existent element
 * @author Profesores Pprog
 */
void test2_set_del();

/**
 * @brief Tests finding an element in a set
 * @author Profesores Pprog
 */
void test1_set_find();

/**
 * @brief Tests finding a non-existent element in a set
 * @author Profesores Pprog
 */
void test2_set_find();

/**
 * @brief Tests getting the number of ids in a set
 * @author Profesores Pprog
 */
void test1_set_get_n_ids();

/**
 * @brief Tests getting an id at a specific position in a set
 * @author Profesores Pprog
 */
void test1_set_get_id();

/**
 * @brief Tests getting an id with invalid parameters
 * @author Profesores Pprog
 */
void test2_set_get_id();

/**
 * @brief Tests getting the number of ids with invalid parameters
 * @author Profesores Pprog
 */
void test2_set_get_n_ids();

/**
 * @brief Tests getting the array of ids in a set with invalid or empty parameters
 * @author Profesores Pprog
 */
void test2_set_get_ids();

/**
 * @brief Tests adding an element to a set with invalid parameters
 * @author Profesores Pprog
 */
void test4_set_add();

/**
 * @brief Tests deleting an element from a set with invalid parameters
 * @author Profesores Pprog
 */
void test3_set_del();

/**
 * @brief Tests finding an element in a set with invalid parameters
 * @author Profesores Pprog
 */
void test3_set_find();

/**
 * @brief Tests getting the array of ids in a set
 * @author Profesores Pprog
 */
void test1_set_get_ids();

#endif