#include <string>
#include <vector>
#include <regex>

std::vector<std::string> split(const std::string &s, const std::string &delimiter);

class Inflatable {
private:
    static Inflatable *create_from(const std::string &s);

public:
    [[nodiscard]] virtual std::vector<int> inflate() const = 0;

    static std::vector<Inflatable *> map_from(const std::vector<std::string> &strings) {
        std::vector<Inflatable *> created;

        for (const std::string &string: strings) {
            created.push_back(Inflatable::create_from(string));
        }

        return created;
    }
};

std::vector<int> inflate_all(std::vector<Inflatable *> &inflatables);

std::vector<int> uncompress(std::string music) {
    const std::vector<std::string> &compressed_values = split(music, ",");
    std::vector<Inflatable *> inflatables = Inflatable::map_from(compressed_values);

    return inflate_all(inflatables);
}

std::vector<int> inflate_all(std::vector<Inflatable *> &inflatables) {
    std::vector<int> all_inflated;

    for (Inflatable *i: inflatables) {
        const std::vector<int> &inflated_items = i->inflate();

        for (const int inflated_item: inflated_items) {
            all_inflated.push_back(inflated_item);
        }
    }

    return all_inflated;
}

template<typename T>
int signum(T val) {
    if (T(0) > val) {
        return -1;
    }

    if (T(0) < val) {
        return 1;
    }

    return 0;
}

class SameInterval : public Inflatable {
private:
    static std::regex interval_regex;

    const int _start;
    const int _end;
    const int _step;

    SameInterval(int start, int end, int step) : _start(start), _end(end), _step(step) {}

public:
    [[nodiscard]] std::vector<int> inflate() const override {
        std::vector<int> inflated;
        int i = _start;

        for (; i != _end; i += _step) {
            inflated.push_back(i);
        }

        inflated.push_back(i);

        return inflated;
    }

    static Inflatable *create_from(const std::string &s) {
        std::smatch match;

        if (!std::regex_search(s, match, interval_regex)) {
            throw std::exception();
        }

        const int start = std::stoi(match[1]);
        const int end = std::stoi(match[2]);
        const std::string parsed_step = match[4];

        const int sign = signum(end - start);

        if (parsed_step.length() > 0) {
            int step = std::stoi(parsed_step) * sign;
            return new SameInterval(start, end, step);
        } else {
            return new SameInterval(start, end, sign);
        }
    }

    static bool accept(const std::string &s) {
        return std::regex_match(s, interval_regex);
    }
};

std::regex SameInterval::interval_regex = std::regex(R"((-?\d+)-(-?\d+)(/(\d+))?)");

class Identical : public Inflatable {
private:
    static std::regex identical_regex;

    const int _value;
    const size_t _count;

    Identical(const int value, const int count) : _value(value), _count(count) {}

public:
    [[nodiscard]] std::vector<int> inflate() const override {
        std::vector<int> inflated;

        for (size_t i = 0; i < _count; i++) {
            inflated.push_back(_value);
        }

        return inflated;
    }

    static Inflatable *create_from(const std::string &s) {
        std::vector<std::string> value_count = split(s, "*");
        std::smatch match;

        if (!std::regex_search(s, match, identical_regex)) {
            throw std::exception();
        }

        const int value = std::stoi(match[1]);
        const int count = std::stoi(match[2]);

        return new Identical(value, count);
    }

    static bool accept(const std::string &s) {
        return std::regex_match(s, identical_regex);
    }
};

std::regex Identical::identical_regex = std::regex(R"((-?\d+)[*](\d+))");

class Simple : public Inflatable {
private:
    const int _value;

    explicit Simple(const int value) : _value(value) {}

public:
    [[nodiscard]] std::vector<int> inflate() const override {
        return std::vector<int>{_value};
    }

    static Inflatable *create_from(const std::string &s) {
        const int value = std::stoi(s);
        return new Simple(value);
    }
};

Inflatable *Inflatable::create_from(const std::string &s) {
    if (SameInterval::accept(s)) {
        return SameInterval::create_from(s);
    }

    if (Identical::accept(s)) {
        return Identical::create_from(s);
    }

    return Simple::create_from(s);
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    std::vector<std::string> substrings;

    size_t start = 0;
    size_t end;
    std::string substring;

    while ((end = s.find(delimiter, start)) != std::string::npos) {
        size_t count = end - start;

        substring = s.substr(start, count);
        substrings.push_back(substring);

        start = end + delimiter.length();
    }

    end = std::min(end, s.length());

    substring = s.substr(start, end);
    substrings.push_back(substring);

    return substrings;
}
