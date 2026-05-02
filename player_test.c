/** 
 * @brief Implementation of the Player module unit tests
 * @file player_test.c
 * @author Iñaki López Rocha
 * @date 02-04-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"
#include "player_test.h"
#include "test.h"

/** @brief Maximum number of tests */
#define MAX_TESTS 26

/** @brief Main function for running the Player module unit tests */
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_player_create();
  if (all || test == 2) test2_player_create();
  if (all || test == 3) test1_player_set_name();
  if (all || test == 4) test2_player_set_name();
  if (all || test == 5) test1_player_get_name();
  if (all || test == 6) test2_player_get_name();
  if (all || test == 7) test1_player_set_location();
  if (all || test == 8) test2_player_set_location();
  if (all || test == 9) test1_player_get_location();
  if (all || test == 10) test2_player_get_location();
  if (all || test == 11) test1_player_add_object();
  if (all || test == 12) test1_player_del_object();
  if (all || test == 13) test1_player_has_object();
  if (all || test == 14) test1_player_get_object();
  if (all || test == 15) test1_player_get_backpack();
  if (all || test == 16) test1_player_set_health();
  if (all || test == 17) test2_player_set_health();
  if (all || test == 18) test1_player_get_health();
  if (all || test == 19) test2_player_get_health();
  if (all || test == 20) test1_player_set_gdesc();
  if (all || test == 21) test1_player_get_gdesc();
  if (all || test == 22) test1_player_get_id();
  if (all || test == 23) test1_player_set_max_objs();
  if (all || test == 24) test2_player_set_max_objs();
  if (all || test == 25) test1_player_modify_health();
  if (all || test == 26) test2_player_modify_health();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

/* Tests player creation */
void test1_player_create() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(p != NULL);
  player_destroy(p);
}

/* Tests player creation with invalid id */
void test2_player_create() {
  Player *p = player_create(NO_ID);
  PRINT_TEST_RESULT(p == NULL);
}

/* Tests setting the player name */
void test1_player_set_name() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_name(p, "Hero") == OK);
  player_destroy(p);
}

/* Tests setting the player name with invalid parameters */
void test2_player_set_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_name(p, "Hero") == ERROR);
}

/* Tests getting the player name */
void test1_player_get_name() {
  Player *p = player_create(1);
  player_set_name(p, "Hero");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "Hero") == 0);
  player_destroy(p);
}

/* Tests getting the player name with invalid parameters */
void test2_player_get_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_name(p) == NULL);
}

/* Tests setting the player location */
void test1_player_set_location() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_location(p, 10) == OK);
  player_destroy(p);
}

/* Tests setting the player location with invalid parameters */
void test2_player_set_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_location(p, 10) == ERROR);
}

/* Tests getting the player location */
void test1_player_get_location() {
  Player *p = player_create(1);
  player_set_location(p, 10);
  PRINT_TEST_RESULT(player_get_location(p) == 10);
  player_destroy(p);
}

/* Tests getting the player location with invalid parameters */
void test2_player_get_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}

/* Tests adding an object to the player's inventory */
void test1_player_add_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_add_object(p, 5) == OK && player_has_object(p, 5) == TRUE);
  player_destroy(p);
}

/* Tests removing an object from the player's inventory */
void test1_player_del_object() {
  Player *p = player_create(1);
  player_add_object(p, 5);
  PRINT_TEST_RESULT(player_del_object(p, 5) == OK && player_has_object(p, 5) == FALSE);
  player_destroy(p);
}

/* Tests checking whether a player has an object */
void test1_player_has_object() {
  Player *p = player_create(1);
  player_add_object(p, 7);
  PRINT_TEST_RESULT(player_has_object(p, 7) == TRUE);
  player_destroy(p);
}

/* Tests getting an object by index from the player's inventory */
void test1_player_get_object() {
  Player *p = player_create(1);
  player_add_object(p, 8);
  PRINT_TEST_RESULT(player_get_object(p, 0) == 8 && player_get_object(p, 1) == NO_ID);
  player_destroy(p);
}

/* Tests getting the player's inventory pointer */
void test1_player_get_backpack() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_get_backpack(p) != NULL && inventory_is_empty(player_get_backpack(p)) == TRUE);
  player_destroy(p);
}

void test1_player_get_id() {
  Player *p = player_create(7);
  PRINT_TEST_RESULT(player_get_id(p) == 7);
  player_destroy(p);
}

void test1_player_set_max_objs() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_max_objs(p, 5) == OK && inventory_get_max_objs(player_get_backpack(p)) == 5);
  player_destroy(p);
}

void test2_player_set_max_objs() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_max_objs(p, 5) == ERROR);
}

void test1_player_modify_health() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_modify_health(p, 5) == OK && player_get_health(p) == 15 && player_modify_health(p, -10) == OK && player_get_health(p) == 5);
  player_destroy(p);
}

void test2_player_modify_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_modify_health(p, 5) == ERROR);
}

/* Tests setting the player health */
void test1_player_set_health() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_health(p, 15) == OK);
  player_destroy(p);
}

/* Tests setting the player health with invalid parameters */
void test2_player_set_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_health(p, 15) == ERROR);
}

/* Tests getting the player health */
void test1_player_get_health() {
  Player *p = player_create(1);
  player_set_health(p, 20);
  PRINT_TEST_RESULT(player_get_health(p) == 20);
  player_destroy(p);
}

/* Tests getting the player health with invalid parameters */
void test2_player_get_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_health(p) == -1);
}

/* Tests setting the player graphic description */
void test1_player_set_gdesc() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_gdesc(p, "PLAYER") == OK);
  player_destroy(p);
}

/* Tests getting the player graphic description */
void test1_player_get_gdesc() {
  Player *p = player_create(1);
  player_set_gdesc(p, "PLAYER");
  PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "PLAYER") == 0);
  player_destroy(p);
}
