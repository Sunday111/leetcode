#pragma once

#include "1320.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"CAKE" 3
"HAPPY" 6
"OPVUWZLCKTDPSUKGHAXIDWHLZFKNBDZEWHBSURTVCADUGTSDMCLDBTAGFWDPGXZBVARNTDICHCUJLNFBQOBTDWMGILXPSFWVGYBZVFFKQIDTOVFAPVNSQJULMVIERWAOXCKXBRI" 295
)");
