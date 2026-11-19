#include "1872.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameVIII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[7,-6,5,10,5,-2,-6] 13
[-1,2,-3,4,-5] 5
)");

using t1872 = SolutionTests<Solution>;

TEST_P(t1872, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stoneGameVIII(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1872,
    t1872::parameters(kCases.size()),
    t1872::name);
