#include "1689.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minPartitions;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"32"
3

"82734"
8

"27346209830709182346"
9

)");

using t1689 = SolutionTests<Solution>;

TEST_P(t1689, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minPartitions(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1689,
    t1689::parameters(kCases.size()),
    t1689::name);
