/**
 * @brief It declares the tests for the Link module
 * @file link_test.h
 * @author Iñaki López Rocha
 * @version 0.0
 * @date 01-04-2026
 * @copyright GNU Public License
 */

#ifndef LINK_TEST_H
#define LINK_TEST_H

/**
 * @brief Tests the creation of a link
 * @author Iñaki López Rocha
 */
void test1_link_create();

/**
 * @brief Tests the creation of a link with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_link_create();

/**
 * @brief Tests getting the id of a link
 * @author Iñaki López Rocha
 */
void test1_link_get_id();

/**
 * @brief Tests setting and getting the link name
 * @author Iñaki López Rocha
 */
void test1_link_name();

/**
 * @brief Tests setting and getting the origin and destination of a link
 * @author Iñaki López Rocha
 */
void test1_link_space_ids();

/**
 * @brief Tests setting and getting the link direction
 * @author Iñaki López Rocha
 */
void test1_link_direction();

/**
 * @brief Tests setting and getting whether a link is open
 * @author Iñaki López Rocha
 */
void test1_link_open();

/**
 * @brief Tests getting the name of a link with invalid parameters
 * @author Iñaki López Rocha
 */
void test2_link_get_name();

#endif
