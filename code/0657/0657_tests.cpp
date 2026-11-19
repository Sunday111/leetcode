#include "0657.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::judgeCircle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"UD" true
"LL" false
)");

using t0657 = SolutionTests<Solution>;

TEST_P(t0657, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.judgeCircle(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0657,
    t0657::parameters(kCases.size()),
    t0657::name);
