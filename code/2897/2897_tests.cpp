#include "2897.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,5,8]           2  261
[4,5,4,7]           3  90
)");

class t2897 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2897, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2897,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
