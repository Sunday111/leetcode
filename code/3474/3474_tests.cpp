#include "3474.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::generateString;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"TFTF"
"ab"
"ababa"

"TFTF"
"abc"
""

"F"
"d"
"a"

"FT"
"wvxyy"
"awvxyy"

"TTFFT"
"fff"
""

"FFFF"
"ddb"
"aaaaaa"

"FFTFFF"
"a"
"bbabbb"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"
)");

class t3474 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3474, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3474,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
