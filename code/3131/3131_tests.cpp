#include "3131.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::addedInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,4]
[9,7,5]
3

[10]
[5]
-5

[1,1,1,1]
[1,1,1,1]
0


)");

using t3131 = SolutionTests<Solution>;

TEST_P(t3131, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.addedInteger(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3131,
    t3131::parameters(kCases.size()),
    t3131::name);
