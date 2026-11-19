#include "2787.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 2 1
)cases");

using t2787 = SolutionTests<Solution>;

TEST_P(t2787, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2787,
    t2787::parameters(kCases.size()),
    t2787::name);
