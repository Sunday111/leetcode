#include "1334.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findTheCity;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
4
3

5
[[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]]
2
0
)");

using t1334 = SolutionTests<Solution>;

TEST_P(t1334, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findTheCity(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1334,
    t1334::parameters(kCases.size()),
    t1334::name);
