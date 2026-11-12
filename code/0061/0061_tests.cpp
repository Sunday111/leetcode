#include "0061.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[1,2,3,4,5]
2
[4,5,1,2,3]

[0,1,2]
4
[2,0,1]
)");

class t0061 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0061, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    auto& [vals, k] = inputs;
    auto in_list = LeetCodeList<ListNode>::FromArray(std::span{vals});
    auto expected_list = LeetCodeList<ListNode>::FromArray(std::span{expected});
    auto out = Solution{}.rotateRight(in_list.head, k);
    ASSERT_TRUE(CompareLists(expected_list.head, out));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0061,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
