#include "3867.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::gcdSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,4]
2

[3,6,2,8]
5


)");

using t3867 = SolutionTests<Solution>;

TEST_P(t3867, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.gcdSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3867,
    t3867::parameters(kCases.size()),
    t3867::name);
