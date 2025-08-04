#include "int_if.hpp"

#include <gtest/gtest.h>

#include <limits>
#include <random>
#include <type_traits>

// === Typed test fixture ===
template <typename T>
class IntIfTest : public ::testing::Test
{
};

using IntegralTypes = ::testing::Types<
    int8_t,
    uint8_t,
    int16_t,
    uint16_t,
    int32_t,
    uint32_t,
    int64_t,
    uint64_t>;

TYPED_TEST_SUITE(IntIfTest, IntegralTypes);

// === Fuzzy test with random inputs ===
TYPED_TEST(IntIfTest, FuzzyCorrectness)
{
    using T = TypeParam;
    using Limits = std::numeric_limits<T>;
    using DT = std::conditional_t<std::is_signed_v<T>, int64_t, uint64_t>;

    constexpr size_t kNumSamples = 1000000;
    std::mt19937 rng(42);

    std::uniform_int_distribution<DT> dist{Limits::min(), Limits::max()};
    for (size_t i = 0; i != kNumSamples; ++i)
    {
        const T a = static_cast<T>(dist(rng)), b = static_cast<T>(dist(rng));
        ASSERT_EQ(iif(true, a, b), a)
            << "int_if(true, " << +a << ", " << +b << ")";
        ASSERT_EQ(iif(false, a, b), b)
            << "int_if(false, " << +a << ", " << +b << ")";
    }
}
