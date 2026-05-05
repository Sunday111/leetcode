#pragma once

#include "1861.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotateTheBox;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
    [["#",".","#"]]
    [["."],["#"],["#"]]

    [["#",".","*","."],["#","#","*","."]]
    [["#","."],
     ["#","#"],
     ["*","*"],
     [".","."]]

    [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]]
    [[".","#","#"],
     [".","#","#"],
     ["#","#","*"],
     ["#","*","."],
     ["#",".","*"],
     ["#",".","."]]
)");
