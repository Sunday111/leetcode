#include "1563.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameV;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[6,2,3,4,5,5]               18
[7,7,7,7,7,7,7]             28
[4]                         0
)");

using t1563 = SolutionTests<Solution>;

TEST_P(t1563, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stoneGameV(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1563,
    t1563::parameters(kCases.size()),
    t1563::name);
