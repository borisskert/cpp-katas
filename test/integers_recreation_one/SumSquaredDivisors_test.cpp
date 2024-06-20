#include <utility>
#include <vector>
#include <igloo/igloo_alt.h>
#include "integers_recreation_one/SumSquaredDivisors.h"

using namespace igloo;

using Result = std::vector<std::pair<long long, long long>>;

void testequal(const Result &ans, const Result &sol) {
    Assert::That(ans, Equals(sol));
}

void dotest(long long m, long long n, const Result &expected) {
    testequal(SumSquaredDivisors::listSquared(m, n), expected);
}

Describe(listSquared_Tests) {
    It(Fixed_Tests) {
        dotest(1, 250, {{1,   1},
                        {42,  2500},
                        {246, 84100}});
        dotest(42, 250, {{42,  2500},
                         {246, 84100}});
        dotest(250, 500, {{287, 84100}});
        dotest(300, 600, {});
    }
};
