#include "1733_minimum_number_of_people_to_teach.hpp"
#include "gtest/gtest.h"
#include "parse_2d_array.hpp"

TEST(t1733_minimum_number_of_people_to_teach, test_1)
{
    auto languages = parse2DArray("[[2],[1,3],[1,2],[3]]");
    auto friendships = parse2DArray("[[1,4],[1,2],[3,4],[2,3]]");
    ASSERT_EQ(Solution{}.minimumTeachings(3, languages, friendships), 2);
}
