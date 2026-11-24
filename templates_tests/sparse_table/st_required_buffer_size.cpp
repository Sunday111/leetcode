#include <array>
#include <cstddef>

#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "sparse_table/st_required_buffer_size.hpp"

TEST(SparseTable, RequiredBufferSizeAtLevelBoundaries)
{
    EXPECT_EQ(st_required_buffer_size(0), 0);
    EXPECT_EQ(st_required_buffer_size(1), 1);
    EXPECT_EQ(st_required_buffer_size(2), 4);
    EXPECT_EQ(st_required_buffer_size(3), 6);
    EXPECT_EQ(st_required_buffer_size(4), 12);
    EXPECT_EQ(st_required_buffer_size(7), 21);
    EXPECT_EQ(st_required_buffer_size(8), 32);
    EXPECT_EQ(st_required_buffer_size(9), 36);
    EXPECT_EQ(st_required_buffer_size(u8{255}), 2040);
    EXPECT_EQ(st_required_buffer_size(u16{65535}), 1048560);
}

TEST(SparseTable, RequiredBufferSizeIsConstantExpression)
{
    constexpr std::size_t max_n = 100'000;
    using Buffer = std::array<int, st_required_buffer_size(max_n)>;
    static_assert(sizeof(Buffer) == 1'700'000 * sizeof(int));
    static_assert(noexcept(st_required_buffer_size(max_n)));
}
