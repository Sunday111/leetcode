#include "0442.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findDuplicates;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,3,2,7,8,2,3,1] [2,3]
[1,1,2]           [1]
[1]               []
)");

using t0442 = SolutionTests<Solution>;

TEST_P(t0442, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findDuplicates(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0442,
    t0442::parameters(kCases.size()),
    t0442::name);
