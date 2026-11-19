#include "1886.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findRotation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1],[1,0]]
[[1,0],[0,1]]
true

[[0,1],[1,1]]
[[1,0],[0,1]]
false

[[0,0,0],[0,1,0],[1,1,1]]
[[1,1,1],[0,1,0],[0,0,0]]
true

[[1]]
[[0]]
false
)");

using t1886 = SolutionTests<Solution>;

TEST_P(t1886, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findRotation(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1886,
    t1886::parameters(kCases.size()),
    t1886::name);
