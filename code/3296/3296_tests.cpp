#include "3296.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minNumberOfSeconds;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[2,1,1]
3

10
[3,2,2,4]
12

5
[1]
15

8
[1,1]
10

1
[5]
5

)");

class t3296 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3296, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3296,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
