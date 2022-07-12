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

class Greed {
private:
    const std::vector<int> _dice;

    Rule *matching_rule();

    explicit Greed(std::vector<int> dice) : _dice(std::move(dice)) {}

public:
    int score();

    static Greed from(const std::vector<int> &dice);
};

int score(const std::vector<int> &dice) {
    return Greed::from(dice).score();
}

class Three : public Rule {
private:
    const int _value;
    const int _points;

public:
    Three(int value, int point) : _value(value), _points(point) {}

    bool matches(const std::vector<int> &dice) override;

    int points() override { return _points; };

    std::vector<int> remaining(const std::vector<int> &dice) override;
};

class One : public Rule {
private:
    const int _value;
    const int _points;

public:
    One(int value, int point) : _value(value), _points(point) {}

    bool matches(const std::vector<int> &dice) override;

    int points() override { return _points; };
};

bool Rule::matches(const std::vector<int> &dice) {
    return true;
};

std::vector<int> Rule::remaining(const std::vector<int> &dice) {
    std::vector<int> copy;
    copy = dice;
    copy.erase(copy.cbegin());

    return copy;
}

bool Three::matches(const std::vector<int> &dice) {
    return dice.size() >= 3 &&
           dice.at(0) == _value &&
           dice.at(1) == _value &&
           dice.at(2) == _value;
};

std::vector<int> Three::remaining(const std::vector<int> &dice) {
    std::vector<int> copy = dice;
    copy.erase(copy.cbegin());
    copy.erase(copy.cbegin());
    copy.erase(copy.cbegin());

    return copy;
}

bool One::matches(const std::vector<int> &dice) {
    return !dice.empty() &&
           dice.at(0) == _value;
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

Rule *Greed::matching_rule() {
    for (Rule *rule: rules) {
        if (rule->matches(_dice)) {
            return rule;
        }
    }

    throw std::exception();
}

int Greed::score() {
    if (_dice.empty()) {
        return 0;
    }

    Rule *rule = matching_rule();
    auto *greed = new Greed(rule->remaining(_dice));

    return rule->points() + greed->score();
}

Greed Greed::from(const std::vector<int> &dice) {
    std::vector<int> copy = dice;
    std::sort(copy.begin(), copy.end());

    return Greed(copy);
}
