#include "2273.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["a","b","c","d","e"] ["a","b","c","d","e"]

["abba","baba","bbaa","cd","cd"] ["abba","cd"]
)cases");

using t2273_find_resultant_array_after_removing_anagrams =
    SolutionTests<Solution>;

TEST_P(t2273_find_resultant_array_after_removing_anagrams, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.removeAnagrams(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2273_find_resultant_array_after_removing_anagrams,
    t2273_find_resultant_array_after_removing_anagrams::parameters(
        kCases.size()),
    t2273_find_resultant_array_after_removing_anagrams::name);
