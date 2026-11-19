#include "2770.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,6,4,1,2] 2 3
[1,3,6,4,1,2] 3 5
[1,3,6,4,1,2] 0 -1
)");

using t2770 = SolutionTests<Solution>;

TEST_P(t2770, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumJumps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2770,
    t2770::parameters(kCases.size()),
    t2770::name);
