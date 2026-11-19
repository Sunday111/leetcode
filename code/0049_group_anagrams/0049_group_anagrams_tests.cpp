#include "0049_group_anagrams.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"
#include "test_utility.hpp"

static constexpr auto kMethodToTest = &Solution::groupAnagrams;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["eat","tea","tan","ate","nat","bat"] [["ate","eat","tea"],["bat"],["nat","tan"]]
)cases");

using t0049_group_anagrams = SolutionTests<Solution>;

TEST_P(t0049_group_anagrams, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args) { return solution.groupAnagrams(args...); },
                inputs);
            ASSERT_EQ(sorted(expected), sorted(actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0049_group_anagrams,
    t0049_group_anagrams::parameters(kCases.size()),
    t0049_group_anagrams::name);
