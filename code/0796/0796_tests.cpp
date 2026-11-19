#include "0796.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotateString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcde"
"cdeab"
true

"abcde"
"abced"
false
)");

using t0796 = SolutionTests<Solution>;

TEST_P(t0796, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.rotateString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0796,
    t0796::parameters(kCases.size()),
    t0796::name);
