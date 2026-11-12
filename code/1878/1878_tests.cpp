#include "1878.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getBiggestThree;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[20,17, 9,13, 5, 2, 9, 1, 5],
 [14, 9, 9, 9,16,18, 3, 4,12],
 [18,15,10,20,19,20,15,12,11],
 [19,16,19,18, 8,13,15,14,11],
 [ 4,19, 5, 2,19,17, 7, 2, 2]
]
[107,103,102]


[[ 3, 4,  5, 1, 3],
 [ 3, 3,  4, 2, 3],
 [20,30,200,40,10],
 [ 1, 5,  5, 4, 1],
 [ 4, 3,  2, 2, 5]
]
[228,216,211]

[[1,2,3],[4,5,6],[7,8,9]]
[20,9,8]

[[7,7,7]]
[7]



)");

class t1878 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t1878, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1878,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
