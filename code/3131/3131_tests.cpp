#include "3131.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::addedInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,4]
[9,7,5]
3

[10]
[5]
-5

[1,1,1,1]
[1,1,1,1]
0


)");

class t3131 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3131, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3131,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
