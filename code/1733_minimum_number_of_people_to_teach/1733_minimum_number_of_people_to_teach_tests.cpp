#include "1733_minimum_number_of_people_to_teach.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumTeachings;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[2],[1,3],[1,2],[3]] [[1,4],[1,2],[3,4],[2,3]] 2
)cases");

class t1733_minimum_number_of_people_to_teach
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1733_minimum_number_of_people_to_teach, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.minimumTeachings(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1733_minimum_number_of_people_to_teach,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
