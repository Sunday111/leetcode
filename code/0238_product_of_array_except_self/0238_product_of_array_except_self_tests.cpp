#include "0238_product_of_array_except_self.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::productExceptSelf;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4] [24,12,8,6]
)cases");

class t0238_product_of_array_except_self
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0238_product_of_array_except_self, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.productExceptSelf(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0238_product_of_array_except_self,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
