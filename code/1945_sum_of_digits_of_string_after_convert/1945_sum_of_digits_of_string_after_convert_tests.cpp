#include "1945_sum_of_digits_of_string_after_convert.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLucky;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"iiii" 1 36
)cases");

class t1945_sum_of_digits_of_string_after_convert
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1945_sum_of_digits_of_string_after_convert, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.getLucky(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1945_sum_of_digits_of_string_after_convert,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
