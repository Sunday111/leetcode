#include "3483.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::totalNumbers;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4]
12

[0,2,2]
2

[6,6,6]
1

[1,3,5]
0


)");

using t3483 = SolutionTests<Solution>;

TEST_P(t3483, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.totalNumbers(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3483,
    t3483::parameters(kCases.size()),
    t3483::name);
