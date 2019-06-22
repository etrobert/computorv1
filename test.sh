#!/bin/bash

COLORGREEN='\033[92m'
COLOREND='\033[0m'
COLORRED='\033[31m'

test () {
  echo "Testing $1 against $2"
  diff <(./computor "$1") $2\
    && echo -e "$COLORGREEN TEST SUCCESS $COLOREND"\
    || echo -e "$COLORRED TEST ERROR $COLOREND"
}

test "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" tests/1.out
test "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0" tests/2.out
test "5 * X^0 + 4 * X^1 = 4 * X^0" tests/3.out
test "1.5 * X^0 + 0 * X^1 + 1.5 * X^2 = 0 * X^0" tests/4.out
test "0 * X^0 = 0 * X^0" tests/5.out
test "0 * X^0 = 1 * X^1" tests/6.out
test "1 * X^0 = -1 * X^1" tests/7.out
test "0 * X^0 + 0 * X^1 - 1 * X^2 = 0 * X^0" tests/8.out
test "hello" tests/9.out
test "5 * X^0 + 4333333333232333333333333333 * X^1 - 9.3 * X^2 = 1 * X^0" tests/10.out
test "0 * X^0 = -1 * X^1" tests/11.out
test "5 * X^0 + 433333 * X^1 + 92222222222222222222222222222222222222 * X^2 = 1 * X^0" tests/12.out
