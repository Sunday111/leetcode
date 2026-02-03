#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "force_inline.hpp"

template <
    typename T,
    typename Cmp,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
struct heap_with_erase
{
    template <typename Op>
    FORCE_INLINE constexpr static void heap_op(
        Op&& op,
        std::vector<T>& rng) noexcept
    {
        std::forward<Op>(op)(rng, Cmp{});
    }

    FORCE_INLINE constexpr static void push_(std::vector<T>& rng, T v) noexcept
    {
        rng.push_back(v);
        heap_op(std::ranges::push_heap, rng);
    }

    FORCE_INLINE constexpr static void pop_(std::vector<T>& rng) noexcept
    {
        heap_op(std::ranges::pop_heap, rng);
        rng.pop_back();
    }

    FORCE_INLINE constexpr void reserve(size_t n) noexcept
    {
        queued.reserve(n);
        erased.reserve(n);
    }

    template <typename It>
    FORCE_INLINE constexpr void init(It begin, It end) noexcept
    {
        assert(empty());
        queued.insert(queued.end(), begin, end);
        heap_op(std::ranges::make_heap, queued);
    }

    [[nodiscard]] FORCE_INLINE const T& top() const noexcept
    {
        purge();
        return queued.front();
    }

    FORCE_INLINE constexpr void pop() noexcept
    {
        purge();
        pop_(queued);
    }

    [[nodiscard]] FORCE_INLINE constexpr bool empty() const noexcept
    {
        return queued.size() == erased.size();
    }

    [[nodiscard]] FORCE_INLINE constexpr size_t size() const noexcept
    {
        return queued.size() - erased.size();
    }

    FORCE_INLINE constexpr void push(const T& v) noexcept { push_(queued, v); }

    FORCE_INLINE constexpr void erase(const T& v) noexcept { push_(erased, v); }

private:
    [[nodiscard]] FORCE_INLINE static constexpr bool eq(
        const T& a,
        const T& b) noexcept
    {
        constexpr Proj p{};
        constexpr Cmp c{};
        auto pa = p(a), pb = p(b);
        return c(pa, pb) == c(pb, pa);
    }

    FORCE_INLINE constexpr void purge() const noexcept
    {
        while (!erased.empty() && eq(erased.front(), queued.front()))
        {
            pop_(erased);
            pop_(queued);
        }
    }

    mutable std::vector<T> queued, erased;
};

template <
    typename T,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
using min_heap_with_erase = heap_with_erase<T, std::greater<>, Proj, Allocator>;

template <
    typename T,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
using max_heap_with_erase = heap_with_erase<T, std::less<>, Proj, Allocator>;
