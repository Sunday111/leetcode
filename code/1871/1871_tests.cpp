#include "1871.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canReach;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"011010"
2
3
true

"01101110"
2
3
false
)");

using t1871 = SolutionTests<Solution>;

TEST_P(t1871, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.canReach(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1871,
    t1871::parameters(kCases.size()),
    t1871::name);
