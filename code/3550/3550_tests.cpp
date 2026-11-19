#include "3550.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestIndex;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2]
2

[1,10,11]
1

[1,2,3]
-1


)");

using t3550 = SolutionTests<Solution>;

TEST_P(t3550, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestIndex(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3550,
    t3550::parameters(kCases.size()),
    t3550::name);
