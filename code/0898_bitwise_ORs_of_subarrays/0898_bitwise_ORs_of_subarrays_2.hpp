#include <array>
#include <cstdint>
#include <vector>

using u32 = uint32_t;
using i32 = int32_t;

#ifdef __GNUC__
#define FORCE_INLINE inline __attribute__((always_inline))
#else
#define FORCE_INLINE inline
#endif

class HashSet
{
public:
    using KeyType = i32;
    static constexpr KeyType kInvalidKey = -1;
    static constexpr std::hash<KeyType> kHasher{};
    static constexpr u32 mask_ = (~u32{0}) >> (32 - 21);

    FORCE_INLINE void clear() noexcept { values_.fill(kInvalidKey); }

    FORCE_INLINE bool add(KeyType key) noexcept
    {
        u32 index = kHasher(key) & mask_;
        while (values_[index] != kInvalidKey && values_[index] != key)
        {
            ++index;
            index &= mask_;
        }
        return std::exchange(values_[index], key) != key;
    }

private:
    std::array<KeyType, 1 << 21> values_;
};

class Solution
{
public:
    [[nodiscard]] static constexpr size_t subarrayBitwiseORs(
        std::vector<i32>& a) noexcept
    {
        const u32 n = static_cast<u32>(a.size());

        static HashSet hs;
        hs.clear();

        u32 num_results = 0;

        for (u32 i = 0; i != n; ++i)
        {
            const i32 x = a[i];
            i32 skip = 0, take = x;
            num_results += hs.add(take);
            for (u32 j = i; j--;)
            {
                skip |= a[j];
                take = skip | x;
                if (skip == take) break;
                num_results += hs.add(take);
            }
        }

        return num_results;
    }
};
