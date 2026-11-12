#include <algorithm>
#include <numeric>

#include "0030.hpp"
#include "gtest/gtest.h"
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

class t0030 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0030, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0030,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

TEST(t0030Boundaries, MaximumRepeatedWords)
{
    std::string s(10'000, 'a');
    std::vector<std::string> words(5000, "a");
    std::vector<int> expected(5001);
    std::iota(expected.begin(), expected.end(), 0);
    Solution instance;
    ASSERT_EQ(expected, instance.findSubstring(s, words));
}

TEST(t0030Boundaries, ManyResets)
{
    std::string s(9999, 'b');
    s += 'a';
    std::vector<std::string> words{"a"};
    Solution instance;
    ASSERT_EQ(std::vector<int>{9999}, instance.findSubstring(s, words));
}

TEST(t0030Boundaries, WordLengthSpecialisations)
{
    for (size_t length : {1u, 2u, 3u, 4u, 8u, 12u, 13u, 30u})
    {
        SCOPED_TRACE(length);
        std::string first(length, 'a');
        auto second = first;
        second.back() = 'b';
        std::vector<std::string> words{first, second, first};
        auto s = second;
        s += first;
        s += first;
        s += 'z';
        s += first;
        s += second;
        s += first;
        s += first;
        auto sorted_words = words;
        std::ranges::sort(sorted_words);
        std::vector<int> expected;
        for (size_t start = 0; start + 3 * length <= s.size(); ++start)
        {
            std::vector<std::string> chunks;
            chunks.reserve(3);
            for (size_t j = 0; j < 3; ++j)
            {
                chunks.push_back(s.substr(start + j * length, length));
            }
            std::ranges::sort(chunks);
            if (chunks == sorted_words)
            {
                expected.push_back(static_cast<int>(start));
            }
        }
        Solution instance;
        auto actual = instance.findSubstring(s, words);
        std::ranges::sort(actual);
        ASSERT_EQ(expected, actual);
    }
}
