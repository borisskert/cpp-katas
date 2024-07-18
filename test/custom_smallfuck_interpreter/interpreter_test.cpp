#include <igloo/igloo_alt.h>
#include "custom_smallfuck_interpreter/interpreter.h"

using namespace igloo;

Describe(your_interpreter) {
    It(should_work_for_some_example_test_cases) {
        // Flips the leftmost cell of the tape
        Assert::That(interpreter("*", "00101100"), Equals("10101100"));
        // Flips the second and third cell of the tape
        Assert::That(interpreter(">*>*", "00101100"), Equals("01001100"));
        // Flips all the bits in the tape
        Assert::That(interpreter("*>*>*>*>*>*>*>*", "00101100"), Equals("11010011"));
        // Flips all the bits that are initialized to 0
        Assert::That(interpreter("*>*>>*>>>*>*", "00101100"), Equals("11111111"));
        // Goes somewhere to the right of the tape and then flips all bits that are initialized to 1, progressing leftwards through the tape
        Assert::That(interpreter(">>>>>*<*<<*", "00101100"), Equals("00000000"));
        // should_work_for_some_simple_and_nested_loops
        Assert::That(
                interpreter(
                        "*[>*]",
                        "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
                ),
                Equals("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));
    }
};
