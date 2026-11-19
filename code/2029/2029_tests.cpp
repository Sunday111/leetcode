#include "2029.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameIX;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,1]           true
[2]             false
[5,1,2,4,3]     false
[20,3,20,17,2,12,15,17,4] true
)");

using t2029 = SolutionTests<Solution>;

TEST_P(t2029, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.stoneGameIX(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2029,
    t2029::parameters(kCases.size()),
    t2029::name);
