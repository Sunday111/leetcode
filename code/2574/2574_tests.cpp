#include "2574.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::leftRightDifference;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,4,8,3] [15,1,11,22]
[1] [0]
)");

using t2574 = SolutionTests<Solution>;

TEST_P(t2574, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.leftRightDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2574,
    t2574::parameters(kCases.size()),
    t2574::name);
