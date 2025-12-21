#include "0955_delete_columns_to_make_sorted_2.hpp"
#include "gtest/gtest.h"

TEST(t0955_delete_columns_to_make_sorted_2, test_1)
{
    std::vector<std::string> strs{"ca", "bb", "ac"};
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 1);
}
TEST(t0955_delete_columns_to_make_sorted_2, test_2)
{
    std::vector<std::string> strs{
        "vdy",
        "vei",
        "zvc",
        "zld",
    };
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 2);
}
TEST(t0955_delete_columns_to_make_sorted_2, test_3)
{
    std::vector<std::string> strs{
        "bbjwefkpb",
        "axmksfchw",
    };
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 1);
}
TEST(t0955_delete_columns_to_make_sorted_2, test_4)
{
    std::vector<std::string> strs{
        "koccmoezl",
        "hbccayhbd",
    };
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 3);
}
TEST(t0955_delete_columns_to_make_sorted_2, test_5)
{
    std::vector<std::string> strs{
        "jsebodtwc",
        "cnneoytml",
        "eeneuyzlu",
        "ewpnmtivg",
    };
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 2);
}

TEST(t0955_delete_columns_to_make_sorted_2, test_6)
{
    std::vector<std::string> strs{
        "abx",
        "agz",
        "bgc",
        "bfc",
    };
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 1);
}

TEST(t0955_delete_columns_to_make_sorted_2, test_7)
{
    std::vector<std::string> strs{"aa", "ac", "ab"};
    ASSERT_EQ(Solution{}.minDeletionSize(strs), 1);
}
