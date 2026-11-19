#include "1340.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[6,4,14,6,8,13,9,7,10,6,12]
2
4
[3,3,3,3,3]
3
1
[7,6,5,4,3,2,1]
1
7
)");

using t1340 = SolutionTests<Solution>;

TEST_P(t1340, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxJumps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1340,
    t1340::parameters(kCases.size()),
    t1340::name);
