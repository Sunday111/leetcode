#include "0953_verifying_an_alien_dictionary.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isAlienSorted;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["hello","leetcode"] "hlabcdefgijkmnopqrstuvwxyz" true
)cases");

using t0953_verifying_an_alien_dictionary = SolutionTests<Solution>;

TEST_P(t0953_verifying_an_alien_dictionary, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isAlienSorted(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0953_verifying_an_alien_dictionary,
    t0953_verifying_an_alien_dictionary::parameters(kCases.size()),
    t0953_verifying_an_alien_dictionary::name);
