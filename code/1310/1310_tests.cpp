#include "1310.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::xorQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,4,8]
[[0,1],[1,2],[0,3],[3,3]]
[2,7,14,8]

[4,8,2,10]
[[2,3],[1,3],[0,0],[0,3]]
[8,0,4,4]
)");

class t1310 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1310, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1310,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
