#include "0973_k_closest_points_to_origin.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::kClosest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3],[-2,2]] 1 [[-2,2]]
)cases");

class t0973_k_closest_points_to_origin : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0973_k_closest_points_to_origin, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.kClosest(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0973_k_closest_points_to_origin,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
