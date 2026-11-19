#include "1461_check_if_a_string_contains_all_binary_codes_of_size_k.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::hasAllCodes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"00110110" 2 true

"0110" 1 true

"0110" 2 false

"00110" 2 true
)cases");

class t1461_check_if_a_string_contains_all_binary_codes_of_size_k
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1461_check_if_a_string_contains_all_binary_codes_of_size_k, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.hasAllCodes(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1461_check_if_a_string_contains_all_binary_codes_of_size_k,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
