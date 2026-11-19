#include "0043_multiply_strings.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::string>(R"cases(
"0" "1009" "0"
"2" "3" "6"
"123" "456" "56088"
"99" "99" "9801"
)cases");

class t0043_multiply_strings : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0043_multiply_strings, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [a, b] = inputs;
    ASSERT_EQ(expected, Solution{}.multiply(a, b));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0043_multiply_strings,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
