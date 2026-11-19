#include "0449_serialize_and_desrialize_bst.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::string>(R"cases(
"2b,1n,3n" "2b,1n,3n"
"" ""
)cases");

class t0449_serialize_and_desrialize_bst
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0449_serialize_and_desrialize_bst, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto* tree = Codec::deserialize(std::get<0>(inputs));
    auto actual = Codec::serialize(tree);
    DeleteBinaryTree(tree);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0449_serialize_and_desrialize_bst,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
