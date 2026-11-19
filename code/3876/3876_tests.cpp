#include "3876.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniformArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,4,7]
true

[2,3]
false

[4,6]
true


)");

using t3876 = SolutionTests<Solution>;

TEST_P(t3876, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.uniformArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3876,
    t3876::parameters(kCases.size()),
    t3876::name);
