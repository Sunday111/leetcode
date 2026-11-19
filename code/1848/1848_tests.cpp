#include "1848.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getMinDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4,5]
5
3
1

[1]
1
0
0

[1,1,1,1,1,1,1,1,1,1]
1
0
0
)");

using t1848 = SolutionTests<Solution>;

TEST_P(t1848, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getMinDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1848,
    t1848::parameters(kCases.size()),
    t1848::name);
