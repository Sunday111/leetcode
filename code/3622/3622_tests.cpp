#include "3622.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkDivisibility;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
99
true

23
false


)");

using t3622 = SolutionTests<Solution>;

TEST_P(t3622, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.checkDivisibility(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3622,
    t3622::parameters(kCases.size()),
    t3622::name);
