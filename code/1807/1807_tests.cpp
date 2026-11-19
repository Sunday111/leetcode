#include "1807.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::evaluate;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"(name)is(age)yearsold"
[["name","bob"],["age","two"]]
"bobistwoyearsold"

"hi(name)"
[["a","b"]]
"hi?"
)cases");

using t1807 = SolutionTests<Solution>;

TEST_P(t1807, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.evaluate(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1807,
    t1807::parameters(kCases.size()),
    t1807::name);
