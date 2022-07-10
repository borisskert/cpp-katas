#ifndef CPP_KATAS_AUTOMATON_H
#define CPP_KATAS_AUTOMATON_H

#include <vector>

class Automaton {
public:
    Automaton();

    bool read_commands(const std::vector<char> &commands);
};

#endif //CPP_KATAS_AUTOMATON_H
