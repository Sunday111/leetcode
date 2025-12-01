#include "2141_maximum_running_time_of_n_computers.hpp"
#include "gtest/gtest.h"

// TEST(t2141_maximum_running_time_of_n_computers, test_1)
// {
//     std::vector<int> batteries{3, 3, 3};
//     ASSERT_EQ(Solution{}.maxRunTime(2, batteries), 4);
// }

TEST(t2141_maximum_running_time_of_n_computers, test_2)
{
    std::vector<int> batteries{10, 10, 3, 5};
    ASSERT_EQ(Solution{}.maxRunTime(3, batteries), 8);
}
