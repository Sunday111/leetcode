#include "3635.hpp"
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

using t3635 = SolutionTests<Solution>;

TEST_P(t3635, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.earliestFinishTime(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3635,
    t3635::parameters(kCases.size()),
    t3635::name);
