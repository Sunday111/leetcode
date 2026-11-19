#include "2267.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::hasValidPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]   true
[[")",")"],["(","("]]                                       false
)cases");

using t2267 = SolutionTests<Solution>;

TEST_P(t2267, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.hasValidPath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2267,
    t2267::parameters(kCases.size()),
    t2267::name);
