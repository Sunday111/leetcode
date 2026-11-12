#include "0033.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::search;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,5,6,7,0,1,2]
0
4

[4,5,6,7,0,1,2]
3
-1

[1]
0
-1
)");

class t0033 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0033, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0033,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
