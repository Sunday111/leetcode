#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::string>(R"cases(
"1b,2n,3b,4n,5n" "1b,2n,3b,4n,5n"
"" ""
"1b,2n,-13b,4n,5n" "1b,2n,-13b,4n,5n"
"1l,2n" "1l,2n"
"1n" "1n"
)cases");

using t0297_srialize_and_desrialize_binary_tree = SolutionTests<Codec>;
TEST_P(t0297_srialize_and_desrialize_binary_tree, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto* tree = solution.deserialize(std::get<0>(inputs));
            auto actual = solution.serialize(tree);
            DeleteBinaryTree(tree);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0297_srialize_and_desrialize_binary_tree,
    t0297_srialize_and_desrialize_binary_tree::parameters(kCases.size()),
    t0297_srialize_and_desrialize_binary_tree::name);
