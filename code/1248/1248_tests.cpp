#include "1248.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,2,1,1]
3
2
[2,4,6]
1
0
[2,2,2,1,2,2,1,2,2,2]
2
16
)");

class t1248 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1248, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1248,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
