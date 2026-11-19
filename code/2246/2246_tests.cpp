#include "2246.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestPath;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[-1,0,0,1,1,2] "abacbe" 3

[-1,0,0,0] "aabc" 3
)cases");

using t2246_longest_path_with_different_adjacent_characters =
    SolutionTests<Solution>;

TEST_P(t2246_longest_path_with_different_adjacent_characters, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestPath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2246_longest_path_with_different_adjacent_characters,
    t2246_longest_path_with_different_adjacent_characters::parameters(
        kCases.size()),
    t2246_longest_path_with_different_adjacent_characters::name);
