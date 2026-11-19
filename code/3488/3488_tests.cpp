#include "3488.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::solveQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,1,4,1,3,2]
[0,3,5]
[2,-1,3]

[1,2,3,4]
[0,1,2,3]
[-1,-1,-1,-1]


)");

using t3488 = SolutionTests<Solution>;

TEST_P(t3488, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.solveQueries(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3488,
    t3488::parameters(kCases.size()),
    t3488::name);
