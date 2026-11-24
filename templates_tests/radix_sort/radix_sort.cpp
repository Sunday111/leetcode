#include <algorithm>
#include <limits>
#include <random>
#include <vector>

#include "gtest/gtest.h"
#include "radix_sort/radix_sort.hpp"

template <typename T, u32 key_bits, u8 bits_per_pass>
concept CanRadixSort =
    requires(T* data) { radix_sort<key_bits, bits_per_pass>(data, 1); };

static_assert(CanRadixSort<u16, 16, 10>);
static_assert(CanRadixSort<u32, 0, 10>);
static_assert(!CanRadixSort<u8, 8, 4>);
static_assert(!CanRadixSort<u32, 25, 0>);
static_assert(!CanRadixSort<u16, 17, 10>);

template <typename T>
class RadixSortValueTest : public ::testing::Test
{
protected:
    static constexpr unsigned seed = 1234;
    static constexpr size_t num_values = 20'000;
    static constexpr size_t repeat = 20;

    std::mt19937 rnd{seed};
    std::uniform_int_distribution<T> distr;

    std::vector<T> values;
    std::vector<T> custom_sorted;
    std::vector<T> std_sorted;

    void generate_values()
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i) values.emplace_back(distr(rnd));
    }

    void run_sort_tests()
    {
        for (size_t i = 0; i != repeat; ++i)
        {
            generate_values();

            // Ascending
            custom_sorted = values;
            std_sorted = values;

            radix_sort<sizeof(T) * 8, 4>(
                custom_sorted.data(),
                static_cast<u32>(custom_sorted.size()));
            std::ranges::sort(std_sorted, std::less{});
            ASSERT_EQ(custom_sorted, std_sorted);

            // Descending
            custom_sorted = values;
            std_sorted = values;

            radix_sort<sizeof(T) * 8, 4, SortOrder::Descending>(
                custom_sorted.data(),
                static_cast<u32>(custom_sorted.size()));
            std::ranges::sort(std_sorted, std::greater{});
            ASSERT_EQ(custom_sorted, std_sorted);
        }
    }
};

using TestTypes =
    ::testing::Types<int16_t, int32_t, int64_t, uint16_t, uint32_t, uint64_t>;
TYPED_TEST_SUITE(RadixSortValueTest, TestTypes);

TYPED_TEST(RadixSortValueTest, RandomizedCorrectness)
{
    this->run_sort_tests();
}

TYPED_TEST(RadixSortValueTest, EmptySingletonAndLimits)
{
    using T = TypeParam;
    for (std::vector<T> values :
         {std::vector<T>{},
          std::vector<T>{std::numeric_limits<T>::max()},
          std::vector<T>{
              std::numeric_limits<T>::max(),
              T{1},
              std::numeric_limits<T>::lowest(),
              T{0},
              std::numeric_limits<T>::max(),
              std::numeric_limits<T>::lowest()}})
    {
        auto expected = values;
        std::ranges::sort(expected);
        radix_sort<sizeof(T) * 8, 4>(
            values.data(),
            static_cast<u32>(values.size()));
        ASSERT_EQ(values, expected);
        std::ranges::reverse(expected);
        radix_sort<sizeof(T) * 8, 4, SortOrder::Descending>(
            values.data(),
            static_cast<u32>(values.size()));
        ASSERT_EQ(values, expected);
    }
}

