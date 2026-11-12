#include "0986.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::intervalIntersection;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,2],[5,10],[13,23],[24,25]]
[[1,5],[8,12],[15,24],[25,26]]
[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]

[[1,3],[5,9]]
[]
[]

[[0,2],[4,6],[8,12]]
[[1,10]]
[[1,2],[4,6],[8,10]]

[[0,2]]
[[1,3]]
[[1,2]]

[[0,10]]
[[1,2],[4,5]]
[[1,2],[4,5]]

[[0,1]]
[[2,3]]
[]

[]
[[1,2]]
[]
)");

class t0986 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0986, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0986,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
