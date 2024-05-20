#include <igloo/igloo_alt.h>
#include "find_the_smallest/to_smallest.h"

using namespace igloo;

#include <vector>

void testequal(std::vector<long long> ans, std::vector<long long> sol) {
    Assert::That(ans, Equals(sol));
}

static void dotest(long long n, std::vector<long long> expected) {
    testequal(ToSmallest::smallest(n), expected);
}

Describe(smallest_Tests) {
    It(Fixed_Tests) {
        dotest(261235, {126235, 2, 0});
        dotest(209917, {29917, 0, 1});
        dotest(285365, {238565, 3, 1});
        dotest(269045, {26945, 3, 0});
        dotest(296837, {239687, 4, 1});
        dotest(261235209917281352, {26123529917281352, 7, 0});
    }
};
