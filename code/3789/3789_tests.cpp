#include "3789.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
2
1
3
2
3

5
4
15
2
3
22

5
4
15
0
0
0


)");

using t3789 = SolutionTests<Solution>;

TEST_P(t3789, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3789,
    t3789::parameters(kCases.size()),
    t3789::name);
