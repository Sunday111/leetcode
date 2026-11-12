#include "3532.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pathExistenceQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
[1,3]
1
[[0,0],[0,1]]
[true,false]

4
[2,5,6,8]
2
[[0,1],[0,2],[1,3],[2,3]]
[false,false,true,true]


)");

class t3532 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3532, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3532,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
