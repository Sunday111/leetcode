#include "3583.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::specialTriplets;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[6,3,6] 1

[0,1,0,0] 1
)cases");

using t3583 = SolutionTests<Solution>;

TEST_P(t3583, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.specialTriplets(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3583,
    t3583::parameters(kCases.size()),
    t3583::name);
