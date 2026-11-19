#include "1201.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 2 3 5 4

4 2 3 4 6

5 2 11 13 10

1000000000 2 740091218 473796308 2000000000
)cases");

using t1201 = SolutionTests<Solution>;

TEST_P(t1201, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.nthUglyNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1201,
    t1201::parameters(kCases.size()),
    t1201::name);
