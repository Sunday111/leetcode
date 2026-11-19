#include "3567.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minAbsDiff;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[20195,15337,73189,16963,-90840],[10664,-43796,-61984,13235,-33619]]
2
[[4673,18188,3728,3728]]


[[1,8],[3,-2]]
2
[[2]]

[[3,-1]]
1
[[0,0]]

[[1,-2,3],[2,3,5]]
2
[[1,2]]


)");

using t3567 = SolutionTests<Solution>;

TEST_P(t3567, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minAbsDiff(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3567,
    t3567::parameters(kCases.size()),
    t3567::name);
