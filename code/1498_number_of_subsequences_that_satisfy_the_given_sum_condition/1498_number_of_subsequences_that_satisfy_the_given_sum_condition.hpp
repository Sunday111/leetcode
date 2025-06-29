
#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <span>
#include <vector>

#ifdef __GNUC__
#define INLINE inline __attribute__((always_inline))
#define HOT __attribute__((hot))
#else
#define INLINE inline
#define HOT
#endif

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
static constexpr int kMOD = 1'000'000'007;

template <typename To, typename From, size_t extent = std::dynamic_extent>
[[nodiscard]] static auto reinterpret_span(std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

[[nodiscard]] INLINE constexpr u32 modAfterAdd(u32 v) noexcept
{
    const u32 gt = v > kMOD;
    return v - (-gt & kMOD);
}

struct ModInt
{
    INLINE constexpr ModInt& operator+=(const ModInt& rhs) noexcept HOT
    {
        value += rhs.value;
        if (value >= kMOD) value -= kMOD;
        return *this;
    }

    [[nodiscard]] INLINE constexpr ModInt operator+(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    INLINE constexpr ModInt& operator-=(const ModInt& rhs) noexcept HOT
    {
        value -= rhs.value;
        return *this;
    }

    [[nodiscard]] INLINE constexpr ModInt operator-(
        const ModInt& rhs) const noexcept HOT
    {
        auto copy = *this;
        copy -= rhs;
        return copy;
    }

    INLINE constexpr ModInt& operator*=(const ModInt& rhs) noexcept HOT
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = static_cast<u32>(v);
        return *this;
    }

    [[nodiscard]] INLINE constexpr ModInt operator*(
        const ModInt& rhs) const noexcept HOT
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    [[nodiscard]] INLINE constexpr ModInt inverse() const noexcept HOT
    {
        auto a = value;
        u32 x0 = 1, x1 = 0, mod = kMOD;
        while (a)
        {
            u32 q = mod / a;
            u32 r = mod % a;
            u32 x2 = x1 - q * x0;
            mod = a;
            a = r;
            x1 = x0;
            x0 = x2;
        }
        return {(x1 + kMOD) % kMOD};
    }

    INLINE constexpr ModInt& operator/=(const ModInt& rhs) noexcept HOT
    {
        return *this *= rhs.inverse();
    }

    [[nodiscard]] INLINE constexpr ModInt operator/(
        const ModInt& rhs) const noexcept HOT
    {
        auto copy = *this;
        copy /= rhs;
        return copy;
    }

    [[nodiscard]] INLINE constexpr ModInt pow(u32 exp) const noexcept HOT
    {
        if (exp == 0) return {1};
        std::bitset<32> bits(exp);
        ModInt ans = *this;
        u8 i = (31 - std::countl_zero(exp)) & 0xFF;
        while (i)
        {
            --i;
            ans *= ans;
            ans *= bits[i] ? *this : ModInt{1};
        }
        return ans;
    }

    u32 value = 0;
};

class Solution
{
public:
    [[nodiscard]] INLINE static u32 numSubseq(
        std::vector<int>& nums_,
        u32 target) noexcept HOT
    {
        return numSubseq(reinterpret_span<u32>(std::span{nums_}), target);
    }

    [[nodiscard]] INLINE static constexpr u32 dist(auto a, auto b) noexcept
    {
        return static_cast<u32>(std::distance(a, b));
    }

    INLINE static void init() noexcept
    {
        auto& r = getPowersOfTwo();
        r.reserve(1'000'000);
        r.push_back(ModInt{1});
        while (r.size() != 1'000'000)
        {
            u32 v = (r.back().value << 1);
            if (v >= kMOD) v -= kMOD;
            r.push_back({v});
        }
    }

    [[nodiscard]] static std::vector<ModInt>& getPowersOfTwo() noexcept
    {
        static std::vector<ModInt> r;
        return r;
    }

    [[nodiscard]] INLINE static constexpr u32 numSubseq(
        std::span<u32> nums,
        u32 target) noexcept HOT
    {
        // counting sort
        {
            u32 max = 0;
            std::array<u32, 1'000'000> freq{0};
            for (u32 x : nums)
            {
                if (x <= target)
                {
                    freq[x]++;
                    if (x > max) max = x;
                }
            }

            auto i = nums.begin();
            u32 limit = std::min(max, target);
            u32 x = 1;
            for (; x <= limit && i == nums.begin(); ++x)
            {
                i = std::fill_n(i, freq[x], x);
            }
            limit = std::min(max, target - std::min(nums.front(), target));
            for (; x <= limit; x++) i = std::fill_n(i, freq[x], x);
            nums = std::span{nums.begin(), i};
        }

        const std::vector<ModInt>& pow2 = getPowersOfTwo();

        u32 i = dist(nums.begin(), std::ranges::upper_bound(nums, target / 2));
        constexpr ModInt one{1};
        ModInt r = pow2[i] - one;

        const u32 n = static_cast<u32>(nums.size());
        for (auto j = i; j != n;)
        {
            u32 limit = target - nums[j];
            while (i != 0)
            {
                auto prev = i - 1;
                if (nums[prev] <= limit) break;
                i = prev;
            }
            if (i == 0) break;

            u32 k = j + 1;
            while (k != n && nums[k] == nums[j]) ++k;

            r += pow2[j - i] * (pow2[i] - one) * (pow2[k - j] - one);
            j = k;
        }

        return r.value;
    }
};

const auto init = []() noexcept
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    Solution::init();
    return 'c';
}();
