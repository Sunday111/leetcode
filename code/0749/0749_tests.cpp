#include "0749.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::containVirus;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]] 10

[[1,1,1],[1,0,1],[1,1,1]] 4

[[1,1,1,0,0,0,0,0,0],[1,0,1,0,1,1,1,1,1],[1,1,1,0,0,0,0,0,0]] 13
)cases");

using t0749 = SolutionTests<Solution>;

TEST_P(t0749, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.containVirus(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0749,
    t0749::parameters(kCases.size()),
    t0749::name);
