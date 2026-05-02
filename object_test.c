/** 
 * @brief Implementation of the Object module unit tests
 * @file object_test.c
 * @author Iñaki López Rocha
 * @date 01-04-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "object_test.h"
#include "test.h"

/** @brief Maximum number of tests */
#define MAX_TESTS 28

/** @brief Main function for running the Object module unit tests */
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_object_create();
  if (all || test == 2) test2_object_create();
  if (all || test == 3) test1_object_set_name();
  if (all || test == 4) test2_object_set_name();
  if (all || test == 5) test1_object_get_name();
  if (all || test == 6) test2_object_get_name();
  if (all || test == 7) test1_object_get_id();
  if (all || test == 8) test2_object_get_id();
  if (all || test == 9) test1_object_set_description();
  if (all || test == 10) test2_object_set_description();
  if (all || test == 11) test1_object_get_description();
  if (all || test == 12) test2_object_get_description();
  if (all || test == 13) test1_object_set_health();
  if (all || test == 14) test2_object_set_health();
  if (all || test == 15) test1_object_get_health();
  if (all || test == 16) test2_object_get_health();
  if (all || test == 17) test1_object_set_movable();
  if (all || test == 18) test2_object_set_movable();
  if (all || test == 19) test1_object_get_movable();
  if (all || test == 20) test2_object_get_movable();
  if (all || test == 21) test1_object_set_dependency();
  if (all || test == 22) test2_object_set_dependency();
  if (all || test == 23) test1_object_get_dependency();
  if (all || test == 24) test2_object_get_dependency();
  if (all || test == 25) test1_object_set_open();
  if (all || test == 26) test2_object_set_open();
  if (all || test == 27) test1_object_get_open();
  if (all || test == 28) test2_object_get_open();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

/* Tests object creation */
void test1_object_create() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(o != NULL);
  object_destroy(o);
}

/* Tests object creation with invalid id */
void test2_object_create() {
  Object *o = object_create(NO_ID);
  PRINT_TEST_RESULT(o == NULL);
}

/* Tests setting the object name */
void test1_object_set_name() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_name(o, "Sword") == OK);
  object_destroy(o);
}

/* Tests setting the object name with invalid parameters */
void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "Sword") == ERROR);
}

/* Tests getting the object name */
void test1_object_get_name() {
  Object *o = object_create(1);
  object_set_name(o, "Sword");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "Sword") == 0);
  object_destroy(o);
}

/* Tests getting the object name with invalid parameters */
void test2_object_get_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

/* Tests getting the object id */
void test1_object_get_id() {
  Object *o = object_create(7);
  PRINT_TEST_RESULT(object_get_id(o) == 7);
  object_destroy(o);
}

/* Tests getting the object id with invalid parameters */
void test2_object_get_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

/* Tests setting the object description */
void test1_object_set_description() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_description(o, "A shiny sword") == OK);
  object_destroy(o);
}

/* Tests setting the object description with invalid parameters */
void test2_object_set_description() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_description(o, "A shiny sword") == ERROR);
}

/* Tests getting the object description */
void test1_object_get_description() {
  Object *o = object_create(1);
  object_set_description(o, "A shiny sword");
  PRINT_TEST_RESULT(strcmp(object_get_description(o), "A shiny sword") == 0);
  object_destroy(o);
}

/* Tests getting the object description with invalid parameters */
void test2_object_get_description() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_description(o) == NULL);
}

void test1_object_set_health() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_health(o, 15) == OK);
  object_destroy(o);
}

void test2_object_set_health() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_health(o, 15) == ERROR);
}

void test1_object_get_health() {
  Object *o = object_create(1);
  object_set_health(o, 20);
  PRINT_TEST_RESULT(object_get_health(o) == 20);
  object_destroy(o);
}

void test2_object_get_health() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_health(o) == 0);
}

void test1_object_set_movable() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
  object_destroy(o);
}

void test2_object_set_movable() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == ERROR);
}

void test1_object_get_movable() {
  Object *o = object_create(1);
  object_set_movable(o, TRUE);
  PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
  object_destroy(o);
}

void test2_object_get_movable() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

void test1_object_set_dependency() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_dependency(o, 4) == OK);
  object_destroy(o);
}

void test2_object_set_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_dependency(o, 4) == ERROR);
}

void test1_object_get_dependency() {
  Object *o = object_create(1);
  object_set_dependency(o, 4);
  PRINT_TEST_RESULT(object_get_dependency(o) == 4);
  object_destroy(o);
}

void test2_object_get_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}

void test1_object_set_open() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_open(o, 7) == OK);
  object_destroy(o);
}

void test2_object_set_open() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_open(o, 7) == ERROR);
}

void test1_object_get_open() {
  Object *o = object_create(1);
  object_set_open(o, 7);
  PRINT_TEST_RESULT(object_get_open(o) == 7);
  object_destroy(o);
}

void test2_object_get_open() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}
