#include "2405.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::partitionString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abacaba" 4

"ssssss" 6
)");

using t2405 = SolutionTests<Solution>;

TEST_P(t2405, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.partitionString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2405,
    t2405::parameters(kCases.size()),
    t2405::name);
