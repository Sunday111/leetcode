#include <array>
#include <cassert>
#include <cstdint>
#include <vector>





#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define NO_SANITIZERS \
    __attribute__((no_sanitize("undefined", "address", "coverage", "thread")))

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    FORCE_INLINE void Reset() const noexcept { *offset = rollback_offset; }

    FORCE_INLINE ~ScopedArena() noexcept
    {
        if (offset)
        {
            Reset();
            offset = nullptr;
        }
    }
};

template <u32 num_bytes>
struct GlobalBufferStorage
{
    FORCE_INLINE static GlobalBufferStorage& Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    FORCE_INLINE void Reset() noexcept { allocator_offset_ = 0; }

    [[nodiscard]] FORCE_INLINE ScopedArena StartArena() noexcept
    {
        return {allocator_offset_, &allocator_offset_};
    }

    alignas(64) std::array<std::byte, num_bytes> allocator_memory_;
    u32 allocator_offset_;
};

template <typename T, typename S>
struct BumpAllocator
{
    using value_type = T;

    BumpAllocator() = default;

    template <class U>
    FORCE_INLINE explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard]] FORCE_INLINE T* allocate(u32 n) noexcept HOT_PATH
        NO_SANITIZERS
    {
        auto& inst = S::Instance();

        // align current offset for T
        u32 alignment = alignof(T);
        u32 offset = inst.allocator_offset_;
        u32 aligned_offset = (offset + (alignment - 1)) & ~(alignment - 1);
        u32 bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return reinterpret_cast<T*>(
            inst.allocator_memory_.data() + aligned_offset);  // NOLINT
    }

    FORCE_INLINE void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    FORCE_INLINE constexpr bool operator==(const BumpAllocator&) const noexcept
    {
        return true;
    }
    FORCE_INLINE constexpr bool operator!=(const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    FORCE_INLINE ObjectWithoutDtor() noexcept { Reset(); }
    FORCE_INLINE void Reset() noexcept { new (&get()) T(); }

    FORCE_INLINE T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    FORCE_INLINE const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};



template <typename Value, typename Storage>
using BumpVector = std::vector<Value, BumpAllocator<Value, Storage>>;


using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

class Solution
{
    static constexpr i64 MOD = 1'000'000'007;

public:
    using SolutionStorage = GlobalBufferStorage<1 << 20>;
    template <typename T>
    using Vec = BumpVector<T, SolutionStorage>;

    i32 numberOfStableArrays(u16 zero, u16 one, u16 limit)
    {
        auto arena = SolutionStorage::Instance().StartArena();

        Vec<Vec<std::array<i32, 2>>> dp;
        dp.resize(zero + 1);
        for (auto& e : dp) e.resize(one + 1);

        for (u16 i = std::min(zero, limit) + 1; i--;)
        {
            dp[i][0][0] = 1;
        }

        for (u16 j = std::min(one, limit) + 1; j--;)
        {
            dp[0][j][1] = 1;
        }

        for (u16 i = 1; i <= zero; ++i)
        {
            for (u16 j = 1; j <= one; ++j)
            {
                bool bi = i >= limit + 1;
                bool bj = j >= limit + 1;
                u16 loi = std::min<u16>(i - 1 - limit, zero);
                u16 loj = std::min<u16>(j - 1 - limit, one);
                dp[i][j][0] = static_cast<int>(
                    (dp[i - 1][j][0] + dp[i - 1][j][1] -
                     (dp[loi][j][1] & -i32{bi}) + MOD) %
                    MOD);
                dp[i][j][1] = static_cast<int>(
                    (dp[i][j - 1][0] + dp[i][j - 1][1] -
                     (dp[i][loj][0] & -i32{bj}) + MOD) %
                    MOD);
            }
        }
        return static_cast<int>((dp[zero][one][0] + dp[zero][one][1]) % MOD);
    }
};
