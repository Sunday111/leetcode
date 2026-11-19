#pragma once

#include <algorithm>
#include <cstdint>
#include <span>
#include <vector>

template <size_t Size, typename Word = uint64_t>
class Bitset
{
public:
    static constexpr size_t kBitsInWord = sizeof(Word) * 8;
    static constexpr size_t kNumFullWords = Size / kBitsInWord;
    static constexpr size_t kNumWords =
        (Size % kBitsInWord) ? kNumFullWords + 1 : kNumFullWords;

public:
    constexpr Bitset() {}

    constexpr void reset(bool value) noexcept
    {
        const auto k = value ? ~uint64_t{1} : 0;
        for (size_t i = 0; i < kNumWords; ++i)
        {
            words[i] = k;
        }
    }

    constexpr bool get_at(size_t idx) const
    {
        size_t i = idx / 64;
        size_t j = idx % 64;
        auto mask = make_bit_mask(j);
        bool r = (words[i] & mask);
        return r;
    }

    constexpr void set_at(size_t idx, bool new_value)
    {
        size_t i = idx / 64;
        size_t j = idx % 64;
        auto mask = make_bit_mask(j);
        if (new_value)
        {
            words[i] |= mask;
        }
        else
        {
            words[i] &= ~mask;
        }
    }

private:
    static constexpr Word make_bit_mask(size_t index)
    {
        return (static_cast<Word>(1) << index);
    }

private:
    std::array<Word, kNumWords> words{};
};

template <size_t segment_size = 64 * 8>
class PrimesStorage
{
public:
    constexpr PrimesStorage() noexcept { make_first_segment(); }

    PrimesStorage(const PrimesStorage&) = delete;
    PrimesStorage& operator=(const PrimesStorage&) = delete;

    constexpr void cache_primes_up_to(uint64_t value) noexcept
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
        m_segment.reset(true);
        m_segment.set_at(0, false);
        m_segment.set_at(1, false);

        for (size_t i = 2; i < (segment_size / 2) + 1; ++i)
        {
            if (m_segment.get_at(i))
            {
                for (size_t j = i * 2; j < segment_size; j += i)
                {
                    m_segment.set_at(j, false);
                }
            }
        }

        for (uint64_t i = 0; i < segment_size; ++i)
        {
            if (m_segment.get_at(i))
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

        m_segment.reset(true);

        size_t prime_idx = 0;
        while (m_primes.size() > prime_idx && m_primes[prime_idx] <= msq)
        {
            const size_t prime = m_primes[prime_idx];
            size_t pos = segment_begin / prime;
            pos += (segment_begin % prime) ? 1 : 0;
            pos *= prime;

            while (pos < segment_end)
            {
                m_segment.set_at(pos % segment_size, false);
                pos += prime;
            }

            ++prime_idx;
        }

        for (size_t i = 0; i < segment_size; ++i)
        {
            if (m_segment.get_at(i))
            {
                m_primes.push_back(segment_begin + i);
            }
        }

        const size_t primes_in_segment = m_primes.size() - prev_primes;
        m_segments.push_back(primes_in_segment);
    }

private:
    Bitset<segment_size> m_segment;
    std::vector<uint64_t> m_primes;
    std::vector<size_t> m_segments;
};

class Solution
{
public:
    int32_t countPrimes(int32_t n)
    {
        // Make it static if you feel sneaky today 😏
        PrimesStorage<64 * 8> storage;

        auto v = static_cast<uint64_t>(n);
        storage.cache_primes_up_to(v);
        auto primes = storage.get_cached_primes_view();

        return static_cast<int32_t>(
            std::distance(primes.begin(), std::ranges::lower_bound(primes, v)));
    }
};
