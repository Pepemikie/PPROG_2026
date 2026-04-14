/**
 * @brief It implements the unit tests for the Character module
 * @file character_test.c
 * @author Iñaki López Rocha
 * @version 1.0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"
#include "character_test.h"
#include "test.h"

/**
 * @brief Maximum number of tests available for the Character module
 */
#define MAX_TESTS 24

/**
 * @brief Main function for the Character test module
 *
 * @param argc number of command-line arguments
 * @param argv array of command-line argument strings. If a test number is provided,
 *        only that test is executed; otherwise all tests are run
 * @return 1 after executing the selected tests
 */
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_character_create();
  if (all || test == 2)  test2_character_create();
  if (all || test == 3)  test1_character_set_name();
  if (all || test == 4)  test2_character_set_name();
  if (all || test == 5)  test1_character_get_name();
  if (all || test == 6)  test2_character_get_name();
  if (all || test == 7)  test1_character_set_health();
  if (all || test == 8)  test2_character_set_health();
  if (all || test == 9)  test1_character_get_health();
  if (all || test == 10) test2_character_get_health();
  if (all || test == 11) test1_character_set_friendly();
  if (all || test == 12) test2_character_set_friendly();
  if (all || test == 13) test1_character_is_friendly();
  if (all || test == 14) test2_character_is_friendly();
  if (all || test == 15) test1_character_set_message();
  if (all || test == 16) test2_character_set_message();
  if (all || test == 17) test1_character_get_message();
  if (all || test == 18) test2_character_get_message();
  if (all || test == 19) test1_character_get_id();
  if (all || test == 20) test2_character_get_id();
  if (all || test == 21) test1_character_set_gdesc();
  if (all || test == 22) test2_character_set_gdesc();
  if (all || test == 23) test1_character_get_gdesc();
  if (all || test == 24) test2_character_get_gdesc();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

void test1_character_create() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}

void test2_character_create() {
  Character *c = character_create(NO_ID);
  PRINT_TEST_RESULT(c == NULL);
}

void test1_character_set_name() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "Jorge") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "Jorge") == ERROR);
}

void test1_character_get_name() {
  Character *c = character_create(1);
  character_set_name(c, "Jorge");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "Jorge") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_set_health() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_health(c, 10) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 10) == ERROR);
}

void test1_character_get_health() {
  Character *c = character_create(1);
  character_set_health(c, 25);
  PRINT_TEST_RESULT(character_get_health(c) == 25);
  character_destroy(c);
}

void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == -1);
}

void test1_character_set_friendly() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(c, FALSE) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, FALSE) == ERROR);
}

void test1_character_is_friendly() {
  Character *c = character_create(1);
  character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(character_is_friendly(c) == TRUE);
  character_destroy(c);
}

void test2_character_is_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_is_friendly(c) == FALSE);
}

void test1_character_set_message() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, "Hola") == OK);
  character_destroy(c);
}

void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "Hola") == ERROR);
}

void test1_character_get_message() {
  Character *c = character_create(1);
  character_set_message(c, "Test Message");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "Test Message") == 0);
  character_destroy(c);
}

void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_get_id() {
  Character *c = character_create(3);
  PRINT_TEST_RESULT(character_get_id(c) == 3);
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_set_gdesc() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "HELLO ") == OK);
  character_destroy(c);
}

void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "HELLO ") == ERROR);
}

void test1_character_get_gdesc() {
  Character *c = character_create(1);
  character_set_gdesc(c, "HELLO ");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "HELLO ") == 0);
  character_destroy(c);
}

void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}