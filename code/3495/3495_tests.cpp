#include "3495.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minOperations;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2],[2,4]] 3
)cases");

using t3495 = SolutionTests<Solution>;

TEST_P(t3495, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3495,
    t3495::parameters(kCases.size()),
    t3495::name);
