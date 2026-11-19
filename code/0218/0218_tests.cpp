#include "0218.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getSkyline;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]] [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]
)cases");

using t0218 = SolutionTests<Solution>;

TEST_P(t0218, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getSkyline(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0218,
    t0218::parameters(kCases.size()),
    t0218::name);
