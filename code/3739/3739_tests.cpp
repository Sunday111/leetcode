#include "3739.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countMajoritySubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,2,3]
2
5

[1,1,1,1]
1
10

[1,2,3]
4
0


)");

using t3739 = SolutionTests<Solution>;

TEST_P(t3739, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countMajoritySubarrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3739,
    t3739::parameters(kCases.size()),
    t3739::name);
