#include "1284.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minFlips;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0],[1],[1]]       1
[[0,1,1]]           1
[[0,0],[0,1]]       3
[[0]]               0
[[1,0,0],[1,0,0]]   -1
)");

using t1284 = SolutionTests<Solution>;

TEST_P(t1284, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minFlips(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1284,
    t1284::parameters(kCases.size()),
    t1284::name);
