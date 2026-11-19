#include "3510.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumPairRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,2,3,1] 2

[1,2,2] 0

[1,1,4,1] 2

[1,1,4,4,2,-4,-1] 5

[3,6,-9,6,3,-4] 4
)cases");

using t3510 = SolutionTests<Solution>;

TEST_P(t3510, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumPairRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3510,
    t3510::parameters(kCases.size()),
    t3510::name);
