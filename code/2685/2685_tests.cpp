#include "2685.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countCompleteComponents;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
6 [[0,1],[0,2],[1,2],[3,4]]       3
6 [[0,1],[0,2],[1,2],[3,4],[3,5]] 1
)");

using t2685 = SolutionTests<Solution>;

TEST_P(t2685, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countCompleteComponents(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2685,
    t2685::parameters(kCases.size()),
    t2685::name);
