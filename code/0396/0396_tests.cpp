#include "0396.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxRotateFunction;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,3,2,6] 26
[100] 0
)");

using t0396 = SolutionTests<Solution>;

TEST_P(t0396, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRotateFunction(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0396,
    t0396::parameters(kCases.size()),
    t0396::name);
