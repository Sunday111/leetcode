#include "1477.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSumOfLengths;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,2,2,4,3]
3
2
[7,3,4,7]
7
2
[4,3,2,6,2,3,4]
6
-1
)");

class t1477 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1477, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1477,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
