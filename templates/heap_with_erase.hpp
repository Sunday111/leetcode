#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

template <
    typename T,
    typename Cmp,
    typename Proj = std::identity,
    template <typename> typename Allocator = std::allocator>
struct heap_with_erase
{
    template <typename Op>
    [[gnu::always_inline]] inline constexpr static void heap_op(
        Op&& op,
        std::vector<T>& rng) noexcept
    {
        std::forward<Op>(op)(rng, Cmp{});
    }

    [[gnu::always_inline]] inline constexpr static void push_(
        std::vector<T>& rng,
        T v) noexcept
    {
        rng.push_back(v);
        heap_op(std::ranges::push_heap, rng);
    }

    [[gnu::always_inline]] inline constexpr static void pop_(
        std::vector<T>& rng) noexcept
    {
        heap_op(std::ranges::pop_heap, rng);
        rng.pop_back();
    }

    [[gnu::always_inline]] inline constexpr void reserve(size_t n) noexcept
    {
        queued.reserve(n);
        erased.reserve(n);
    }

    template <typename It>
    [[gnu::always_inline]] inline constexpr void init(It begin, It end) noexcept
    {
        assert(empty());
        queued.insert(queued.end(), begin, end);
        heap_op(std::ranges::make_heap, queued);
    }

    [[nodiscard, gnu::always_inline]] inline const T& top() const noexcept
    {
        purge();
        return queued.front();
    }

    [[gnu::always_inline]] inline constexpr void pop() noexcept
    {
        purge();
        pop_(queued);
    }

    [[nodiscard, gnu::always_inline]] inline constexpr bool empty()
        const noexcept
    {
        return queued.size() == erased.size();
    }

    [[nodiscard, gnu::always_inline]] inline constexpr size_t size()
        const noexcept
    {
        return queued.size() - erased.size();
    }

    [[gnu::always_inline]] inline constexpr void push(const T& v) noexcept
    {
        push_(queued, v);
    }

    [[gnu::always_inline]] inline constexpr void erase(const T& v) noexcept
    {
        push_(erased, v);
    }

private:
    [[nodiscard, gnu::always_inline]] inline static constexpr bool eq(
        const T& a,
        const T& b) noexcept
    {
        constexpr Proj p{};
        constexpr Cmp c{};
        auto pa = p(a), pb = p(b);
        return c(pa, pb) == c(pb, pa);
    }

    [[gnu::always_inline]] inline constexpr void purge() const noexcept
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
