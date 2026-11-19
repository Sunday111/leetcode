#include "1833.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxIceCream;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2,4,1]     7 4
[10,6,8,7,7,8]  5 0
[1,6,3,1,2,5]  20 6
)");

using t1833 = SolutionTests<Solution>;

TEST_P(t1833, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxIceCream(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1833,
    t1833::parameters(kCases.size()),
    t1833::name);
