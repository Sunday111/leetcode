#include "2698.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::punishmentNumber;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
182

37
1478

1000
10804657
)");

using t2698 = SolutionTests<Solution>;

TEST_P(t2698, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.punishmentNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2698,
    t2698::parameters(kCases.size()),
    t2698::name);
