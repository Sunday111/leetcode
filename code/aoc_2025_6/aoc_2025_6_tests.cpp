#include "aoc_2025_6.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::string>,
    std::tuple<uint64_t, uint64_t>>(
    "\n"
    "\"\n"
    "123 328  51 64 \n"
    " 45 64  387 23 \n"
    "  6 98  215 314\n"
    "*   +   *   +\n"
    "\" 4277556 3263827\n");

class taoc_2025_6 : public ::testing::TestWithParam<size_t>
{
};
TEST_P(taoc_2025_6, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [data] = inputs;
    auto [part1, part2] = expected;
    ASSERT_EQ(part1, Solution1{}.solve(data));
    ASSERT_EQ(part2, Solution2{}.solve(data));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    taoc_2025_6,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
