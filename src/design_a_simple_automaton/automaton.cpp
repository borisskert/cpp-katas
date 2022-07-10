#include <vector>

/**
 * https://www.codewars.com/kata/5268acac0d3f019add000203/train/cpp
 */
class Automaton {
public:
    Automaton();

    bool read_commands(const std::vector<char> &commands);
};

Automaton::Automaton() = default;

class State {
public:
    virtual State *transition(char command) = 0;

    virtual bool is_final() {
        return false;
    }
};

class Q1 : public State {
    State *transition(char command) override;
};

class Q2 : public State {
    State *transition(char command) override;

    bool is_final() override {
        return true;
    }
};

class Q3 : public State {
    State *transition(char command) override;
};

bool Automaton::read_commands(const std::vector<char> &commands) {
    State *state = new Q1();

    for (const char &command: commands) {
        state = state->transition(command);
    }

    return state->is_final();
}

State *Q1::transition(char command) {
    if (command == '1') {
        return new Q2();
    }

    return this;
}

State *Q2::transition(char c) {
    if (c == '0') {
        return new Q3();
    }

    return this;
}

State *Q3::transition(char c) {
    return new Q2();
}
