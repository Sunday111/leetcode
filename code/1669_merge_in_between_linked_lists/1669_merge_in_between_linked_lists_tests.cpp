#include "1669_merge_in_between_linked_lists.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::mergeInBetween;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,1,13,6,9,5] 3 4 [1000000,1000001,1000002] [10,1,13,1000000,1000001,1000002,5]

[0,1,2,3,4,5,6] 2 5 [1000000,1000001,1000002,1000003,1000004] [0,1,1000000,1000001,1000002,1000003,1000004,6]
)cases");

class t1669_merge_in_between_linked_lists
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1669_merge_in_between_linked_lists, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.mergeInBetween(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1669_merge_in_between_linked_lists,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
