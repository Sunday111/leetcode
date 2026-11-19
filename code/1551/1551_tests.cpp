#include "1551.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
2

6
9

50
625

51
650

)");

using t1551 = SolutionTests<Solution>;

TEST_P(t1551, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1551,
    t1551::parameters(kCases.size()),
    t1551::name);
