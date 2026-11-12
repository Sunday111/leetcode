#include "0835.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestOverlap;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,1,0],[0,1,0],[0,1,0]]
[[0,0,0],[0,1,1],[0,0,1]]
3
[[1]]
[[1]]
1
[[0]]
[[0]]
0
[[1,0,0,0],[0,0,0,0],[0,0,1,0],[0,0,0,0]]
[[0,0,0,0],[0,1,0,0],[0,0,0,0],[0,0,0,1]]
2
[[0,0,0,0],[0,0,0,0],[1,1,1,0],[0,0,0,0]]
[[0,1,1,1],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
3
)");

class t0835 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0835, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0835,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
