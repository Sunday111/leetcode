#include "0010.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isMatch;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aa" "a*" true
"ab" ".*" true
"mississippi" "mis*is*ip*." true
"bbbba" ".*a*a" true
"a" ".*..a*" false
"baa" ".ba" false
"bbab" "b*a*" false
"bbba" ".*b" false
)");

using t0010 = SolutionTests<Solution>;

TEST_P(t0010, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isMatch(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0010,
    t0010::parameters(kCases.size()),
    t0010::name);
