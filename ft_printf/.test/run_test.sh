#!/bin/bash

echo -n 'Enter test case : '
read TEST_CASE

# FLAGS="-g -fsanitize=address"

# if [ $TEST_CASE = "BIG_MIX" ]
# then
# 	gcc -D ${TEST_CASE} test_main.c ../libftprintf.a && ./a.out | grep -v '_'
# 	exit
# fi
gcc -D ${TEST_CASE} test_main.c ../libftprintf.a && ./a.out
# gcc -D ${TEST_CASE} test_main.c && ./a.out
