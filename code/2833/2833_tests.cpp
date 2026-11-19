#include "2833.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::furthestDistanceFromOrigin;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"L_RL__R" 3
"_R__LL_" 5
"_______" 7
)");

using t2833 = SolutionTests<Solution>;

TEST_P(t2833, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.furthestDistanceFromOrigin(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2833,
    t2833::parameters(kCases.size()),
    t2833::name);
