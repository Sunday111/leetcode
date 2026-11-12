#include "1260.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::shiftGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,5,6],[7,8,9]]
1
[[9,1,2],[3,4,5],[6,7,8]]

[[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]]
4
[[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]

[[1,2,3],[4,5,6],[7,8,9]]
9
[[1,2,3],[4,5,6],[7,8,9]]
)");

class t1260 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1260, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1260,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
