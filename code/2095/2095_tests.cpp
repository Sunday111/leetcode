#include "2095.hpp"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::deleteMiddle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,4,7,1,2,6] [1,3,4,1,2,6]
[1,2,3,4]       [1,2,4]
[2,1]           [2]
)");

using t2095 = SolutionTests<Solution>;

TEST_P(t2095, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.deleteMiddle(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2095,
    t2095::parameters(kCases.size()),
    t2095::name);
