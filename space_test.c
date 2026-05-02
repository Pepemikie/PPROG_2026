/** 
 * @brief It tests space module
 * 
 * @file space_test.c
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "space.h"
#include "space_test.h"
#include "test.h"

/** @brief Maximum number of tests */
#define MAX_TESTS 28

/** 
 * @brief Main function for SPACE unit tests. 
 * 
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed 
 *   2.- A number means a particular test (the one identified by that number) 
 *       is executed
 *  
 */
int main(int argc, char** argv) {

  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all test for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_space_create();
  if (all || test == 2)  test2_space_create();
  if (all || test == 3)  test1_space_set_name();
  if (all || test == 4)  test2_space_set_name();
  if (all || test == 5)  test3_space_set_name();
  if (all || test == 6)  test1_space_set_object();
  if (all || test == 7)  test2_space_set_object();
  if (all || test == 8)  test1_space_get_id();
  if (all || test == 9)  test2_space_get_id();
  if (all || test == 10) test1_space_get_name();
  if (all || test == 11) test2_space_get_name();
  if (all || test == 12) test1_space_get_object();
  if (all || test == 13) test2_space_get_object();
  if (all || test == 14) test3_space_get_object();
  if (all || test == 15) test1_space_set_gdesc();
  if (all || test == 16) test2_space_set_gdesc();
  if (all || test == 17) test1_space_get_gdesc();
  if (all || test == 18) test2_space_get_gdesc();
  if (all || test == 19) test1_space_set_discovered();
  if (all || test == 20) test1_space_get_discovered();
  if (all || test == 21) test1_space_add_character();
  if (all || test == 22) test2_space_add_character();
  if (all || test == 23) test1_space_has_character();
  if (all || test == 24) test2_space_has_character();
  if (all || test == 25) test1_space_get_number_of_characters();
  if (all || test == 26) test1_space_get_character();
  if (all || test == 27) test1_space_del_character();
  if (all || test == 28) test2_space_del_character();

  PRINT_PASSED_PERCENTAGE;

  return 0;
}

/* Tests the creation of a space */
void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

/* Tests the creation of a space with invalid parameters */
void test2_space_create() {
  Space *s;
  s = space_create(NO_ID);
  PRINT_TEST_RESULT(s == NULL);
}

/* Tests setting the name of a space */
void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

/* Tests setting the name of a space with invalid parameters */
void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

/* Tests setting the name of a space with NULL name */
void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/* Tests adding an object to a space */
void test1_space_set_object() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_object(s, 1) == OK);
  space_destroy(s);
}

/* Tests adding an object to a space with invalid parameters */
void test2_space_set_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, 1) == ERROR);
}
void test1_space_set_gdesc() {
  Space *s = space_create(1);
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1] = {
    "line1",
    "line2",
    "line3",
    "line4",
    "line5"
  };
  PRINT_TEST_RESULT(space_set_gdesc(s, gdesc) == OK);
  space_destroy(s);
}

void test2_space_set_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_get_gdesc() {
  Space *s = space_create(1);
  char gdesc[SPACE_GDESC_LINES][SPACE_GDESC_LENGTH + 1] = {
    "line1",
    "line2",
    "line3",
    "line4",
    "line5"
  };
  space_set_gdesc(s, gdesc);
  PRINT_TEST_RESULT(strcmp(space_get_gdesc(s, 1), "line2") == 0);
  space_destroy(s);
}

void test2_space_get_gdesc() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_get_gdesc(s, -1) == NULL && space_get_gdesc(NULL, 0) == NULL);
  space_destroy(s);
}

void test1_space_set_discovered() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK && space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test1_space_get_discovered() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
  space_destroy(s);
}

void test1_space_add_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_character(s, 10) == OK && space_has_character(s, 10) == TRUE);
  space_destroy(s);
}

void test2_space_add_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_character(s, 10) == ERROR);
}

void test1_space_has_character() {
  Space *s = space_create(1);
  space_add_character(s, 10);
  PRINT_TEST_RESULT(space_has_character(s, 10) == TRUE && space_has_character(s, NO_ID) == FALSE);
  space_destroy(s);
}

void test2_space_has_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_character(s, 10) == FALSE);
}

void test1_space_get_number_of_characters() {
  Space *s = space_create(1);
  space_add_character(s, 10);
  space_add_character(s, 11);
  PRINT_TEST_RESULT(space_get_number_of_characters(s) == 2);
  space_destroy(s);
}

void test1_space_get_character() {
  Space *s = space_create(1);
  Id *characters = NULL;

  space_add_character(s, 12);
  characters = space_get_character(s);
  PRINT_TEST_RESULT(characters != NULL && characters[0] == 12);
  space_destroy(s);
}

void test1_space_del_character() {
  Space *s = space_create(1);
  space_add_character(s, 12);
  PRINT_TEST_RESULT(space_del_character(s, 12) == OK && space_has_character(s, 12) == FALSE);
  space_destroy(s);
}

void test2_space_del_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_del_character(s, NO_ID) == ERROR);
  space_destroy(s);
}
/* Tests getting the id of a space */
void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

/* Tests getting the id of a space with invalid parameters */
void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/* Tests getting the name of a space */
void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

/* Tests getting the name of a space with invalid parameters */
void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/* Tests getting the objects of a space */
void test1_space_get_object() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_has_object(s, 1) == FALSE);
  space_destroy(s);
}

/* Tests getting the objects of a space with invalid parameters */
void test2_space_get_object() {
  Space *s;
  s = space_create(1);
  space_add_object(s, 1);
  PRINT_TEST_RESULT(space_has_object(s, 1) == TRUE);
  space_destroy(s);
}

/* Tests getting the objects of a space when there are no objects */
void test3_space_get_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_object(s, 1) == FALSE);
}