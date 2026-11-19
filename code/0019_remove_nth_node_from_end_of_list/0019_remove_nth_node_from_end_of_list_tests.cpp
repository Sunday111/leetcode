#include <cassert>

#include "0019_remove_nth_node_from_end_of_list.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeNthFromEnd;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4,5] 2 [1,2,3,5]
)");

class t0019_remove_nth_node_from_end_of_list
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0019_remove_nth_node_from_end_of_list, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.removeNthFromEnd(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0019_remove_nth_node_from_end_of_list,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
