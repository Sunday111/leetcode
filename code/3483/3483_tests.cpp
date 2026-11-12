#include "3483.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::totalNumbers;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4]
12

[0,2,2]
2

[6,6,6]
1

[1,3,5]
0


)");

class t3483 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3483, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3483,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
