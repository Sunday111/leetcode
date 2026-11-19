#include "0065_valid_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"32.e-80123" true
)cases");

class t0065_valid_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0065_valid_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.isNumber(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0065_valid_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
