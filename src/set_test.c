/** 
 * @brief It tests set module
 * 
 * @file set_test.c
 * @author Profesores Pprog
 * @version 0.0 
 * @date 17-02-2026
 * @copyright GNU Public License
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "set.h"
#include "set_test.h"
#include "test.h"

/** @brief Maximum number of tests */
#define MAX_TESTS 12

/** @brief Main function for running the Set module unit tests */
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
  }

  if (all || test == 1) test1_set_create();
  if (all || test == 2) test1_set_add();
  if (all || test == 3) test2_set_add();
  if (all || test == 4) test3_set_add();
  if (all || test == 5) test1_set_del();
  if (all || test == 6) test2_set_del();
  if (all || test == 7) test1_set_find();
  if (all || test == 8) test2_set_find();
  if (all || test == 9) test1_set_get_n_ids();
  if (all || test == 10) test1_set_get_id();
  if (all || test == 11) test2_set_get_id();
  if (all || test == 12) test1_set_get_ids();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

/* Tests the creation of a set */
void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

/* Tests adding an element to a set */
void test1_set_add() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add(s, 100) == OK);
  set_destroy(s);
}

/* Tests adding a duplicate element to a set */
void test2_set_add() {
  Set *s = set_create();
  set_add(s, 100);
  /* Según set.c, si ya existe no debería dar error, pero no añade nada nuevo */
  PRINT_TEST_RESULT(set_add(s, 100) == OK && set_get_n_ids(s) == 1);
  set_destroy(s);
}

/* Tests adding to a full set */
void test3_set_add() {
  Set *s = set_create();
  int i;
  for (i = 0; i < MAX_SET; i++) set_add(s, i);
  /* El elemento 11 debe dar error */
  PRINT_TEST_RESULT(set_add(s, 99) == ERROR);
  set_destroy(s);
}

/* Tests deleting an element from a set */
void test1_set_del() {
  Set *s = set_create();
  set_add(s, 50);
  PRINT_TEST_RESULT(set_del(s, 50) == OK && set_get_n_ids(s) == 0);
  set_destroy(s);
}

/* Tests deleting a non-existent element from a set */
void test2_set_del() {
  Set *s = set_create();
  set_add(s, 50);
  PRINT_TEST_RESULT(set_del(s, 20) == ERROR);
  set_destroy(s);
}

/* Tests finding an element in a set */
void test1_set_find() {
  Set *s = set_create();
  set_add(s, 123);
  PRINT_TEST_RESULT(set_find(s, 123) != -1);
  set_destroy(s);
}

/* Tests finding a non-existent element in a set */
void test2_set_find() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_find(s, 999) == -1);
  set_destroy(s);
}

/* Tests getting the number of ids in a set */
void test1_set_get_n_ids() {
  Set *s = set_create();
  set_add(s, 1);
  set_add(s, 2);
  PRINT_TEST_RESULT(set_get_n_ids(s) == 2);
  set_destroy(s);
}

/* Tests getting an id at a specific position in a set */
void test1_set_get_id() {
  Set *s = set_create();
  set_add(s, 10);
  set_add(s, 20);
  PRINT_TEST_RESULT(set_get_id(s, 0) == 10 && set_get_id(s, 1) == 20);
  set_destroy(s);
}

/* Tests getting an id with invalid parameters */
void test2_set_get_id() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_id(s, 0) == NO_ID);
}

/* Tests getting the array of ids in a set */
void test1_set_get_ids() {
  Id *ids = NULL;
  Set *s = set_create();
  set_add(s, 5);
  ids = set_get_ids(s);
  PRINT_TEST_RESULT(ids != NULL && ids[0] == 5);
  set_destroy(s);
}