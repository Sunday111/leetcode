#include "1855.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[55,30,5,4,2]
[100,20,10,10,5]
2

[2,2,2]
[10,10,1]
1

[30,29,19,5]
[25,25,25,25,25]
2
)");

class t1855 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1855, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1855,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
