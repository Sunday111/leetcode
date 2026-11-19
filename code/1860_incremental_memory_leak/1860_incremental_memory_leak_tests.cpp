#include "1860_incremental_memory_leak.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::memLeak;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
8 11 [6,0,4]

2 2 [3,1,0]

2147483647 2147483647 [92681,88047,41707]
)cases");

class t1860_incremental_memory_leak : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t1860_incremental_memory_leak, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.memLeak(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1860_incremental_memory_leak,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
