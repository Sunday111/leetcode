#include "2514_count_anagrams.hpp"
#include "gtest/gtest.h"

TEST(t2514_count_anagrams, test_1)
{
    ASSERT_EQ(Solution{}.countAnagrams("too hot"), 18);
    ASSERT_EQ(CachingFactorialsSolution{}.countAnagrams("too hot"), 18);
}

TEST(t2514_count_anagrams, test_2)
{
    ASSERT_EQ(
        Solution{}.countAnagrams(
            "b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp"),
        210324488);

    ASSERT_EQ(
        CachingFactorialsSolution{}.countAnagrams(
            "b okzojaporykbmq tybq zrztwlolvcyumcsq jjuowpp"),
        210324488);
}
