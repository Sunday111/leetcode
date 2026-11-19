#include "0973.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::kClosest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3],[-2,2]] 1 [[-2,2]]
)cases");

using t0973 = SolutionTests<Solution>;

TEST_P(t0973, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.kClosest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0973,
    t0973::parameters(kCases.size()),
    t0973::name);
