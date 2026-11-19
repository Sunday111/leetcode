#include "2309.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::greatestLetter;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"lEeTcOdE" "E"
"arRAzFif" "R"
"AbCdEfGhIjK" ""
)");

using t2309 = SolutionTests<Solution>;

TEST_P(t2309, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.greatestLetter(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2309,
    t2309::parameters(kCases.size()),
    t2309::name);
