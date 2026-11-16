#include "3041_test_cases.hpp"
#include "gtest/gtest.h"

class t3041 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3041, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3041,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
