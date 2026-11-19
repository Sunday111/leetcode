#include "2573.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findTheString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
"abab"

[[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
"aaaa"

[[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
""

[[2,2],[2,1]]
""

[[3, 0, 1], [0, 2, 1], [1, 1, 1]]
""

[[3, 2, 0], [2, 2, 1], [0, 1, 1]]
""

[[4,1,1,1],[1,3,1,1],[1,1,2,1],[1,1,1,1]]
""

[[3,2,0],[2,2,0],[0,0,1]]
""
)");

using t2573 = SolutionTests<Solution>;

TEST_P(t2573, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findTheString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2573,
    t2573::parameters(kCases.size()),
    t2573::name);
