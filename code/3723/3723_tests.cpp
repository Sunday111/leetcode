#include "3723.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSumOfSquares;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
3
"30"

2
17
"98"

1
10
""


)");

using t3723 = SolutionTests<Solution>;

TEST_P(t3723, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSumOfSquares(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3723,
    t3723::parameters(kCases.size()),
    t3723::name);
