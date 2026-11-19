#include "0611_valid_triangle_number.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::triangleNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,2,3,4] 3

[1,1,3,4] 0

[0,2,2] 0

[2,3,4,4] 4
)cases");

class t0611_valid_triangle_number : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0611_valid_triangle_number, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.triangleNumber(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0611_valid_triangle_number,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
