#include "2144.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3] 5
[6,5,7,9,2,2] 23
[5,5] 10
)");

using t2144 = SolutionTests<Solution>;

TEST_P(t2144, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2144,
    t2144::parameters(kCases.size()),
    t2144::name);
