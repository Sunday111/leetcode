#include "0068_text_justification.hpp"
#include "gtest/gtest.h"

TEST(t0068_text_justification, test_1)
{
    std::vector<std::string> words{
        "This",
        "is",
        "an",
        "example",
        "of",
        "text",
        "justification.",
    };

    std::vector<std::string> expected{
        "This    is    an",
        "example  of text",
        "justification.  ",
    };

    ASSERT_EQ(Solution{}.fullJustify(words, 16), expected);
}
