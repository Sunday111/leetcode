#include "1432.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxDiff;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
111 888
)cases");

using t1432 = SolutionTests<Solution>;

TEST_P(t1432, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxDiff(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1432,
    t1432::parameters(kCases.size()),
    t1432::name);
