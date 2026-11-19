#include "3658.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::gcdOfOddEvenSums;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
4

5
5


)");

using t3658 = SolutionTests<Solution>;

TEST_P(t3658, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.gcdOfOddEvenSums(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3658,
    t3658::parameters(kCases.size()),
    t3658::name);
