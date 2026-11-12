#include "0399.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::calcEquation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[["a","b"],["b","c"]]
[2.0,3.0]
[["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
[6.00000,0.50000,-1.00000,1.00000,-1.00000]

[["a","b"],["b","c"],["bc","cd"]]
[1.5,2.5,5.0]
[["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
[3.75000,0.40000,5.00000,0.20000]

[["a","b"]]
[0.5]
[["a","b"],["b","a"],["a","c"],["x","y"]]
[0.50000,2.00000,-1.00000,-1.00000]
)");

class t0399 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0399, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0399,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
