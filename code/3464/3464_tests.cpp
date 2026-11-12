#include "3464.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
[[0,0],[1,2],[2,0],[2,2],[2,1]]
4
1

2
[[0,2],[2,0],[2,2],[0,0]]
4
2

1000000000
[[0,1000000000],[1000000000,0],[1000000000,1000000000],[0,0]]
4
1000000000



2
[[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]]
5
1


)");

class t3464 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3464, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3464,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