TEST(RadixSort, MoreElementsThanTheValueTypeCanCount)
{
    std::vector<u16> values(70'000);
    u32 remaining = 70'000;
    for (auto& value : values) value = remaining-- & 0xFFFF;
    auto expected = values;
    std::ranges::sort(expected);
    radix_sort<16, 4>(values.data(), static_cast<u32>(values.size()));
    ASSERT_EQ(values, expected);
}

TEST(RadixSort, TenBitPassesOnThirtyTwoBitKeys)
{
    const std::vector<u32> input{0x80000001, 0xC0000000, 0x40000001, 0, 1};
    auto values = input;
    radix_sort<32>(values.data(), 5);
    EXPECT_EQ(
        values,
        (std::vector<u32>{0, 1, 0x40000001, 0x80000001, 0xC0000000}));

    values = input;
    radix_sort<30>(values.data(), 5);
    EXPECT_EQ(
        values,
        (std::vector<u32>{0xC0000000, 0, 0x80000001, 0x40000001, 1}));
}

TEST(RadixSort, DefaultDigitWidthSortsExactlyTwentyFiveLowBits)
{
    std::vector<int32_t> values{-1, 1 << 25, 1 << 24, 0, INT32_MIN, 1};
    radix_sort<25>(values.data(), 6);
    EXPECT_EQ(
        values,
        (std::vector<int32_t>{1 << 25, 0, INT32_MIN, 1, 1 << 24, -1}));
}

TEST(RadixSort, ShortFinalPassIncludesSignBit)
{
    std::vector<int32_t> values{0, INT32_MIN, -1, INT32_MAX, 1};
    radix_sort<32, 11, SortOrder::Descending>(values.data(), 5);
    EXPECT_EQ(values, (std::vector<int32_t>{INT32_MAX, 1, 0, -1, INT32_MIN}));
}

TEST(RadixSort, ExactSmallCapacity)
{
    std::vector<u32> values{9, 1, 5, 3, 7, 0, 8, 2, 6, 4};
    auto expected = values;
    std::ranges::sort(expected);
    radix_sort<32, 4, SortOrder::Ascending, 10>(values.data(), 10);
    ASSERT_EQ(values, expected);
}

TEST(RadixSort, ReusesHistogramAcrossDigitAndCountWidths)
{
    u16 narrow[]{0xFFFF, 0, 0xFF00, 1};
    u32 wide[]{0x1FFFF, 0, 0x10000, 1};
    for (int run = 0; run != 2; ++run)
    {
        radix_sort<16, 16, SortOrder::Descending, 4>(narrow, 4);
        EXPECT_TRUE(std::ranges::is_sorted(narrow, std::greater{}));
        radix_sort<32, 8>(wide, 4);
        EXPECT_TRUE(std::ranges::is_sorted(wide));
        radix_sort<17, 17, SortOrder::Descending>(wide, 4);
        EXPECT_TRUE(std::ranges::is_sorted(wide, std::greater{}));
        std::ranges::reverse(narrow);
    }
}

template <u32 key_bits, u8 digit_bits>
struct StableSortParams
{
    static constexpr u8 bits_per_pass = digit_bits;
    static constexpr u32 num_sorted_bits = key_bits;
};

template <typename T>
class StableRadixSortTest : public ::testing::Test
{
protected:
    static constexpr unsigned seed = 1234;
    static constexpr size_t num_values = 20'000;
    static constexpr size_t repeat = 20;

    std::mt19937 rnd{seed};
    std::uniform_int_distribution<u32> distr;

    static constexpr u32 kSizeA = T::num_sorted_bits;
    static constexpr u32 kSizeB = 32 - kSizeA;

    std::vector<u32> values;
    std::vector<u32> custom_sorted;
    std::vector<u32> std_sorted;

    void generate_values()
    {
        values.clear();
        values.reserve(num_values);
        for (size_t i = 0; i < num_values; ++i)
        {
            u32 a = distr(rnd) % (1 << kSizeA);
            u32 b = distr(rnd) % (1 << kSizeB);
            u32 v = (b << kSizeA) | a;
            values.emplace_back(v);
        }
    }

    template <u32 kMask, template <typename> typename Cmp>
    [[nodiscard, gnu::always_inline]] inline static constexpr bool
    mask_and_compare(u32 v1, u32 v2) noexcept
    {
        return Cmp<u32>{}((v1 & kMask), (v2 & kMask));
    }

    void run_sort_tests()
    {
        for (size_t i = 0; i != repeat; ++i)
        {
            generate_values();

            // Ascending
            custom_sorted = values;
            std_sorted = values;

            constexpr auto kMask = u32{0xFFFFFFFF} >> kSizeB;

            radix_sort<T::num_sorted_bits, T::bits_per_pass>(
                custom_sorted.data(),
                static_cast<u32>(custom_sorted.size()));
            std::ranges::stable_sort(
                std_sorted,
                mask_and_compare<kMask, std::less>);
            ASSERT_EQ(custom_sorted, std_sorted);

            // Descending
            custom_sorted = values;
            std_sorted = values;

            radix_sort<
                T::num_sorted_bits,
                T::bits_per_pass,
                SortOrder::Descending>(
                custom_sorted.data(),
                static_cast<u32>(custom_sorted.size()));
            std::ranges::stable_sort(
                std_sorted,
                mask_and_compare<kMask, std::greater>);
            ASSERT_EQ(custom_sorted, std_sorted);
        }
    }
};

using StableTestTypes = ::testing::Types<
    StableSortParams<6, 3>,
    StableSortParams<14, 7>,
    StableSortParams<20, 4>,
    StableSortParams<25, 10>>;

TYPED_TEST_SUITE(StableRadixSortTest, StableTestTypes);

TYPED_TEST(StableRadixSortTest, RandomizedCorrectness)
{
    this->run_sort_tests();
}
