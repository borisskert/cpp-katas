#include <igloo/igloo_alt.h>
#include "directions_reduction/dir_reduction.h"
#include "greed_is_good/score.h"

using namespace igloo;

Describe(GreedisGood_test) {
    It(Sample_Test) {
        Assert::That(score({2, 3, 4, 6, 2}), Equals(0));
        Assert::That(score({2, 4, 4, 5, 4}), Equals(450));
    }
};
