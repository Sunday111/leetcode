#pragma once

#include "1927.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumGame;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"5023"                                                                      false
"25??"                                                                      true
"?3295???"                                                                  false
"?6?6?000?3"                                                                true
"?0?3105????1834??7382?997?3?????7?63116?566?701?065?13?3??38?7?488?????9"  false
"??????"                                                                    false
"81??"                                                                      false
"0009??"                                                                    true
)");
