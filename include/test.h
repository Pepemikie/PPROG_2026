/**
 * @brief It defines the test interface
 *
 * @file test.h
 * @author José Miguel Romero Oubiña
 * @version 0
 * @date 25-03-2026
 * @copyright GNU Public License
 */

#ifndef _TEST_H
#define _TEST_H

#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef NOCOLOR
#define KRED  "\x1B[31m" /**< Red color */
#define KGRN  "\x1B[32m" /**< Green color */
#define KYEL  "\x1B[33m" /**< Yellow color */
#define KCYN  "\x1B[36m" /**< Cyan color */
#define RESET "\033[0m"  /**< Reset color */
#else
#define KRED  /**< Red color */
#define KGRN  /**< Green color */
#define KYEL  /**< Yellow color */
#define KCYN  /**< Cyan color */
#define RESET /**< Reset color */
#endif

/**
 * @brief prints the test results
 * 
 * @param x is a parameter
 * 
 */
#define PRINT_TEST_RESULT(x) 	do{			\
    __test_counter++;							\
    __pass = (x);							\
    __test_passed = (__pass)? __test_passed + 1 : __test_passed;	\
    printf(KYEL "%s" RESET " line "  "%d " KCYN "%s" RESET ": %s\n",	\
	   __FILE__, __LINE__ , __FUNCTION__,				\
	   ((!__pass) ? KRED "NOT PASS" RESET : KGRN "PASS" RESET));	\
  } while (0)

#define PRINT_PASSED_PERCENTAGE printf("Tests passed %d%%\n", ((__test_passed * 100) / __test_counter))/**< prints the percentage of the tests passed */
      
static int __test_counter = 0; /**< number of tests */
static int __test_passed  = 0;/**< how many test has been passed */
static int __pass = 0;/**< how many to pass */

#endif
