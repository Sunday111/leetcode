#include "1284.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minFlips;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0],[1],[1]]       1
[[0,1,1]]           1
[[0,0],[0,1]]       3
[[0]]               0
[[1,0,0],[1,0,0]]   -1
)");

class t1284 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1284, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1284,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
