#include "3718.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::missingMultiple;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[8,2,3,4,6]
2
10

[1,4,7,10,15]
5
5


)");

using t3718 = SolutionTests<Solution>;

TEST_P(t3718, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.missingMultiple(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3718,
    t3718::parameters(kCases.size()),
    t3718::name);
