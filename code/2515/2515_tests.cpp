#include "2515.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::closestTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["hello","i","am","leetcode","hello"]
"hello"
1
1
["a","b","leetcode"]
"leetcode"
0
1
["i","eat","leetcode"]
"ate"
0
-1
)");

class t2515 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2515, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2515,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
