#include <algorithm>

#include "1948_delete_duplicate_folders_in_system.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<std::string>>>,
    std::vector<std::vector<std::string>>>(R"cases(
[["a"],["c"],["d"],["a","b"],["c","b"],["d","a"]] [["d"],["d","a"]]
[["a"],["c"],["a","b"],["c","b"],["a","b","x"],["a","b","x","y"],["w"],["w","y"]] [["a"],["a","b"],["c"],["c","b"]]
)cases");

class t1948_delete_duplicate_folders_in_system
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t1948_delete_duplicate_folders_in_system, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = Solution{}.deleteDuplicateFolder(std::get<0>(inputs));
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1948_delete_duplicate_folders_in_system,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
