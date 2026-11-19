#include "3875.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniformArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,3]
true

[4,6]
true


)");

using t3875 = SolutionTests<Solution>;

TEST_P(t3875, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.uniformArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3875,
    t3875::parameters(kCases.size()),
    t3875::name);
