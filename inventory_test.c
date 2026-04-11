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

#define MAX_TESTS 9

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
  Inventory *inv = inventory_create(2);
  inventory_add_object(inv, 10);
  Set *objs = inventory_get_objects(inv);
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
