#include <utility>
#include <vector>
#include <cmath>

/**
 * https://www.codewars.com/kata/55aa075506463dac6600010d/train/cpp
 */
class SumSquaredDivisors {
public:
    static std::vector<std::pair<long long, long long>> listSquared(long long m, long long n);
};

static std::vector<long long> divisors(long long n) {
    std::vector<long long> divs;

    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divs.push_back(i);

            if (i != n / i) {
                divs.push_back(n / i);
            }
        }
    }

    return divs;
}

static long long squaredSum(const std::vector<long long> &divs) {
    long long sum = 0;

    for (long long div: divs) {
        sum += div * div;
    }

    return sum;
}

static bool isSquare(long long n) {
    auto root = (long long) sqrt(n);
    return root * root == n;
}

std::vector<std::pair<long long, long long>> SumSquaredDivisors::listSquared(long long int m, long long int n) {
    std::vector<std::pair<long long, long long>> result;

    for (long long i = m; i <= n; i++) {
        std::vector<long long> divs = divisors(i);
        long long sum = squaredSum(divs);

        if (isSquare(sum)) {
            result.emplace_back(i, sum);
        }
    }

    return result;
}
