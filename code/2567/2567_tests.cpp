#include "2567.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimizeSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,4,7,8,5]
3

[1,4,3]
0

[7,7,7]
0

[1,1,1,1,1]
0

[1,2,100,101,102]
2

[1,2,3,100,101]
2

[1,50,51,52,100]
2

[100,52,51,50,1]
2

[1,1,2,2,100]
1

[1,1000000000,1000000000]
0

[1,1,1,1000000000,1000000000,1000000000]
999999999

[4,1,3,2]
1

[9,1,9,9,1,9]
0


)");

class t2567 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t2567, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2567,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
