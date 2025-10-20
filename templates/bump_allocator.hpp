#pragma once

#include <array>
#include <cassert>

#include "force_inline.hpp"
#include "hot_path.hpp"
#include "no_sanitizers.hpp"

struct ScopedArena
{
    size_t rollback_offset = 0;
    size_t* offset = nullptr;

    ~ScopedArena()
    {
        if (offset)
        {
            *offset = rollback_offset;
            offset = nullptr;
        }
    }
};

template <size_t num_bytes>
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

    std::array<std::byte, num_bytes> allocator_memory_;
    size_t allocator_offset_;
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

    [[nodiscard]] FORCE_INLINE T* allocate(std::size_t n) noexcept HOT_PATH
        NO_SANITIZERS
    {
        auto& inst = S::Instance();

        // raw buffer start
        std::byte* base = inst.allocator_memory_.data();

        // align current offset for T
        std::size_t alignment = alignof(T);
        std::size_t offset = inst.allocator_offset_;
        std::size_t aligned_offset =
            (offset + (alignment - 1)) & ~(alignment - 1);

        // compute how many bytes we need
        std::size_t bytes = n * sizeof(T);

        assert(aligned_offset + bytes <= inst.allocator_memory_.size());

        // pointer to aligned location
        void* p = base + aligned_offset;  // NOLINT

        // bump offset
        inst.allocator_offset_ = aligned_offset + bytes;

        return static_cast<T*>(p);
    }

    FORCE_INLINE void deallocate(T*, std::size_t) noexcept {}

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
