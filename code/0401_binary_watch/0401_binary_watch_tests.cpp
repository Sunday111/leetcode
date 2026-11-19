#include "0401_binary_watch.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::readBinaryWatch;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
)cases");

class t0401_binary_watch : public ::testing::TestWithParam<size_t>
{
};

TEST_P(t0401_binary_watch, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto actual = std::apply(
        [](auto&... args) { return Solution{}.readBinaryWatch(args...); },
        inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0401_binary_watch,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
