#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>

/**
 * https://www.codewars.com/kata/55c6126177c9441a570000cc/train/cpp
 */
class WeightSort {
public:
    static std::string orderWeight(const std::string &strng);
};

class Weight {
private:
    std::string _raw;
    unsigned int crossSum;

    Weight(std::string raw, const unsigned int crossSum) : _raw(std::move(raw)), crossSum(crossSum) {}

    static unsigned int crossSumOf(const std::string &);

    static Weight from(const std::string &);

public:
    Weight &operator=(const Weight &other) = default;

    Weight(const Weight &) = default;

    bool operator<(const Weight &other) const;

    [[nodiscard]] std::string raw() const {
        return this->_raw;
    }

    static std::vector<Weight> parse_from(const std::string &strng);
};

namespace weight_for_weight {
    /**
     * Easy string join with a specified delimiter
     */
    class Join {
    private:
        const std::string delimiter;
        std::vector<std::string> strings;

        Join() = default;

        [[nodiscard]] std::string join_strings() const;

    public:
        explicit Join(std::string delimiter) : delimiter(std::move(delimiter)) {}

        void append(const std::string &str) {
            this->strings.push_back(str);
        }

        std::string build();
    };
}

std::string WeightSort::orderWeight(const std::string &strng) {
    std::vector<Weight> weights = Weight::parse_from(strng);

    std::sort(weights.begin(), weights.end());

    weight_for_weight::Join join = weight_for_weight::Join(" ");
    for (const Weight &weight: weights) {
        join.append(weight.raw());
    }

    return join.build();
}

bool Weight::operator<(const Weight &other) const {
    if (this->crossSum == other.crossSum) {
        return this->_raw < other._raw;
    }

    return this->crossSum < other.crossSum;
}

std::vector<Weight> Weight::parse_from(const std::string &strng) {
    std::vector<Weight> weights;
    std::stringstream words(strng);

    std::string word;
    while (words >> word) {
        Weight weight = Weight::from(word);
        weights.push_back(weight);
    }

    return weights;
}

Weight Weight::from(const std::string &raw) {
    return {raw, crossSumOf(raw)};
}

unsigned int Weight::crossSumOf(const std::string &weight) {
    unsigned int crossSum = 0;

    for (char c: weight) {
        crossSum += c - '0';
    }

    return crossSum;
}

namespace weight_for_weight {
    std::string Join::build() {
        if (this->strings.empty()) {
            return "";
        }

        return join_strings();
    }

    std::string Join::join_strings() const {
        std::string joined;

        size_t ultimo = strings.size() - 1;
        size_t index = 0;

        for (; index < ultimo; index++) {
            joined.append(this->strings[index]);
            joined.append(this->delimiter);
        }

        joined.append(this->strings[index]);

        return joined;
    }
}
