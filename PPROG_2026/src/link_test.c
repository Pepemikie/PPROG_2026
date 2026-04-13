/** 
 * @brief Implementation of the Link module unit tests
 * @file link_test.c
 * @author Iñaki López Rocha
 * @date 01-04-2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 8

int main(int argc, char** argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_get_id();
  if (all || test == 4) test1_link_name();
  if (all || test == 5) test1_link_space_ids();
  if (all || test == 6) test1_link_direction();
  if (all || test == 7) test1_link_open();
  if (all || test == 8) test2_link_get_name();

  PRINT_PASSED_PERCENTAGE;
  return 0;
}

/* Tests link creation */
void test1_link_create() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(l != NULL);
  link_destroy(l);
}

/* Tests link creation with invalid id */
void test2_link_create() {
  Link *l = link_create(NO_ID);
  PRINT_TEST_RESULT(l == NULL);
}

/* Tests getting the id of a link */
void test1_link_get_id() {
  Link *l = link_create(2);
  PRINT_TEST_RESULT(link_get_id(l) == 2);
  link_destroy(l);
}

/* Tests setting and getting the link name */
void test1_link_name() {
  Link *l = link_create(1);
  link_set_name(l, "door");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "door") == 0);
  link_destroy(l);
}

/* Tests setting and getting the origin and destination of a link */
void test1_link_space_ids() {
  Link *l = link_create(1);
  link_set_origin(l, 10);
  link_set_destination(l, 20);
  PRINT_TEST_RESULT(link_get_origin(l) == 10 && link_get_destination(l) == 20);
  link_destroy(l);
}

/* Tests setting and getting the link direction */
void test1_link_direction() {
  Link *l = link_create(1);
  link_set_direction(l, N);
  PRINT_TEST_RESULT(link_get_direction(l) == N);
  link_destroy(l);
}

/* Tests setting and getting whether a link is open */
void test1_link_open() {
  Link *l = link_create(1);
  link_set_open(l, TRUE);
  PRINT_TEST_RESULT(link_get_open(l) == TRUE);
  link_destroy(l);
}

/* Tests getting the name of a link with invalid parameters */
void test2_link_get_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_name(l) == NULL);
}
