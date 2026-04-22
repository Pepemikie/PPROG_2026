#!/bin/bash

# We check if the first argument is provided and is either 0 or 1
if [ -z "$1" ] || [ "$1" != "0" ] && [ "$1" != "1" ]; then
    echo "Error, first argument MUST be 0 (normal execution) or 1 (valgrind)"
    exit 1
fi

# We use a variable to store the value of the first argument, which indicates the mode of execution (normal or valgrind)
MODE=$1

# We search for the test files in the src/ directory and store their names (without the .c extension) in a variable
TESTS=$(find src/ -name '*_test.c' -exec basename {} .c \;)

# We check if the second argument is provided, which indicates the name of a specific test to run
if [ -n "$2" ]; then
    TEST_NAME="$2"

    # We compile the specified test using make
    echo "Compiling the test $TEST_NAME..."
    make "$TEST_NAME"

    # We check if the specified test exists 
    if [ ! -f "$TEST_NAME" ]; then
        echo "Error, the test '$TEST_NAME' does not exist"
        make clean
        exit 1
    fi

    # Execute the test based on the value of MODE (0 for normal execution, 1 for valgrind)
    if [ "$MODE" = "0" ]; then
        echo "Running the test $TEST_NAME..."
        ./"$TEST_NAME"

    else
        echo "Running the test $TEST_NAME with valgrind..."
        valgrind --leak-check=full ./"$TEST_NAME"
    fi

else
    # If therese is no second argument, we execute all the tests found in the src/ directory
    echo "Compiling all tests..."
    make test
    
    # We loop trough the list of tests and ompile each one
    if [ "$MODE" = "0" ]; then
        echo "Running all tests..."
        for TEST in $TESTS; do
            echo "Running the test $TEST..."
            ./"$TEST"
        done

    else
        echo "Running all tests with valgrind..."
        for TEST in $TESTS; do
            echo "Running the test $TEST with valgrind..."
            valgrind --leak-check=full ./"$TEST"
        done
    fi
fi

make clean