#include "2840.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcdba"
"cabdab"
true

"abe"
"bea"
false
)");

using t2840 = SolutionTests<Solution>;

TEST_P(t2840, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.checkStrings(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2840,
    t2840::parameters(kCases.size()),
    t2840::name);
