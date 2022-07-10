#include <igloo/igloo_alt.h>
#include "design_a_simple_automaton/automaton.h"

using namespace igloo;

Describe(BasicTests) {
    It(Test1) {
        auto automata = Automaton();
        Assert::That(automata.read_commands({'1'}), Equals(true));
    }

    It(Test2) {
        auto automata = Automaton();
        Assert::That(automata.read_commands({'1', '0', '0', '1'}), Equals(true));
    }
};
