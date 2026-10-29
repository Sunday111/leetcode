#include <array>

#include "graph/euler_tour.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"

TEST(EulerTour, RequiredBufferSize)
{
    EXPECT_EQ(euler_tour_required_buffer_size(0), 0);
    EXPECT_EQ(euler_tour_required_buffer_size(1), 1);
    EXPECT_EQ(euler_tour_required_buffer_size(2), 3);
    EXPECT_EQ(euler_tour_required_buffer_size(5), 9);
    EXPECT_EQ(euler_tour_required_buffer_size(u8{255}), 509);
    EXPECT_EQ(euler_tour_required_buffer_size(u16{50'000}), 99'999);
}

TEST(EulerTour, RequiredBufferSizeIsConstantExpression)
{
    using Buffer = std::array<u32, euler_tour_required_buffer_size(50'000)>;
    static_assert(sizeof(Buffer) == 99'999 * sizeof(u32));
    static_assert(noexcept(euler_tour_required_buffer_size(50'000)));
}
