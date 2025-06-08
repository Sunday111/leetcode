#include "1700_number_of_students_unable_to_eat.hpp"
#include "gtest/gtest.h"

TEST(t1700_number_of_students_unable_to_eat, test_1)
{
    std::vector students{1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1};
    std::vector sandwiches{0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0};
    ASSERT_EQ(Solution::countStudents(students, sandwiches), 3);
}
