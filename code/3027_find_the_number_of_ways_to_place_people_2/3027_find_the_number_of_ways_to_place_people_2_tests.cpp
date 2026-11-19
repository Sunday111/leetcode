#include "3027_find_the_number_of_ways_to_place_people_2.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[2,5],[128653,-2370425]] 1
)cases");

class t3027_find_the_number_of_ways_to_place_people_2
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3027_find_the_number_of_ways_to_place_people_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numberOfPairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3027_find_the_number_of_ways_to_place_people_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
