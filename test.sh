#!/bin/bash

diff <(./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0") tests/1.out
diff <(./computor "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0") tests/2.out
diff <(./computor "5 * X^0 + 4 * X^1 = 4 * X^0") tests/3.out
diff <(./computor "1.5 * X^0 + 0 * X^1 + 1.5 * X^2 = 0") tests/4.out
diff <(./computor "0 * X^0 = 0 * X^0") tests/5.out
