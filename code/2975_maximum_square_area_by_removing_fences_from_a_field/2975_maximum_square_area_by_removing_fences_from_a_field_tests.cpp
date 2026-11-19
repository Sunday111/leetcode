#include "2975_maximum_square_area_by_removing_fences_from_a_field.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<unsigned int, unsigned int, std::vector<int>, std::vector<int>>,
    int>(R"cases(
4 3 [2,3] [2] 4
)cases");

class t2975_maximum_square_area_by_removing_fences_from_a_field
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t2975_maximum_square_area_by_removing_fences_from_a_field, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.maximizeSquareArea(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2975_maximum_square_area_by_removing_fences_from_a_field,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
