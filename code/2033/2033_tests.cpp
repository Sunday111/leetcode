#include "2033.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4],[6,8]] 2 4
[[1,5],[2,3]] 1 5
[[1,2],[3,4]] 2 -1
)");

using t2033 = SolutionTests<Solution>;

TEST_P(t2033, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minOperations(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2033,
    t2033::parameters(kCases.size()),
    t2033::name);
