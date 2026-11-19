#include "3546.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canPartitionGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[2,3]]
true

[[1,3],[2,4]]
false


)");

using t3546 = SolutionTests<Solution>;

TEST_P(t3546, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.canPartitionGrid(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3546,
    t3546::parameters(kCases.size()),
    t3546::name);
