#include "1752.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::check;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] true
[2,1,3,4] false
[1,2,3] true
)");

using t1752 = SolutionTests<Solution>;

TEST_P(t1752, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.check(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1752,
    t1752::parameters(kCases.size()),
    t1752::name);
