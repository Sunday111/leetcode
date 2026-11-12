#include "1340.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[6,4,14,6,8,13,9,7,10,6,12]
2
4
[3,3,3,3,3]
3
1
[7,6,5,4,3,2,1]
1
7
)");

class t1340 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1340, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1340,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
