#include "0115.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numDistinct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"rabbbit"   "rabbit"  3
"babgbag"   "bag"     5
)");

class t0115 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0115, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0115,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
