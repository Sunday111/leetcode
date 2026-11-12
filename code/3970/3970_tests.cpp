#include "3970.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::shortestPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
1
3

3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
2
2

3
[[0,1,1],[1,2,1]]
"aaa"
2
-1


)");

class t3970 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3970, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3970,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
