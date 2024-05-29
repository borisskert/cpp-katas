#include <string>
#include <unordered_map>
#include <igloo/igloo_alt.h>
#include "simple_assembler_interpreter/assembler.h"

using namespace igloo;

Describe(SimpleAssemberInterpreterSolutionTest) {
    It(TestMov1) {
        std::vector<std::string> program{"mov a 1"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        Assert::That(assembler(program), Equals(out));
    }

    It(TestMov2) {
        std::vector<std::string> program{"mov a 2"};
        std::unordered_map<std::string, int> out{{"a", 2}};
        Assert::That(assembler(program), Equals(out));
    }

    It(TestMovCopyRegister) {
        std::vector<std::string> program{"mov a 2", "mov b a"};
        std::unordered_map<std::string, int> out{{"a", 2},
                                                 {"b", 2}};
        Assert::That(assembler(program), Equals(out));
    }

    It(TestMovCopyZero) {
        std::vector<std::string> program{"mov b a"};
        std::unordered_map<std::string, int> out{{"b", 0}};
        Assert::That(assembler(program), Equals(out));
    }

    It(TestInc1) {
        std::vector<std::string> program{"mov a 1", "inc a"};
        std::unordered_map<std::string, int> out{{"a", 2}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestInc2) {
        std::vector<std::string> program{"mov a 1", "inc a", "inc a"};
        std::unordered_map<std::string, int> out{{"a", 3}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestIncZero) {
        std::vector<std::string> program{"inc a"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestDec1) {
        std::vector<std::string> program{"mov a 0", "dec a"};
        std::unordered_map<std::string, int> out{{"a", -1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestDec2) {
        std::vector<std::string> program{"mov a 0", "dec a", "dec a"};
        std::unordered_map<std::string, int> out{{"a", -2}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestDecZero) {
        std::vector<std::string> program{"dec a", "dec a"};
        std::unordered_map<std::string, int> out{{"a", -2}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestJnzNoJumpByRegister) {
        std::vector<std::string> program{"mov a 0", "jnz a 2", "inc a 1"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestJnzJumpByRegister) {
        std::vector<std::string> program{"mov a 1", "jnz a 2", "inc a 1"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestJnzNoJumpByConstant) {
        std::vector<std::string> program{"mov a 0", "jnz 0 2", "inc a 1"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(TestJnzJumpByConstant) {
        std::vector<std::string> program{"mov a 1", "jnz 1 2", "inc a 1"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        const std::unordered_map<std::string, int> &actual = assembler(program);

        Assert::That(actual, Equals(out));
    }

    It(Simple1) {
        std::vector<std::string> program{"mov a 5", "inc a", "dec a", "dec a",
                                         "jnz a -1", "inc a"};
        std::unordered_map<std::string, int> out{{"a", 1}};
        Assert::That(assembler(program), Equals(out));
    }
};
