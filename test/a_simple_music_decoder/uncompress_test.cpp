#include <igloo/igloo_alt.h>
#include "a_simple_music_decoder/uncompress.h"

using namespace igloo;

Describe(A_Simple_Music_Decoder_Tests) {
    It(Sample_tests) {
        Assert::That(uncompress("1,2*2,3"), Equals(std::vector<int>{1, 2, 2, 3}));
        Assert::That(uncompress("1,3-5,7"), Equals(std::vector<int>{1, 3, 4, 5, 7}));
        Assert::That(uncompress("1,5-3,7"), Equals(std::vector<int>{1, 5, 4, 3, 7}));
        Assert::That(uncompress("1,10-6/2,7"), Equals(std::vector<int>{1, 10, 8, 6, 7}));
    }

    It(Fixed_tests) {
        Assert::That(uncompress("1,2*5,3*3"), Equals(std::vector<int>{1, 2, 2, 2, 2, 2, 3, 3, 3}));
        Assert::That(uncompress("1-3,3-7,9-12"), Equals(std::vector<int>{1, 2, 3, 3, 4, 5, 6, 7, 9, 10, 11, 12}));
        Assert::That(uncompress("10-100/10"), Equals(std::vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}));
        Assert::That(uncompress("-3--1,-3*5,-15--5/5"), Equals(std::vector<int>{-3, -2, -1, -3, -3, -3, -3, -3, -15, -10, -5}));
    }

    It(Fixed_Negative_tests) {
        Assert::That(uncompress("-3--1"), Equals(std::vector<int>{-3, -2, -1}));
        Assert::That(uncompress("-3*5"), Equals(std::vector<int>{-3, -3, -3, -3, -3}));
        Assert::That(uncompress("-15--5/5"), Equals(std::vector<int>{-15, -10, -5}));
        Assert::That(uncompress("-3--1,-3*5,-15--5/5"),
                     Equals(std::vector<int>{-3, -2, -1, -3, -3, -3, -3, -3, -15, -10, -5}));
    }

    It(Further_tests) {
        Assert::That(uncompress("25,170*5,149*2,161,2-6/2"),
                     Equals(std::vector<int>{25, 170, 170, 170, 170, 170, 149, 149, 161, 2, 4, 6}));
        Assert::That(uncompress("74,108,5*2,164-161,53,6-18/3,72-64/2"),
                     Equals(std::vector<int>{74, 108, 5, 5, 164, 163, 162, 161, 53, 6, 9, 12, 15, 18, 72, 70, 68, 66,
                                             64}));
        Assert::That(uncompress("-2*2"), Equals(std::vector<int>{-2, -2}));
        Assert::That(uncompress("1*2,2-5,7,9"), Equals(std::vector<int>{1, 1, 2, 3, 4, 5, 7, 9}));
        Assert::That(uncompress("1--5/2"), Equals(std::vector<int>{1, -1, -3, -5}));
    }
};
