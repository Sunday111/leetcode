#include "2515.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::closestTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["hello","i","am","leetcode","hello"]
"hello"
1
1
["a","b","leetcode"]
"leetcode"
0
1
["i","eat","leetcode"]
"ate"
0
-1
)");

using t2515 = SolutionTests<Solution>;

TEST_P(t2515, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.closestTarget(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2515,
    t2515::parameters(kCases.size()),
    t2515::name);
