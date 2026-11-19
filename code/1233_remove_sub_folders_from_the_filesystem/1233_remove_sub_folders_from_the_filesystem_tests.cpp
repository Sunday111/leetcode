#include <algorithm>

#include "1233_remove_sub_folders_from_the_filesystem.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::removeSubfolders;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["/a","/a/b","/c/d","/c/d/e","/c/f"] ["/a","/c/d","/c/f"]

["/a","/a/b/c","/a/b/d"] ["/a"]

["/a/b/c","/a/b/ca","/a/b/d"] ["/a/b/c","/a/b/ca","/a/b/d"]

["/aa/ab/ac/ae","/aa/ab/af/ag","/ap/aq/ar/as","/ap/aq/ar","/ap/ax/ay/az","/ap","/ap/aq/ar/at","/aa/ab/af/ah","/aa/ai/aj/ak","/aa/ai/am/ao"]
["/aa/ab/ac/ae","/aa/ab/af/ag","/aa/ab/af/ah","/aa/ai/aj/ak","/aa/ai/am/ao","/ap"]
)cases");

class t1233_remove_sub_folders_from_the_filesystem
    : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1233_remove_sub_folders_from_the_filesystem, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.removeSubfolders(args...); },
        inputs);
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1233_remove_sub_folders_from_the_filesystem,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
