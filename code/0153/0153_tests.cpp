#include "0153.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMin;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] 1
[4,5,6,7,0,1,2] 0
[11,13,15,17] 11
)");

using t0153 = SolutionTests<Solution>;

TEST_P(t0153, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findMin(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0153,
    t0153::parameters(kCases.size()),
    t0153::name);
