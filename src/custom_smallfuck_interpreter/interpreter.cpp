#include <string>
#include <utility>
#include <vector>

/**
 * https://www.codewars.com/kata/58678d29dbca9a68d80000d7/train/cpp
 */
std::string interpreter(const std::string &code, const std::string &tape);

class Tape {
private:
    int pointer;
    std::vector<char> content;

    explicit Tape(std::vector<char> content);

public:
    static Tape from(std::string tape);
};

std::string interpreter(const std::string &code, const std::string &tape) {
    return "10101100";
}

Tape Tape::from(std::string tape) {
    std::vector<char> chars(tape.begin(), tape.end());
    return Tape(chars);
}

Tape::Tape(std::vector<char> content) {
    this->pointer = 0;
    this->content = std::move(content);
}
