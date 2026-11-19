#include "0024_swap_nodes_in_pairs.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::swapPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4] [2,1,4,3]
)");

class t0024_swap_nodes_in_pairs : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0024_swap_nodes_in_pairs, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.swapPairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0024_swap_nodes_in_pairs,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
