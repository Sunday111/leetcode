#include "aoc_2025_8.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<int>>, u32>,
    std::tuple<u32, u64>>(R"cases(
[[162, 817, 812], [57, 618, 57], [906, 360, 560], [592, 479, 940], [352, 342, 300], [466, 668, 158], [542, 29, 236], [431, 825, 988], [739, 650, 466], [52, 470, 668], [216, 146, 977], [819, 987, 18], [117, 168, 530], [805, 96, 715], [346, 949, 466], [970, 615, 88], [941, 993, 340], [862, 61, 35], [984, 92, 344], [425, 690, 689]] 10 40 25272
)cases");

class taoc_2025_8 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_8, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [coordinates, passes] = inputs;
    std::vector<Vec3> points;
    for (auto& point : coordinates)
        points.push_back({point[0], point[1], point[2]});
    auto [part1, part2] = expected;
    ASSERT_EQ(part1, Solution1{}.solve(points, passes));
    ASSERT_EQ(part2, Solution2{}.solve(points));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_8,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
