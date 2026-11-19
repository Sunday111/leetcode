#include "1079.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numTilePossibilities;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"AAB" 8

"AAABBC" 188

"V" 1
)cases");

using t1079 = SolutionTests<Solution>;

TEST_P(t1079, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numTilePossibilities(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1079,
    t1079::parameters(kCases.size()),
    t1079::name);
