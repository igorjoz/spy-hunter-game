#include "Helper.h"


#include <string.h>
#include <cstdlib>


int Helper::convertDigitsArrayIntoNumber(char digits[], int length) {
    int number = 0;

    for (int i = 0; i < length; i++) {
        int digit = digits[i] - '0';

        number = number * 10 + digit;
    }

    return number;
}


char* Helper::convertNumberIntoDigitsArray(int number) {
    char digits[100];
    _itoa_s(number, digits, 10);

    return digits;
}
