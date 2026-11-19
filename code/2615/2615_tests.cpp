#include "2615.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::distance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,1,1,2] [5,0,3,4,0]
[0,5,3]     [0,0,0]
)");

using t2615 = SolutionTests<Solution>;

TEST_P(t2615, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.distance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2615,
    t2615::parameters(kCases.size()),
    t2615::name);
