#!/bin/bash

# We check if the first argument is provided and is either 0 or 1
if [ -z "$1" ] || [ "$1" != "0" ] && [ "$1" != "1" ]; then
    echo "Error, first argument MUST be 0 (normal execution) or 1 (valgrind)"
    exit 1
fi

# Execution mode:
# 0 -> normal
# 1 -> valgrind
MODE=$1

# Search unit test files
TESTS=$(find src/ -name '*_test.c' -exec basename {} .c \;)

# =========================
# UNIT TESTS
# =========================

if [ -n "$2" ]; then

    TEST_NAME="$2"

    echo "Compiling the test $TEST_NAME..."
    make "$TEST_NAME"

    if [ ! -f "$TEST_NAME" ]; then
        echo "Error, the test '$TEST_NAME' does not exist"
        make clean
        exit 1
    fi

    if [ "$MODE" = "0" ]; then
        echo "Running the test $TEST_NAME..."
        ./"$TEST_NAME"
    else
        echo "Running the test $TEST_NAME with valgrind..."
        valgrind --leak-check=full ./"$TEST_NAME"
    fi

else

    echo "Compiling all unit tests..."
    make test

    if [ "$MODE" = "0" ]; then

        echo ""
        echo "=============================="
        echo "RUNNING UNIT TESTS"
        echo "=============================="

        for TEST in $TESTS; do
            echo ""
            echo "Running test $TEST..."
            ./"$TEST"
        done

    else

        echo ""
        echo "=============================="
        echo "RUNNING UNIT TESTS WITH VALGRIND"
        echo "=============================="

        for TEST in $TESTS; do
            echo ""
            echo "Running test $TEST with valgrind..."
            valgrind --leak-check=full ./"$TEST"
        done
    fi

    # =========================
    # INTEGRATION TESTS
    # =========================

    echo ""
    echo "=============================="
    echo "RUNNING INTEGRATION TESTS"
    echo "=============================="

    # Compile integration version
    make all

    INTEGRATION_TESTS_UNIPLAYER="game1 game2 game3 game4 game_win"
    INTEGRATION_TESTS_MULTIPLAYER="game_team"

    FAILED=0

    for TEST in $INTEGRATION_TESTS_UNIPLAYER; do

        echo ""
        echo "Running integration test $TEST..."

        rm -f ${TEST}.log

        ./rob_the_museum museum_uniplayer.dat -l ${TEST}.log -d < ${TEST}.cmd > /dev/null

        diff ${TEST}.log tests/${TEST}.expected > /dev/null

        if [ $? -eq 0 ]; then
            echo "[PASS] $TEST"
        else
            echo "[FAIL] $TEST"
            FAILED=1

            echo "Differences found:"
            diff output.log tests/${TEST}.expected
        fi
    done

    for TEST in $INTEGRATION_TESTS_MULTIPLAYER; do

        echo ""
        echo "Running integration test $TEST..."

        rm -f ${TEST}.log

        ./rob_the_museum museum.dat -l ${TEST}.log -d < ${TEST}.cmd > /dev/null

        diff ${TEST}.log tests/${TEST}.expected > /dev/null

        if [ $? -eq 0 ]; then
            echo "[PASS] $TEST"
        else
            echo "[FAIL] $TEST"
            FAILED=1

            echo "Differences found:"
            diff output.log tests/${TEST}.expected
        fi
    done

    echo ""

    if [ $FAILED -eq 0 ]; then
        echo "ALL INTEGRATION TESTS PASSED"
    else
        echo "SOME INTEGRATION TESTS FAILED"
    fi
fi

