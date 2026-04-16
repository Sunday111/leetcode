#pragma once

#include "3761.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minMirrorPairDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[12,21,45,33,54]
1

[120,21]
1

[21,120]
-1


)");
