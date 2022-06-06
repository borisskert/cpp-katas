#include<string>
#include <unordered_map>
#include <algorithm>

/*
 * https://www.codewars.com/kata/55c04b4cc56a697bb0000048/train/cpp
 */

class Scramblies {
private:
    const std::unordered_map<char, int> _counts;

    explicit Scramblies(std::unordered_map<char, int> counts) : _counts(std::move(counts)) {}

public:
    [[nodiscard]] Scramblies increaseAll(const std::string &s) const;

    [[nodiscard]] Scramblies decreaseAll(const std::string &s) const;

    [[nodiscard]] bool allNonNegative() const;

    static Scramblies empty() {
        return Scramblies(std::unordered_map<char, int>(0));
    }
};

bool scramble(const std::string &s1, const std::string &s2) {
    return Scramblies::empty()
            .increaseAll(s1)
            .decreaseAll(s2)
            .allNonNegative();
}

Scramblies Scramblies::increaseAll(const std::string &s) const {
    std::unordered_map<char, int> counts = this->_counts;

    for (const char c: s) {
        int count = counts[c];
        counts[c] = count + 1;
    }

    return Scramblies(counts);
}

Scramblies Scramblies::decreaseAll(const std::string &s) const {
    std::unordered_map<char, int> counts = this->_counts;

    for (const char c: s) {
        int count = counts[c];
        counts[c] = count - 1;
    }

    return Scramblies(counts);
}

bool Scramblies::allNonNegative() const {
    return std::all_of(
            this->_counts.begin(),
            this->_counts.end(),
            [&](const std::pair<const char, int> &item) {
                return item.second >= 0;
            });
}
