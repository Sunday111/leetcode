#include "1344.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::angleClock;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
12 30 165
 3 30  75
 3 15 7.5
)");

using t1344 = SolutionTests<Solution>;

TEST_P(t1344, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.angleClock(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1344,
    t1344::parameters(kCases.size()),
    t1344::name);
