#include "3583_count_special_triplets.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::specialTriplets;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[6,3,6] 1

[0,1,0,0] 1
)cases");

class t3583_count_special_triplets : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3583_count_special_triplets, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.specialTriplets(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3583_count_special_triplets,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
