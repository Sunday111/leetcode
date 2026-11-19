#include "3027.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,5],[128653,-2370425]] 1
)cases");

using t3027 = SolutionTests<Solution>;

TEST_P(t3027, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3027,
    t3027::parameters(kCases.size()),
    t3027::name);
