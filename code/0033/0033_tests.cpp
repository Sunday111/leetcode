#include "0033.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::search;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,5,6,7,0,1,2]
0
4

[4,5,6,7,0,1,2]
3
-1

[1]
0
-1
)");

using t0033 = SolutionTests<Solution>;

TEST_P(t0033, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.search(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0033,
    t0033::parameters(kCases.size()),
    t0033::name);
