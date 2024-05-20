#include <vector>
#include <algorithm>
#include <string>

/**
 * https://www.codewars.com/kata/573992c724fc289553000e95/train/cpp
 */
class ToSmallest {
public:
    static std::vector<long long> smallest(long long n);
};

class NumberUtils {
private:
    NumberUtils() = default;

public:
    static std::vector<unsigned short> digits(long long n);

    static long long int from_digits(const std::vector<unsigned short> &digits);

    static unsigned int length(long long n);
};

class Result {
public:
    const long long int value;
    const unsigned int i;
    const unsigned int j;

    Result(long long int value, const unsigned int i, const unsigned int j) : value(value), i(i), j(j) {}

    [[nodiscard]] std::vector<long long> to_vector() const {
        return {value, i, j};
    }

    bool operator<(const Result &rhs) const {
        return value < rhs.value;
    }
};

class IntPair {
private:
    IntPair() : i(0), j(0) {}

    IntPair(int i, int j) : i(i), j(j) {}

public:
    const int i;
    const int j;

    static std::vector<Result> potential_results(long long n);

    [[nodiscard]] long long moveDigit(long long n) const;

    static std::vector<IntPair> cartesian_product(unsigned long n);
};

std::vector<unsigned short> NumberUtils::digits(long long int n) {
    std::vector<unsigned short> digits;

    while (n > 0) {
        digits.insert(digits.begin(), n % 10);
        n /= 10;
    }

    return digits;
}

long long int NumberUtils::from_digits(const std::vector<unsigned short> &digits) {
    long long int n = digits.at(0);

    for (int i = 1; i < digits.size(); i++) {
        n = n * 10 + digits.at(i);
    }

    return n;
}

unsigned int NumberUtils::length(long long int n) {
    return std::to_string(n).length();
}

std::vector<IntPair> IntPair::cartesian_product(unsigned long n) {
    std::vector<IntPair> pairs;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pairs.push_back(IntPair(i, j));
        }
    }

    return pairs;
}

std::vector<Result> IntPair::potential_results(long long int n) {
    unsigned int length = NumberUtils::length(n);
    const std::vector<IntPair> &pairs = IntPair::cartesian_product(length);

    std::vector<Result> results;

    for (const IntPair &pair: pairs) {
        long long int value = n;

        value = pair.moveDigit(n);
        results.emplace_back(value, pair.i, pair.j);
    }

    return results;
}

long long IntPair::moveDigit(long long int n) const {
    std::vector<unsigned short> digits = NumberUtils::digits(n);
    int digit = digits.at(i);

    digits.erase(digits.begin() + i);
    digits.insert(digits.begin() + j, digit);

    return NumberUtils::from_digits(digits);
}

std::vector<long long> ToSmallest::smallest(long long int n) {
    std::vector<Result> results = IntPair::potential_results(n);
    auto min = std::min_element(begin(results), end(results));

    return min->to_vector();
}
