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

#define MAX_TESTS 12

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
