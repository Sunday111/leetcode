#include "2196_create_binary_tree_from_descriptionstest_cases.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

using t2196_create_binary_tree_from_descriptions = SolutionTests<Solution>;

TEST_P(t2196_create_binary_tree_from_descriptions, MinOperations)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto node = solution.createBinaryTree(std::get<0>(inputs));
            ASSERT_TRUE(CompareBinaryTrees(expected.root, node));
        });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2196_create_binary_tree_from_descriptions,
    t2196_create_binary_tree_from_descriptions::parameters(kCases.size()),
    t2196_create_binary_tree_from_descriptions::name);
