#include "0297_srialize_and_desrialize_binary_tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::string>(R"cases(
"1b,2n,3b,4n,5n" "1b,2n,3b,4n,5n"
"" ""
"1b,2n,-13b,4n,5n" "1b,2n,-13b,4n,5n"
"1l,2n" "1l,2n"
"1n" "1n"
)cases");

class t0297_srialize_and_desrialize_binary_tree
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0297_srialize_and_desrialize_binary_tree, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto* tree = Codec::deserialize(std::get<0>(inputs));
    auto actual = Codec::serialize(tree);
    DeleteBinaryTree(tree);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0297_srialize_and_desrialize_binary_tree,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
