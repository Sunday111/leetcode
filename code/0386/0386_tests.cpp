#include "0386.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lexicalOrder;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
13 [1,10,11,12,13,2,3,4,5,6,7,8,9]
)cases");

using t0386 = SolutionTests<Solution>;

TEST_P(t0386, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lexicalOrder(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0386,
    t0386::parameters(kCases.size()),
    t0386::name);
