#include "3704.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countNoZeroPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1000000000000000 50891681057058
)cases");

using t3704 = SolutionTests<Solution>;

TEST_P(t3704, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countNoZeroPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3704,
    t3704::parameters(kCases.size()),
    t3704::name);
