#include "aoc_2025_9.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<u32>>>,
    std::tuple<u64, u64>>(R"cases(
[[7,1],[11,1],[11,7],[9,7],[9,5],[2,5],[2,3],[7,3]] 50 24
)cases");

class taoc_2025_9 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_9, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    std::vector<Vec2<u32>> points;
    for (auto& point : std::get<0>(inputs))
        points.push_back({point[0], point[1]});
    auto [part1, part2] = expected;
    ASSERT_EQ(part1, Solution1{}.solve(points));
    ASSERT_EQ(part2, Solution2{}.solve(points));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_9,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
