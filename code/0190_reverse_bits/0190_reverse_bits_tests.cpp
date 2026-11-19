#include "0190_reverse_bits.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<u32>, u32>(R"cases(
43261596 964176192
)cases");

class t0190_reverse_bits : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0190_reverse_bits, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    ASSERT_EQ(expected, Solution{}.reverseBits(std::get<0>(inputs)));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0190_reverse_bits,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
