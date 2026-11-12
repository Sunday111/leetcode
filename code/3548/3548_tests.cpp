#include <print>

#include "3548.hpp"
#include "gtest/gtest.h"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canPartitionGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[2,3]]
true

[[1,2],[3,4]]
true

[[1,2,4],[2,3,5]]
false

[[4,1,8],[3,2,6]]
false

[[1],[2],[1],[1],[1]]
true

[[1,2,1,1,1]]
true

[[1,1,1,2,1]]
true

[[73816],[71688]]
false

[[10,5,4,5]]
false

[[100000],[86218],[100000]]
true

[[5,5,6,2,2,2]]
true

[[25372],[100000],[100000]]
true

[[1,1],[2,1],[4,3]]
false

[[2190,608,1685],[22556,4932,16279],[1566,137,14025]]
true

[[2190,608,1685],[22556,4932,16279],[1566,137,14025]]
true
)");

class t3548 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3548, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);

    EXPECT_EQ(expected, actual);

    if (expected != actual)
    {
        std::println("Input matrix:");
        for (auto& row : std::get<0>(inputs))
        {
            std::print("    ");
            for (auto v : row)
            {
                std::print("{:4} ", v);
            }
            std::println("");
        }
    }
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3548,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
