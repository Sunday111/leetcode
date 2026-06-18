#include "1093_test_cases.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

class t1093 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1093, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    EXPECT_THAT(
        expected,
        testing::Pointwise(testing::DoubleNear(0.0001), actual));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1093,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
