#include "1665.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumEffort;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2],[2,4],[4,8]] 8
[[1,3],[2,4],[10,11],[10,12],[8,9]] 32
[[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]] 27
)");

using t1665 = SolutionTests<Solution>;

TEST_P(t1665, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumEffort(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1665,
    t1665::parameters(kCases.size()),
    t1665::name);
