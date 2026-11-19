#include "1722.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumHammingDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4]
[2,1,4,5]
[[0,1],[2,3]]
1

[1,2,3,4]
[1,3,2,4]
[]
2

[5,1,2,4,3]
[1,5,4,2,3]
[[0,4],[4,2],[1,3],[1,4]]
0
)");

using t1722 = SolutionTests<Solution>;

TEST_P(t1722, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumHammingDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1722,
    t1722::parameters(kCases.size()),
    t1722::name);
