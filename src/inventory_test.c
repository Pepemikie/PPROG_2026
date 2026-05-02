/** 
 * @brief Implementation of the Inventory module unit tests
 * @file inventory_test.c
 * @author Iñaki López Rocha
 * @date 01-04-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory.h"
#include "inventory_test.h"
#include "set.h"
#include "test.h"

/** @brief Maximum number of tests */
#define MAX_TESTS 16 

/** @brief Main function for running inventory tests */
int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Inventory:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();
  if (all || test == 3) test1_inventory_add_del();
  if (all || test == 4) test1_inventory_has_object();
  if (all || test == 5) test1_inventory_full_empty();
  if (all || test == 6) test1_inventory_max_objs();
  if (all || test == 7) test1_inventory_number_of_objects();
  if (all || test == 8) test1_inventory_get_objects();
  if (all || test == 9) test1_inventory_set_objects();
  if (all || test == 10) test2_inventory_add_del();
  if (all || test == 11) test2_inventory_has_object();
  if (all || test == 12) test2_inventory_full_empty();
  if (all || test == 13) test2_inventory_get_objects();
  if (all || test == 14) test2_inventory_set_objects();
  if (all || test == 15) test2_inventory_get_max_objs();
  if (all || test == 16) test2_inventory_number_of_objects();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

/* Tests inventory creation */
void test1_inventory_create() {
  Inventory *inv = inventory_create(3);
  PRINT_TEST_RESULT(inv != NULL);
  inventory_destroy(inv);
}

/* Tests inventory creation with invalid parameters */
void test2_inventory_create() {
  Inventory *inv = inventory_create(0);
  PRINT_TEST_RESULT(inv == NULL);
}

/* Tests adding and removing objects from an inventory */
void test1_inventory_add_del() {
  Inventory *inv = inventory_create(2);
  PRINT_TEST_RESULT(inventory_add_object(inv, 5) == OK && inventory_del_object(inv, 5) == OK);
  inventory_destroy(inv);
}

/* Tests checking whether an object is in the inventory */
void test1_inventory_has_object() {
  Inventory *inv = inventory_create(2);
  inventory_add_object(inv, 6);
  PRINT_TEST_RESULT(inventory_has_object(inv, 6) == TRUE && inventory_has_object(inv, NO_ID) == FALSE);
  inventory_destroy(inv);
}

/* Tests inventory fullness and emptiness */
void test1_inventory_full_empty() {
  Inventory *inv = inventory_create(1);
  PRINT_TEST_RESULT(inventory_is_empty(inv) == TRUE);
  inventory_add_object(inv, 7);
  PRINT_TEST_RESULT(inventory_is_full(inv) == TRUE);
  inventory_destroy(inv);
}

/* Tests getting and setting the inventory max object capacity */
void test1_inventory_max_objs() {
  Inventory *inv = inventory_create(2);
  PRINT_TEST_RESULT(inventory_set_max_objs(inv, 3) == OK && inventory_get_max_objs(inv) == 3);
  inventory_set_max_objs(inv, 0);
  PRINT_TEST_RESULT(inventory_set_max_objs(inv, 0) == ERROR);
  inventory_destroy(inv);
}

/* Tests getting the number of objects in the inventory */
void test1_inventory_number_of_objects() {
  Inventory *inv = inventory_create(3);
  inventory_add_object(inv, 8);
  inventory_add_object(inv, 9);
  PRINT_TEST_RESULT(inventory_get_number_of_objects(inv) == 2);
  inventory_destroy(inv);
}

/* Tests getting the inventory objects set pointer */
void test1_inventory_get_objects() {
  Set *objs = NULL;
  Inventory *inv = inventory_create(2);
  inventory_add_object(inv, 10);
  objs = inventory_get_objects(inv);
  PRINT_TEST_RESULT(objs != NULL && inventory_has_object(inv, 10) == TRUE);
  inventory_destroy(inv);
}

/* Tests setting inventory objects with a new set */
void test1_inventory_set_objects() {
  Inventory *inv = inventory_create(2);
  Set *new_objs = set_create();
  set_add(new_objs, 11);
  PRINT_TEST_RESULT(inventory_set_objects(inv, new_objs) == OK && inventory_has_object(inv, 11) == TRUE);
  inventory_destroy(inv);
}

void test2_inventory_add_del() {
  Inventory *inv = NULL;
  PRINT_TEST_RESULT(inventory_add_object(inv, 5) == ERROR && inventory_del_object(inv, 5) == ERROR);
}

void test2_inventory_has_object() {
  PRINT_TEST_RESULT(inventory_has_object(NULL, 5) == FALSE && inventory_has_object(NULL, NO_ID) == FALSE);
}

void test2_inventory_full_empty() {
  PRINT_TEST_RESULT(inventory_is_empty(NULL) == TRUE && inventory_is_full(NULL) == FALSE);
}

void test2_inventory_get_objects() {
  PRINT_TEST_RESULT(inventory_get_objects(NULL) == NULL);
}

void test2_inventory_set_objects() {
  Inventory *inv = inventory_create(2);
  Set *new_objs = set_create();
  PRINT_TEST_RESULT(inventory_set_objects(NULL, new_objs) == ERROR && inventory_set_objects(inv, NULL) == ERROR);
  set_destroy(new_objs);
  inventory_destroy(inv);
}

void test2_inventory_number_of_objects() {
  PRINT_TEST_RESULT(inventory_get_number_of_objects(NULL) == -1);
}

void test2_inventory_get_max_objs() {
  PRINT_TEST_RESULT(inventory_get_max_objs(NULL) == -1);
}
