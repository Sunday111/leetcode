#include "3025_find_the_number_of_ways_to_place_people_1.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,0],[0,3]] 1

[[1,1],[2,2],[3,3]] 0

[[3,1],[1,3],[1,1]] 2
)cases");

class t3025_find_the_number_of_ways_to_place_people_1
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t3025_find_the_number_of_ways_to_place_people_1, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.numberOfPairs(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3025_find_the_number_of_ways_to_place_people_1,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
