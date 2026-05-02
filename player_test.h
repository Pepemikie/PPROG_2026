/**
 * @brief It declares the tests for the Player module
 * @file player_test.h
 * @author Iñaki López Rocha
 * @version 0.0
 * @date 02-04-2026
 * @copyright GNU Public License
 */

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

/**
 * @brief Tests the creation of a player
 * @author Iñaki López Rocha
 */
void test1_player_create();

/**
 * @brief Tests the creation of a player with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_create();

/**
 * @brief Tests setting the player name
 * @author Iñaki López Rocha
 */
void test1_player_set_name();

/**
 * @brief Tests setting the player name with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_set_name();

/**
 * @brief Tests getting the player name
 * @author Iñaki López Rocha
 */
void test1_player_get_name();

/**
 * @brief Tests getting the player name with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_get_name();

/**
 * @brief Tests setting the player location
 * @author Iñaki López Rocha
 */
void test1_player_set_location();

/**
 * @brief Tests setting the player location with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_set_location();

/**
 * @brief Tests getting the player location
 * @author Iñaki López Rocha
 */
void test1_player_get_location();

/**
 * @brief Tests getting the player location with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_get_location();

/**
 * @brief Tests adding an object to the player's inventory
 * @author Iñaki López Rocha
 */
void test1_player_add_object();

/**
 * @brief Tests removing an object from the player's inventory
 * @author Iñaki López Rocha
 */
void test1_player_del_object();

/**
 * @brief Tests checking whether a player has an object
 * @author Iñaki López Rocha
 */
void test1_player_has_object();

/**
 * @brief Tests getting an object by index from the player's inventory
 * @author Iñaki López Rocha
 */
void test1_player_get_object();

/**
 * @brief Tests getting the player's inventory pointer
 * @author Iñaki López Rocha
 */
void test1_player_get_backpack();

/**
 * @brief Tests setting the player health
 * @author Iñaki López Rocha
 */
void test1_player_set_health();

/**
 * @brief Tests setting the player health with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_set_health();

/**
 * @brief Tests getting the player health
 * @author Iñaki López Rocha
 */
void test1_player_get_health();

/**
 * @brief Tests getting the player health with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_get_health();

/**
 * @brief Tests setting the player graphic description
 * @author Iñaki López Rocha
 */
void test1_player_set_gdesc();

/**
 * @brief Tests getting the player graphic description
 * @author Iñaki López Rocha
 */
void test1_player_get_gdesc();

/**
 * @brief Tests getting the player id
 * @author Iñaki López Rocha
 */
void test1_player_get_id();

/**
 * @brief Tests setting the player's backpack capacity
 * @author Iñaki López Rocha
 */
void test1_player_set_max_objs();

/**
 * @brief Tests setting the player's backpack capacity with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_set_max_objs();

/**
 * @brief Tests modifying the player's health
 * @author Iñaki López Rocha
 */
void test1_player_modify_health();

/**
 * @brief Tests modifying the player's health with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_player_modify_health();

#endif
