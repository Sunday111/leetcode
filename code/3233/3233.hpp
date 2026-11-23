#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

#include "bitsets/bitset_view/bsv_fill.hpp"
#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"

template <size_t segment_size = 64 * 8>
class PrimesStorage
{
public:
    constexpr PrimesStorage() noexcept { make_first_segment(); }

    PrimesStorage(const PrimesStorage&) = delete;
    PrimesStorage& operator=(const PrimesStorage&) = delete;

    constexpr void cache_primes(uint64_t value) noexcept
    {
        while (m_primes.back() < value)
        {
            make_next_segment();
        }
    }

    [[nodiscard]] constexpr uint64_t get_at(size_t prime_index) noexcept
    {
        [[likely]]
        if (prime_index < m_primes.size())
        {
            return m_primes[prime_index];
        }

        make_segments(prime_index);
        return get_at(prime_index);
    }

    [[nodiscard]] std::span<const uint64_t> get_cached_primes_view()
        const noexcept
    {
        return m_primes;
    }

private:
    // fill first segment by usual Eratosthenes sieve
    constexpr void make_first_segment() noexcept
    {
        BitsetView<uint64_t, segment_size> segment{m_segment.data()};
        bsv_fill<true>(segment);
        bsv_set<false>(segment, 0);
        bsv_set<false>(segment, 1);

        for (size_t i = 2; i < (segment_size / 2) + 1; ++i)
        {
            if (bsv_get(segment, i))
            {
                for (size_t j = i * 2; j < segment_size; j += i)
                {
                    bsv_set<false>(segment, j);
                }
            }
        }

        for (uint64_t i = 0; i < segment_size; ++i)
        {
            if (bsv_get(segment, i))
            {
                m_primes.push_back(i);
            }
        }

        m_segments.push_back(m_primes.size());
    }

    constexpr void make_segments(size_t required_prime_index) noexcept
    {
        while (required_prime_index >= m_primes.size())
        {
            make_next_segment();
        }
    }

    [[nodiscard]] static constexpr float my_sqrt(const float x)
    {
        int ui = std::bit_cast<int>(x);
        ui = (1 << 29) + (ui >> 1) - (1 << 22);
        return std::bit_cast<float>(ui);
    }

    constexpr void make_next_segment() noexcept
    {
        const size_t prev_primes = m_primes.size();
        const size_t segment_index = m_segments.size();
        const size_t segment_begin = segment_index * segment_size;
        const size_t segment_end = segment_begin + segment_size;
        const size_t m = segment_end - 1;
        const size_t msq =
            static_cast<size_t>(my_sqrt(static_cast<float>(m))) + 1;

        BitsetView<uint64_t, segment_size> segment{m_segment.data()};
        bsv_fill<true>(segment);

        for (auto prime : m_primes)
        {
            if (prime > msq) break;

            size_t pos = segment_begin / prime;
            pos += (segment_begin % prime) ? 1 : 0;
            pos *= prime;

            while (pos < segment_end)
            {
                bsv_set<false>(segment, pos % segment_size);
                pos += prime;
            }
        }

        for (size_t i = 0; i < segment_size; ++i)
        {
            if (bsv_get(segment, i))
            {
                m_primes.push_back(segment_begin + i);
            }
        }

        const size_t primes_in_segment = m_primes.size() - prev_primes;
        m_segments.push_back(primes_in_segment);
    }

private:
    std::array<uint64_t, segment_size / 64 + (segment_size % 64 != 0)>
        m_segment{};
    std::vector<uint64_t> m_primes;
    std::vector<size_t> m_segments;
};

class Solution
{
public:
    [[nodiscard]] static constexpr inline uint32_t isqrt(uint32_t s) noexcept
    {
        if (s <= 1) return s;

        uint32_t x0 = s / 2;
        uint32_t x1 = (x0 + s / x0) / 2;

        while (x1 < x0)
        {
            x0 = x1;
            x1 = (x0 + s / x0) / 2;
        }

        return x0;
    }

    static uint32_t nonSpecialCount(uint32_t l, uint32_t r)
    {
        auto in_range = [&](auto v)
        {
            auto sq = v * v;
            return sq >= l && sq <= r;
        };

        auto sqrt_l = isqrt(l);
        auto sqrt_r = isqrt(r);

        static PrimesStorage ps;
        ps.cache_primes(std::max(sqrt_l, sqrt_r));
        auto primes = ps.get_cached_primes_view();
        auto li = std::ranges::lower_bound(primes, sqrt_l);
        auto ri = std::ranges::upper_bound(primes, sqrt_r);
        while (li != ri && !in_range(*li)) ++li;

        return (r - l + 1) - static_cast<uint32_t>(std::distance(li, ri));
    }
};
