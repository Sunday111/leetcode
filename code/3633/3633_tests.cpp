#include "3633.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::earliestFinishTime;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,8]
[4,1]
[6]
[3]
9

[5]
[3]
[1]
[10]
14


)");

using t3633 = SolutionTests<Solution>;

TEST_P(t3633, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.earliestFinishTime(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3633,
    t3633::parameters(kCases.size()),
    t3633::name);
