#include "0438.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"cbaebabacd" "abc" [0,6]

"abab" "ab" [0,1,2]
)cases");

using t0438_find_all_anagrams_in_a_string = SolutionTests<Solution>;

TEST_P(t0438_find_all_anagrams_in_a_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findAnagrams(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0438_find_all_anagrams_in_a_string,
    t0438_find_all_anagrams_in_a_string::parameters(kCases.size()),
    t0438_find_all_anagrams_in_a_string::name);
