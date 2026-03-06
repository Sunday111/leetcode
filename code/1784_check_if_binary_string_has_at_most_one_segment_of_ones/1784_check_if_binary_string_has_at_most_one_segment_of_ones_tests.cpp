#include "1784_check_if_binary_string_has_at_most_one_segment_of_onestest_cases.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

class t1784_check_if_binary_string_has_at_most_one_segment_of_ones
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones,
    MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1784_check_if_binary_string_has_at_most_one_segment_of_ones,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
