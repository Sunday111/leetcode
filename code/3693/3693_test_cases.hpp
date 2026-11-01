#pragma once

#include <tuple>
#include <vector>

#include "3693.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::climbStairs;
inline static const auto kCases = []
{
    auto cases = parse_test_cases<kMethodToTest>(R"(
4
[1,2,3,4]
13

4
[5,1,6,2]
11

3
[9,8,3]
12

1
[1]
2

1
[10000]
10001

2
[1,10000]
10003

2
[10000,1]
5

5
[1,10000,1,10000,1]
12

6
[10000,10000,10000,10000,10000,10000]
20018

7
[10000,10000,10000,10000,10000,10000,10000]
30017

8
[10000,10000,10000,10000,10000,10000,10000,10000]
30022
)");
    cases.emplace_back(
        std::tuple{100'000u, std::vector<int>(100'000, 1)},
        200'000u);
    cases.emplace_back(
        std::tuple{100'000u, std::vector<int>(100'000, 10'000)},
        333'639'996u);
    return cases;
}();
