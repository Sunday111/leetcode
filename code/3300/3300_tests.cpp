#include "3300.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minElement;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,12,13,14]
1

[1,2,3,4]
1

[999,19,199]
10


)");

class t3300 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3300, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3300,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
