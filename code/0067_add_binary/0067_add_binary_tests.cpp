#include "0067_add_binary.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::addBinary;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"11" "1" "100"

"1010" "1011" "10101"
)cases");

class t0067_add_binary : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0067_add_binary, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.addBinary(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0067_add_binary,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
