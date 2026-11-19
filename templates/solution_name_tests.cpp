#include <type_traits>

#include "gtest/gtest.h"
#include "solution_name.hpp"

namespace
{
class LC_SOLUTION_NAME(first)
{
public:
    inline static int value = 0;
};

class LC_SOLUTION_NAME(second)
{
public:
    inline static int value = 0;
};

static_assert(!std::is_same_v<Solution_first, Solution_second>);

TEST(SolutionName, LocalVariantsHaveIndependentStorage)
{
    Solution_first::value = 1;
    Solution_second::value = 2;
    EXPECT_EQ(Solution_first::value, 1);
    EXPECT_EQ(Solution_second::value, 2);
}
}  // namespace
