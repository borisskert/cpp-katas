#include <utility>
#include <vector>
#include <algorithm>

/*
 * https://www.codewars.com/kata/5270d0d18625160ada0000e4/train/cpp
 */

class Rule {
public:
    virtual bool matches(const std::vector<int> &dice);

    virtual int points() { return 0; };

    virtual std::vector<int> remaining(const std::vector<int> &dice);
};

class Three : public Rule {
private:
    const int _value;
    const int _points;

public:
    Three(int value, int point) : _value(value), _points(point) {}

    bool matches(const std::vector<int> &dice) override {
        return dice.size() >= 3 &&
               dice.at(0) == _value &&
               dice.at(1) == _value &&
               dice.at(2) == _value;
    };

    int points() override {
        return _points;
    };

    std::vector<int> remaining(const std::vector<int> &dice) override {
        std::vector<int> copy = dice;
        copy.erase(copy.cbegin());
        copy.erase(copy.cbegin());
        copy.erase(copy.cbegin());

        return copy;
    }
};

class One : public Rule {
private:
    const int _value;
    const int _points;

public:
    One(int value, int point) : _value(value), _points(point) {}

    bool matches(const std::vector<int> &dice) override {
        return !dice.empty() &&
               dice.at(0) == _value;
    };

    int points() override {
        return _points;
    };
};

const std::vector<Rule *> rules = std::vector<Rule *>{
        new Three(1, 1000),
        new Three(6, 600),
        new Three(5, 500),
        new Three(4, 400),
        new Three(3, 300),
        new Three(2, 200),
        new One(1, 100),
        new One(5, 50),
        new Rule()
};

class Greed {
private:
    const std::vector<int> _dice;

    Rule *matching_rule() {
        for (Rule *rule: rules) {
            if (rule->matches(_dice)) {
                return rule;
            }
        }

        throw std::exception();
    }

    explicit Greed(std::vector<int> dice) : _dice(std::move(dice)) {}

public:
    int score() {
        if (_dice.empty()) {
            return 0;
        }

        Rule *rule = matching_rule();
        auto *greed = new Greed(rule->remaining(_dice));

        return rule->points() + greed->score();
    }

    static Greed from(const std::vector<int> &dice) {
        std::vector<int> copy = dice;
        std::sort(copy.begin(), copy.end());

        return Greed(copy);
    }
};

int score(const std::vector<int> &dice) {
    return Greed::from(dice).score();
}

bool Rule::matches(const std::vector<int> &dice) {
    return true;
};

std::vector<int> Rule::remaining(const std::vector<int> &dice) {
    std::vector<int> copy;
    copy = dice;
    copy.erase(copy.cbegin());

    return copy;
}
