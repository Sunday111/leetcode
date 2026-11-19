#include "3464.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
[[0,0],[1,2],[2,0],[2,2],[2,1]]
4
1

2
[[0,2],[2,0],[2,2],[0,0]]
4
2

1000000000
[[0,1000000000],[1000000000,0],[1000000000,1000000000],[0,0]]
4
1000000000



2
[[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]]
5
1


)");

using t3464 = SolutionTests<Solution>;

TEST_P(t3464, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3464,
    t3464::parameters(kCases.size()),
    t3464::name);
