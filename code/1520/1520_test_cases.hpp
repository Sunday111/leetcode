#pragma once

#include "1520.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumOfSubstrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bdacdcba"                     ["bdacdcba"]
"a"                            ["a"]
"aaaa"                         ["aaaa"]
"abc"                          ["a","b","c"]
"abcdefghijklmnopqrstuvwxyz"   ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]
"aabbcc"                       ["aa","bb","cc"]
"ababcdcd"                     ["abab","cdcd"]
"abbaccd"                      ["bb","cc","d"]
"adefaddaccc"                  ["e","f","ccc"]
"ababa"                        ["ababa"]
"abcaca"                       ["b"]
"aba"                          ["b"]
"abba"                         ["bb"]
"abcbac"                       ["abcbac"]
"abcbca"                       ["bcbc"]
"abcabca"                      ["abcabca"]
"abcacba"                      ["abcacba"]
"abca"                         ["b","c"]
"bcaba"                        ["c"]
"acbaba"                       ["c"]
"abcaba"                       ["c"]
)");
