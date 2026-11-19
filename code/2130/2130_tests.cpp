#include "2130.hpp"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "leet_code_list.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pairSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[5,4,2,1] 6
[4,2,2,3] 7
[1,100000] 100001
)");

using t2130 = SolutionTests<Solution>;

TEST_P(t2130, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.pairSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2130,
    t2130::parameters(kCases.size()),
    t2130::name);
