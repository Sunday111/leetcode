#pragma once

#include "0030.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findSubstring;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"barfoothefoobarman"
["foo","bar"]
[0,9]

"wordgoodgoodgoodbestword"
["word","good","best","word"]
[]

"barfoofoobarthefoobarman"
["bar","foo","the"]
[6,9,12]

"a"
["aa"]
[]

"ab"
["ab"]
[0]

"foobar"
["foo","bar","baz"]
[]

"aaaaaa"
["aa","aa"]
[0,1,2]

"barfoofoofoobar"
["bar","foo","foo"]
[0,6]

"barfooxxxfoobar"
["bar","foo"]
[0,9]

"barfooxbarfoo"
["bar","foo"]
[0,7]

"wordgoodgoodgoodbestword"
["word","good","best","good"]
[8]

"aaaaaaaa"
["aa","bb"]
[]

"bbbfoobbb"
["foo"]
[3]

"abbacaabc"
["a","b","c"]
[2,6]

"abcabcabc"
["a","b","c"]
[0,1,2,3,4,5,6]

"abcxabcabc"
["a","b","c"]
[0,4,5,6,7]

"ababa"
["a"]
[0,2,4]

)");
