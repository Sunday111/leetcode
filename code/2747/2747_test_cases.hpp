#pragma once

#include <tuple>
#include <utility>
#include <vector>

#include "2747.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countServers;
inline static const auto kCases = []
{
    auto cases = parse_test_cases<kMethodToTest>(R"(
3
[[1,3],[2,6],[1,5]]
5
[10,11]
[1,2]

3
[[1,1],[2,2],[3,3]]
1
[3,2]
[1,1]

4
[[1,4],[2,7],[3,3],[4,8]]
3
[7,4,8,12]
[2,2,2,4]

3
[[2,6],[1,5],[1,5],[1,4],[2,6]]
2
[8,6,7,5,8,9]
[2,1,1,2,2,3]

1
[[1,1]]
1
[2,3]
[0,1]

2
[[1,10]]
1
[2,9,10,11,12]
[2,2,1,1,2]

5
[[1,50],[2,50],[5,50],[1,50]]
10
[61,50,60,49,50]
[5,2,2,5,2]

100000
[[100000,1000000],[1,900000],[99999,999999]]
100000
[1000000,999999,100001]
[99997,99998,100000]

3
[[1,7],[1,1],[1,4]]
2
[3,4,6,7,9,10]
[2,2,2,2,2,3]

4
[[4,20],[2,5],[1,10],[2,10]]
5
[25,6,15,11,25]
[3,3,2,2,3]

)");

    cases.emplace_back(
        std::tuple{
            100'000u,
            std::vector<std::vector<int>>(100'000, {100'000, 500'000}),
            100'000u,
            std::vector<int>{500'000, 600'000, 600'001}},
        std::vector<int>{99'999, 99'999, 100'000});

    std::vector<std::vector<int>> logs(100'000);
    std::vector<int> queries(100'000);
    std::vector<int> expected(100'000);
    for (u32 i = 0; i != 100'000; ++i)
    {
        logs.at(i) = {static_cast<int>(100'000 - i), 1'000'000};
        const bool at_request = (i % 2) == 0;
        queries.at(i) = 999'999 + at_request;
        expected.at(i) = 100'000 * !at_request;
    }
    cases.emplace_back(
        std::tuple{100'000u, std::move(logs), 1u, std::move(queries)},
        std::move(expected));
    cases.emplace_back(
        std::tuple{
            1u,
            std::vector<std::vector<int>>{{1, 2}},
            1u,
            std::vector<int>{2, 4}},
        std::vector<int>{0, 1});
    return cases;
}();
