/**
 * @brief It declares the tests for the Inventory module
 * @file inventory_test.h
 * @author Iñaki López Rocha
 * @version 0.0
 * @date 11-04-2026
 * @copyright GNU Public License
 */

#ifndef INVENTORY_TEST_H
#define INVENTORY_TEST_H

/**
 * @brief Tests the creation of an inventory
 * @author Iñaki López Rocha
 */
void test1_inventory_create();

/**
 * @brief Tests the creation of an inventory with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_create();

/**
 * @brief Tests adding and removing objects from an inventory
 * @author Iñaki López Rocha
 */
void test1_inventory_add_del();

/**
 * @brief Tests checking whether an object is in the inventory
 * @author Iñaki López Rocha
 */
void test1_inventory_has_object();

/**
 * @brief Tests inventory fullness and emptiness
 * @author Iñaki López Rocha
 */
void test1_inventory_full_empty();

/**
 * @brief Tests getting and setting the inventory max object capacity
 * @author Iñaki López Rocha
 */
void test1_inventory_max_objs();

/**
 * @brief Tests getting the number of objects in the inventory
 * @author Iñaki López Rocha
 */
void test1_inventory_number_of_objects();

/**
 * @brief Tests getting the inventory objects set pointer
 * @author Iñaki López Rocha
 */
void test1_inventory_get_objects();

/**
 * @brief Tests setting inventory objects with a new set
 * @author Iñaki López Rocha
 */
void test1_inventory_set_objects();

/**
 * @brief Tests adding an object with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_add_del();

/**
 * @brief Tests getting whether the inventory has an object with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_has_object();

/**
 * @brief Tests inventory empty/full behavior with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_full_empty();

/**
 * @brief Tests getting the inventory objects set pointer with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_get_objects();

/**
 * @brief Tests setting the inventory objects with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_set_objects();

/**
 * @brief Tests getting the inventory max objects with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_get_max_objs();

/**
 * @brief Tests getting the number of objects with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_inventory_number_of_objects();

#endif
