#include "2130_test_cases.hpp"
#include "gtest/gtest.h"
#include "leet_code_list.hpp"

class t2130 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2130, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2130,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
