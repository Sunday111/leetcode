#include "1758_minimum_changes_to_make_alternating_binary_stringtest_cases.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases<kMethodToTest>(kTestCases);

class t1758_minimum_changes_to_make_alternating_binary_string
    : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1758_minimum_changes_to_make_alternating_binary_string, MinOperations)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1758_minimum_changes_to_make_alternating_binary_string,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
