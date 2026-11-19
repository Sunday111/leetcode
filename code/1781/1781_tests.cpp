#include "1781.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::beautySum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
    "aabcb"     5
    "aabcbaa"   17
)");

using t1781 = SolutionTests<Solution>;

TEST_P(t1781, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.beautySum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1781,
    t1781::parameters(kCases.size()),
    t1781::name);
