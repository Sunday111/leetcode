#pragma once

#include <string>

#include "3212.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubmatrices;
inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<std::vector<std::string>>>,
    u32>(R"(
[["X","Y","."],["Y",".","."]]
3

[["X","X"],["X","Y"]]
0

[[".","."],[".","."]]
0


)");
