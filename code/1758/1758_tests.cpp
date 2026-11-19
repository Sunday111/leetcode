#include "1758.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"0100"
1

"10"
0

"1111"
2

)");

using t1758 = SolutionTests<Solution>;

TEST_P(t1758, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1758,
    t1758::parameters(kCases.size()),
    t1758::name);
