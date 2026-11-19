#include "2265.hpp"
#include "leet_code_binary_tree.hpp"  // IWYU pragma: keep
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::averageOfSubtree;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,8,5,0,1,null,6]  5
[1]                 1
)");

using t2265 = SolutionTests<Solution>;

TEST_P(t2265, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.averageOfSubtree(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2265,
    t2265::parameters(kCases.size()),
    t2265::name);
