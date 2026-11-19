#include "aoc_2025_10_1.hpp"
#include "aoc_2025_10_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::tuple<u32, u32>>(
        R"cases(
"
[.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
[...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
[.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
" 7 33
)cases");

class taoc_2025_10 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_10, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [data] = inputs;
    auto [first, second] = expected;
    ASSERT_EQ(first, part1::Solution{}.solve(data));
    ASSERT_EQ(second, part2::Solution{}.solve(data));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_10,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
