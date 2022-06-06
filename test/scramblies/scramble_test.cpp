#include <igloo/igloo_alt.h>
#include "scramblies/scramble.h"

using namespace igloo;

Describe(Scramble) {
    It(BasicTests) {
        Assert::That(scramble("rkqodlw", "world"), Equals(true));
        Assert::That(scramble("cedewaraaossoqqyt", "codewars"), Equals(true));
        Assert::That(scramble("katas", "steak"), Equals(false));
        Assert::That(scramble("scriptjavx", "javascript"), Equals(false));
        Assert::That(scramble("scriptingjava", "javascript"), Equals(true));
        Assert::That(scramble("scriptsjava", "javascript"), Equals(true));
        Assert::That(scramble("javscripts", "javascript"), Equals(false));
        Assert::That(scramble("aabbcamaomsccdd", "commas"), Equals(true));
        Assert::That(scramble("commas", "commas"), Equals(true));
        Assert::That(scramble("sammoc", "commas"), Equals(true));
    }
};
