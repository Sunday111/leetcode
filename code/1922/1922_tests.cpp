#include "1922.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countGoodNumbers;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 5

4 400

50 564908303

806166225460393 643535977
)cases");

using t1922 = SolutionTests<Solution>;

TEST_P(t1922, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countGoodNumbers(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1922,
    t1922::parameters(kCases.size()),
    t1922::name);
