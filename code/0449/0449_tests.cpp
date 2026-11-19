#include "0449.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::string>(R"cases(
"2b,1n,3n" "2b,1n,3n"
"" ""
)cases");

using t0449 = SolutionTests<Codec>;
TEST_P(t0449, Test)
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
    t0449,
    t0449::parameters(kCases.size()),
    t0449::name);
