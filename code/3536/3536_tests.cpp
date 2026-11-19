#include "3536.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
31
3

22
4

124
8


)");

using t3536 = SolutionTests<Solution>;

TEST_P(t3536, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxProduct(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3536,
    t3536::parameters(kCases.size()),
    t3536::name);
