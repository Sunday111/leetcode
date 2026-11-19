#include "1288.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::removeCoveredIntervals;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[3,6],[2,8]]     2
[[1,4],[2,3]]           1
)");

using t1288 = SolutionTests<Solution>;

TEST_P(t1288, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.removeCoveredIntervals(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1288,
    t1288::parameters(kCases.size()),
    t1288::name);
