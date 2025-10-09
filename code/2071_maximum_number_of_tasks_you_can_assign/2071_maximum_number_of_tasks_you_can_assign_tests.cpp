#include "2071_maximum_number_of_tasks_you_can_assign.hpp"
#include "gtest/gtest.h"

// TEST(t2071_maximum_number_of_tasks_you_can_assign, test_1)
// {
//     std::vector tasks{3, 2, 1}, workers{1, 2, 3};
//     ASSERT_EQ(Solution{}.maxTaskAssign(tasks, workers, 1, 1), 3);
// }

// TEST(t2071_maximum_number_of_tasks_you_can_assign, test_2)
// {
//     std::vector tasks{5, 9, 8, 5, 9};
//     std::vector workers{1, 6, 4, 2, 6};
//     std::ranges::sort(tasks), std::ranges::sort(workers);
//     std::println("{:20}: {}", "tasks", tasks);
//     std::println("{:20}: {}", "workers", workers);
//     ASSERT_EQ(Solution{}.maxTaskAssign(tasks, workers, 1, 5), 3);
// }

TEST(t2071_maximum_number_of_tasks_you_can_assign, test_3)
{
    std::vector tasks{3, 2, 1};
    std::vector workers{0, 3, 3};
    std::ranges::sort(tasks), std::ranges::sort(workers);
    std::println("{:20}: {}", "tasks", tasks);
    std::println("{:20}: {}", "workers", workers);
    ASSERT_EQ(Solution{}.maxTaskAssign(tasks, workers, 1, 1), 3);
}
