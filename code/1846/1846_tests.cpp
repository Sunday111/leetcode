#include "1846.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::maximumElementAfterDecrementingAndRearranging;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,2,1,2,1]     2
[100,1,1000]    3
[1,2,3,4,5]     5
)");

using t1846 = SolutionTests<Solution>;

TEST_P(t1846, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        {
            return solution.maximumElementAfterDecrementingAndRearranging(
                args...);
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1846,
    t1846::parameters(kCases.size()),
    t1846::name);
