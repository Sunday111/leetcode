#include "1123_lowest_common_ancestor_of_deepest_leaves.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::lcaDeepestLeaves;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,5,1,6,2,0,8,null,null,7,4] [2,7,4]
)cases");

using t1123_lowest_common_ancestor_of_deepest_leaves = SolutionTests<Solution>;

TEST_P(t1123_lowest_common_ancestor_of_deepest_leaves, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto actual = std::apply(
                [&](auto&... args)
                { return solution.lcaDeepestLeaves(args...); },
                inputs);
            ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1123_lowest_common_ancestor_of_deepest_leaves,
    t1123_lowest_common_ancestor_of_deepest_leaves::parameters(kCases.size()),
    t1123_lowest_common_ancestor_of_deepest_leaves::name);
