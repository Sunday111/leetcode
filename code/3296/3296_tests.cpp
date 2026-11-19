#include "3296.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minNumberOfSeconds;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[2,1,1]
3

10
[3,2,2,4]
12

5
[1]
15

8
[1,1]
10

1
[5]
5

)");

using t3296 = SolutionTests<Solution>;

TEST_P(t3296, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minNumberOfSeconds(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3296,
    t3296::parameters(kCases.size()),
    t3296::name);
