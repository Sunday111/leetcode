#include "1079_letter_tile_possibilities.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numTilePossibilities;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"AAB" 8

"AAABBC" 188

"V" 1
)cases");

using t1079_letter_tile_possibilities = SolutionTests<Solution>;

TEST_P(t1079_letter_tile_possibilities, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numTilePossibilities(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1079_letter_tile_possibilities,
    t1079_letter_tile_possibilities::parameters(kCases.size()),
    t1079_letter_tile_possibilities::name);
