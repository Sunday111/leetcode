#include "aoc_2025_11_1.hpp"
#include "aoc_2025_11_2.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string, std::string>,
    std::tuple<u64, u64>>(R"cases(
"
aaa: you hhh
you: bbb ccc
bbb: ddd eee
ccc: ddd eee fff
ddd: ggg
eee: out
fff: out
ggg: out
hhh: ccc fff iii
iii: out
" "
svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
" 5 2
)cases");

class taoc_2025_11 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_11, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [first, second] = inputs;
    ASSERT_EQ(std::get<1>(expected), part2::Solution{}.solve(second));
}
TEST_P(taoc_2025_11, DISABLED_Part1)
{
    auto [inputs, expected] = kCases.at(GetParam());
    ASSERT_EQ(
        std::get<0>(expected),
        part1::Solution{}.solve(std::get<0>(inputs)));
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_11,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
