#include "2904.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::shortestBeautifulSubstring;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"1100100101011001001" 7 "1100100101011"
"100011001" 3 "11001"
"1011" 2 "11"
"000" 1 ""
"1100001110111100100" 8 "11101111001"
"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111" 100 "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"111111111111111111110000010101010101010101010101000000000011111111111111111111111111111111111" 50 "1110000010101010101010101010101000000000011111111111111111111111111111111111"
"111111110010001010" 11 "11111111001000101"
"001" 1 "1"
)");

class t2904 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2904, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2904,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
