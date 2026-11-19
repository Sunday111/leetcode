#include "0020.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isValid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()"
true

"()[]{}"
true

"(]"
false

"([])"
true

"([)]"
false


)cases");

using t0020 = SolutionTests<Solution>;

TEST_P(t0020, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isValid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0020,
    t0020::parameters(kCases.size()),
    t0020::name);
