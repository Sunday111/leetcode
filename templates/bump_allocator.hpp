#pragma once

#include <array>
#include <cassert>

#include "integral_aliases.hpp"
#include "no_sanitizers.hpp"

struct ScopedArena
{
    u32 rollback_offset = 0;
    u32* offset = nullptr;

    [[gnu::always_inline]] inline void Reset() const noexcept
    {
        *offset = rollback_offset;
    }

    [[gnu::always_inline]] inline ~ScopedArena() noexcept
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
    [[gnu::always_inline]] inline static GlobalBufferStorage&
    Instance() noexcept
    {
        static GlobalBufferStorage inst;
        return inst;
    }

    [[gnu::always_inline]] inline void Reset() noexcept
    {
        allocator_offset_ = 0;
    }

    [[nodiscard, gnu::always_inline]] inline ScopedArena StartArena() noexcept
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
    [[gnu::always_inline]] inline explicit constexpr BumpAllocator(
        const BumpAllocator<U, S>&) noexcept
    {
    }

    [[nodiscard, gnu::always_inline, gnu::hot]] inline T* allocate(
        u32 n) noexcept NO_SANITIZERS
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

    [[gnu::always_inline]] inline void deallocate(T*, u32) noexcept {}

    // equality so containers can compare allocators
    [[gnu::always_inline]] inline constexpr bool operator==(
        const BumpAllocator&) const noexcept
    {
        return true;
    }
    [[gnu::always_inline]] inline constexpr bool operator!=(
        const BumpAllocator&) const noexcept
    {
        return false;
    }
};

template <typename T>
class ObjectWithoutDtor
{
    alignas(T) std::array<std::byte, sizeof(T)> arr;

public:
    [[gnu::always_inline]] inline ObjectWithoutDtor() noexcept { Reset(); }
    [[gnu::always_inline]] inline void Reset() noexcept { new (&get()) T(); }

    [[gnu::always_inline]] inline T& get() noexcept
    {
        return *reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T& get() const noexcept
    {
        return *reinterpret_cast<const T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline T* operator->() noexcept
    {
        return reinterpret_cast<T*>(arr.data());  // NOLINT
    }

    [[gnu::always_inline]] inline const T* operator->() const noexcept
    {
        return reinterpret_cast<const T*>(arr.data());  // NOLINT
    }
};
