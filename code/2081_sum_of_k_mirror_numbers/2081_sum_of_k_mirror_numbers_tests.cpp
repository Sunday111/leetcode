#include "2081_sum_of_k_mirror_numbers.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<uint8_t, uint8_t>, uint64_t>(R"cases(
2 5 25
3 7 499
7 17 20379000
)cases");

class t2081_sum_of_k_mirror_numbers : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t2081_sum_of_k_mirror_numbers, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto [k, n] = inputs;
    ASSERT_EQ(expected, Solution{}.kMirror(k, n));
    ASSERT_EQ(expected, Cheat::kMirror(k, n));
#ifndef NDEBUG
    ASSERT_EQ(expected, Solution2{}.kMirror(k, n));
    ASSERT_EQ(expected, Solution3{}.kMirror(k, n));
    ASSERT_EQ(expected, Solution4{}.kMirror(k, n));
#endif
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2081_sum_of_k_mirror_numbers,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
