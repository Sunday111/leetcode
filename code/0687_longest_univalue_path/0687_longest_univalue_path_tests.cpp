#include "0687_longest_univalue_path.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestUnivaluePath;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,4,5,1,1,null,5] 2

[1,null,1,1,1,1,1,1] 4
)cases");

class t0687_longest_univalue_path : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0687_longest_univalue_path, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.longestUnivaluePath(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0687_longest_univalue_path,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
