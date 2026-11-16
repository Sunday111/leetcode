#pragma once

#include "3041.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSelectedElements;
inline static const auto kCases = []
{
    auto cases = parse_test_cases<kMethodToTest>(R"(
[1,3]      2
[1,4,7,10]  1
[1,2,2]    3
[2,1,5,1,1] 3
[1] 1
[1000000] 1
[1,1,1,1] 2
[1000000,1000000] 2
[1,1,3,3,5,5] 6
[1,2,4] 3
[63,64,65,65,66] 5
)");
    for (int n : {128, 129, 32767, 32768})
    {
        std::vector<int> values;
        values.reserve(cast<u32>(n));
        for (int i = 0; i < n; ++i) values.push_back(1 + 3 * i);
        cases.emplace_back(std::tuple{std::move(values)}, 1u);
    }
    std::vector<int> consecutive;
    consecutive.reserve(100'000);
    for (int i = 0; i < 100'000; ++i) consecutive.push_back(900'001 + i);
    cases.emplace_back(std::tuple{std::move(consecutive)}, 100'000u);
    cases.emplace_back(std::tuple{std::vector<int>(100'000, 1'000'000)}, 2u);
    return cases;
}();
