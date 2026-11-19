#include "1727.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestSubmatrix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0,1],[1,1,1],[1,0,1]]
4
[[1,0,1,0,1]]
3
[[1,1,0],[1,0,1]]
2
)");

using t1727 = SolutionTests<Solution>;

TEST_P(t1727, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestSubmatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1727,
    t1727::parameters(kCases.size()),
    t1727::name);
