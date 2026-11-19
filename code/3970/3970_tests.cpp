#include "3970.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::shortestPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
1
3

3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
2
2

3
[[0,1,1],[1,2,1]]
"aaa"
2
-1


)");

using t3970 = SolutionTests<Solution>;

TEST_P(t3970, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.shortestPath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3970,
    t3970::parameters(kCases.size()),
    t3970::name);
