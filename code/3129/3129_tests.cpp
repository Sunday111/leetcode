#include "3129.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfStableArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
1
2
2

1
2
1
1

3
3
2
14

39
20
18
207227572


)");

class t3129 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3129, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3129,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
