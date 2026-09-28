#include "0241_test_cases.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

class t0241 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0241, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    std::ranges::sort(actual);
    std::ranges::sort(expected);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0241,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
