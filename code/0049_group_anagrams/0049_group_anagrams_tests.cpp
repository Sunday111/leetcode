#include "0049_group_anagrams.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

TEST(t0049_group_anagrams, test_1)
{
    std::vector<std::string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    std::vector<std::vector<std::string>> expected{
        {"bat"},
        {"nat", "tan"},
        {"ate", "eat", "tea"},
    };
    auto r = Solution{}.groupAnagrams(strs);
    ASSERT_EQ(sorted(r), sorted(expected));
}
