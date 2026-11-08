#pragma once

#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "1606.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::busiestServers;
inline static const auto kCases = []
{
    auto cases = parse_test_cases<kMethodToTest>(R"(
3
[1,2,3,4,5]
[5,2,3,3,3]
[1]

3
[1,2,3,4]
[1,2,1,2]
[0]

3
[1,2,3]
[10,12,11]
[0,1,2]

1
[1]
[1]
[0]

1
[1,2,3,4]
[1,1,1,1]
[0]

1
[1,2,3,4,5]
[3,1,1,1,1]
[0]

5
[1,2]
[10,10]
[0,1]

3
[1,2,3,4,5,6]
[3,10,10,10,10,10]
[0]

3
[1,2,3,4,5]
[10,10,1,10,1]
[2]

3
[1,2,3,10,11,12]
[9,8,7,1,1,1]
[0,1,2]

3
[1,2,3,4,5,6]
[100,2,100,1,1,1]
[1]

2
[1,2,3,100,101]
[99,99,1,1,1]
[0]

2
[1,999999999,1000000000]
[1000000000,1,1000000000]
[1]

4
[1,2,3,4,5,6,7,8]
[1,1,1,1,1,1,1,1]
[0,1,2,3]

2
[1,2,3,4]
[1000000000,1000000000,1,1]
[0,1]
)");

    for (u32 k : {63u, 64u, 65u, 4095u, 4096u, 4097u, 99'998u})
    {
        std::vector<int> arrival(k + 2);
        std::iota(arrival.begin(), arrival.end(), 1);
        std::vector<int> load(k + 2, 1'000'000'000);
        load.at(k - 1) = 1;
        load.at(k) = 1;
        load.at(k + 1) = 1;
        cases.emplace_back(
            std::tuple{k, std::move(arrival), std::move(load)},
            std::vector<int>{static_cast<int>(k - 1)});
    }

    std::vector<int> arrival(100'000);
    std::iota(arrival.begin(), arrival.end(), 1);
    std::vector<int> load(100'000, 1);
    cases.emplace_back(std::tuple{1u, arrival, load}, std::vector<int>{0});
    for (u32 i = 0; i != 99'999; ++i)
    {
        load.at(i) = static_cast<int>(99'999 - i);
    }
    cases.emplace_back(std::tuple{99'999u, arrival, load}, std::vector<int>{0});
    std::vector<int> expected(100'000);
    std::iota(expected.begin(), expected.end(), 0);
    cases.emplace_back(
        std::tuple{100'000u, std::move(arrival), std::move(load)},
        std::move(expected));
    return cases;
}();
