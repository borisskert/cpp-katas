#include <igloo/igloo_alt.h>
#include "create_phone_number/create_phone_number.h"

using namespace igloo;

Describe(CreatePhoneNumber) {
    It(BasicTests1) {
        static const int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
        Assert::That(createPhoneNumber(arr), Equals("(123) 456-7890"));
    }

    It(BasicTests2) {
        static const int arr[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        Assert::That(createPhoneNumber(arr), Equals("(111) 111-1111"));
    }

    It(BasicTests3) {
        static const int arr[10] = {1, 2, 3, 4, 5, 6, 8, 8, 0, 0};
        Assert::That(createPhoneNumber(arr), Equals("(123) 456-8800"));
    }

    It(BasicTests4) {
        static const int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        Assert::That(createPhoneNumber(arr), Equals("(000) 000-0000"));
    }
};
