#include "2839.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canBeEqual;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcd"
"cdab"
true

"abcd"
"dacb"
false
)");

using t2839 = SolutionTests<Solution>;

TEST_P(t2839, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.canBeEqual(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2839,
    t2839::parameters(kCases.size()),
    t2839::name);
