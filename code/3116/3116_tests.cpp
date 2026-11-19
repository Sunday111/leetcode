#include "3116.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findKthSmallest;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,6,9]
3
9

[5,2]
7
12


)");

using t3116 = SolutionTests<Solution>;

TEST_P(t3116, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findKthSmallest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3116,
    t3116::parameters(kCases.size()),
    t3116::name);
