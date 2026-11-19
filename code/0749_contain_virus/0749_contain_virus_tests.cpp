#include "0749_contain_virus.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::containVirus;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]] 10

[[1,1,1],[1,0,1],[1,1,1]] 4

[[1,1,1,0,0,0,0,0,0],[1,0,1,0,1,1,1,1,1],[1,1,1,0,0,0,0,0,0]] 13
)cases");

using t0749_contain_virus = SolutionTests<Solution>;

TEST_P(t0749_contain_virus, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.containVirus(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0749_contain_virus,
    t0749_contain_virus::parameters(kCases.size()),
    t0749_contain_virus::name);
