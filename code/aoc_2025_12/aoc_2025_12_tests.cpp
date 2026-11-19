#include "aoc_2025_12_1.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::string>, std::vector<std::vector<u8>>>,
    u32>(R"cases(
["#########","#########","#########","#########","#########","#########"]
[[3,3,1,0,0,0,0,0],[3,3,2,0,0,0,0,0],[6,3,1,1,0,0,0,0]] 2
)cases");

class taoc_2025_12 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_12, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [patterns, counts] = inputs;
    ASSERT_EQ(patterns.size(), 6);
    std::array<Figure, 6> figures{
        patterns[0].c_str(),
        patterns[1].c_str(),
        patterns[2].c_str(),
        patterns[3].c_str(),
        patterns[4].c_str(),
        patterns[5].c_str()};
    std::vector<Request> requests;
    for (auto& count : counts)
    {
        ASSERT_EQ(count.size(), 8);
        std::ranges::copy(count, requests.emplace_back().begin());
    }
    ASSERT_EQ(expected, part1::Solution{}.solve(figures, requests));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_12,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
