#include "0966_vowel_spellcheck.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spellchecker;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["KiTe","kite","hare","Hare"]
["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
)cases");

using t0966_vowel_spellcheck = SolutionTests<Solution>;

TEST_P(t0966_vowel_spellcheck, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.spellchecker(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0966_vowel_spellcheck,
    t0966_vowel_spellcheck::parameters(kCases.size()),
    t0966_vowel_spellcheck::name);
