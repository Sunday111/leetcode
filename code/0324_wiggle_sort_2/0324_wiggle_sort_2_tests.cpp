#include "0324_wiggle_sort_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::vector<int>>, std::vector<int>>(
        R"cases(
[1,5,1,1,6,4] [1,6,1,5,1,4]

[1,3,2,2,3,1] [2,3,1,3,1,2]
)cases");

class t0324_wiggle_sort_2 : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0324_wiggle_sort_2, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    std::apply(
        [](auto&... args) { return Solution{}.wiggleSort(args...); },
        inputs);
    auto& actual = std::get<0>(inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0324_wiggle_sort_2,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
