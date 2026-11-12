#include "3499.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::maxActiveSectionsAfterTrade;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"01"
1

"0100"
4

"1000100"
7

"01010"
4


)");

class t3499 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3499, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3499,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
