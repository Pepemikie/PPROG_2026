/** 
 * @brief It declares the tests for the space module
 * 
 * @file space_test.h
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2026
 * @copyright GNU Public License
 */
#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @brief Tests the creation of a space
 * @author Profesores Pprog
 */
void test1_space_create();

/**
 * @brief Tests the creation of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_create();

/**
 * @brief Tests setting the name of a space
 * @author Profesores Pprog
 */
void test1_space_set_name();

/**
 * @brief Tests setting the name of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_set_name();

/**
 * @brief Tests setting the name of a space with NULL name
 * @author Profesores Pprog
 */
void test3_space_set_name();

/**
 * @brief Tests adding an object to a space
 * @author Profesores Pprog
 */
void test1_space_set_object();

/**
 * @brief Tests adding an object to a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_set_object();

/**
 * @brief Tests getting the id of a space
 * @author Profesores Pprog
 */
void test1_space_get_id();

/**
 * @brief Tests getting the id of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_get_id();

/**
 * @brief Tests getting the name of a space
 * @author Profesores Pprog
 */
void test1_space_get_name();

/**
 * @brief Tests getting the name of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_get_name();

/**
 * @brief Tests getting the objects of a space
 * @author Profesores Pprog
 */
void test1_space_get_object();

/**
 * @brief Tests getting the objects of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_get_object();

/**
 * @brief Tests getting the objects of a space when there are no objects
 * @author Profesores Pprog
 */
void test3_space_get_object();

/**
 * @brief Tests setting the graphic description of a space
 * @author Profesores Pprog
 */
void test1_space_set_gdesc();

/**
 * @brief Tests setting the graphic description of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_set_gdesc();

/**
 * @brief Tests getting the graphic description of a space
 * @author Profesores Pprog
 */
void test1_space_get_gdesc();

/**
 * @brief Tests getting the graphic description of a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_get_gdesc();

/**
 * @brief Tests setting the discovered state of a space
 * @author Profesores Pprog
 */
void test1_space_set_discovered();

/**
 * @brief Tests getting the discovered state of a space
 * @author Profesores Pprog
 */
void test1_space_get_discovered();

/**
 * @brief Tests adding a character to a space
 * @author Profesores Pprog
 */
void test1_space_add_character();

/**
 * @brief Tests adding a character to a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_add_character();

/**
 * @brief Tests checking whether a character is in a space
 * @author Profesores Pprog
 */
void test1_space_has_character();

/**
 * @brief Tests checking whether a character is in a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_has_character();

/**
 * @brief Tests getting the number of characters in a space
 * @author Profesores Pprog
 */
void test1_space_get_number_of_characters();

/**
 * @brief Tests getting the characters array from a space
 * @author Profesores Pprog
 */
void test1_space_get_character();

/**
 * @brief Tests removing a character from a space
 * @author Profesores Pprog
 */
void test1_space_del_character();

/**
 * @brief Tests removing a character from a space with invalid parameters
 * @author Profesores Pprog
 */
void test2_space_del_character();

#endif