#include "0959.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::regionsBySlashes;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[" /","/ "]     2
[" /","  "]     1
["/\","\/"]   5
)");

using t0959 = SolutionTests<Solution>;

TEST_P(t0959, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.regionsBySlashes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0959,
    t0959::parameters(kCases.size()),
    t0959::name);
