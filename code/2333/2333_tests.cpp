#include "2333.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSumSquareDiff;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

[1,4,10,12]
[5,8,6,9]
1
1
43

[1,2,3,4]
[2,10,20,19]
0
0
579
)");

class t2333 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2333, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2333,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
