#include "0016_3sum_closest.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::threeSumClosest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,2,1,-4] 1 2

[0,0,0] 1 0

[1,5,6,7,8] 10 12

[2,3,8,9,10] 16 15

[-1000,-5,-5,-5,-1] -14 -15

[-2,-1,1,4] 0 1

[0,1,2] 3 3

[0,3,97,102,200] 300 300
)");

using t0016_3sum_closest = SolutionTests<Solution>;

TEST_P(t0016_3sum_closest, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.threeSumClosest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0016_3sum_closest,
    t0016_3sum_closest::parameters(kCases.size()),
    t0016_3sum_closest::name);
