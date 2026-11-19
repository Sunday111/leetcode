#include "1503.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLastMoment;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 [4,3] [0,1] 4
)cases");

using t1503 = SolutionTests<Solution>;

TEST_P(t1503, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLastMoment(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1503,
    t1503::parameters(kCases.size()),
    t1503::name);
