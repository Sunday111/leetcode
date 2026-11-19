#pragma once

#include <array>
#include <bit>
#include <unordered_map>

inline static constexpr int kMOD = 1'000'000'007;

[[nodiscard]] constexpr int modAdd(int a, int b)
{
    a += b;
    return a >= kMOD ? a - kMOD : a;
}

class Solution
{
public:
    template <uint8_t m, uint8_t prev_color, uint8_t idx>
    static constexpr void genColumns(uint16_t state, uint16_t*& out)
    {
        if constexpr (idx == m)
        {
            *out++ = state;  // NOLINT
            return;
        }
        else
        {
            if constexpr (prev_color != 0)
            {
                uint16_t new_state = (uint16_t{1} << (0 + 3u * idx)) | state;
                genColumns<m, 0, idx + 1>(new_state, out);
            }
            if constexpr (prev_color != 1)
            {
                uint16_t new_state = (uint16_t{1} << (1 + 3u * idx)) | state;
                genColumns<m, 1, idx + 1>(new_state, out);
            }
            if constexpr (prev_color != 2)
            {
                uint16_t new_state = (uint16_t{1} << (2 + 3u * idx)) | state;
                genColumns<m, 2, idx + 1>(new_state, out);
            }
        }
    }

    template <uint8_t m>
    static constexpr uint8_t kNumValidColumns = []
    {
        return (1 << (m - 1)) * 3;
    }();

    template <uint8_t m>
    static constexpr auto kValidColumns = []
    {
        std::array<uint16_t, kNumValidColumns<m>> columns;  // NOLINT
        uint16_t* p = columns.data();
        genColumns<m, 4, 0>(0, p);
        return columns;
    }();

    template <uint8_t m>
    static constexpr auto kTransitions = []
    {
        constexpr auto& columns = kValidColumns<m>;
        std::array<uint64_t, columns.size() + 1> transitions{};

        for (size_t i = 0; i != columns.size(); ++i)
        {
            auto from = columns[i];
            auto& tr = transitions[i];
            for (size_t j = 0; j != columns.size(); ++j)
            {
                auto to = columns[j];
                if ((from & to) == 0)
                {
                    tr |= (uint64_t{1} << j);
                }
            }
        }

        auto& fake_tr = transitions.back();
        for (size_t i = 0; i != columns.size(); ++i)
        {
            fake_tr |= (uint64_t{1} << i);
        }

        return transitions;
    }();

    template <uint8_t m>
    static int computeNumber(
        std::unordered_map<uint32_t, int>& memo,
        uint8_t prev_variant_idx,
        uint16_t n)
    {
        const uint32_t memo_key = (uint32_t{n} << 8) | prev_variant_idx;

        if (auto it = memo.find(memo_key); it != memo.end())
        {
            return it->second;
        }

        int result = 0;
        if (n == 1)
        {
            result = std::popcount(kTransitions<m>[prev_variant_idx]);
        }
        else
        {
            auto tr = kTransitions<m>[prev_variant_idx];
            auto variant_idx = static_cast<uint8_t>(std::countr_zero(tr));
            while (variant_idx != 64)
            {
                result =
                    modAdd(result, computeNumber<m>(memo, variant_idx, n - 1));
                tr &= ~(uint64_t{1} << variant_idx);
                variant_idx = static_cast<uint8_t>(std::countr_zero(tr));
            }
        }

        memo[memo_key] = result;
        return result;
    }

    template <uint8_t m>
    static int colorTheGrid(uint16_t n)
    {
        // step 1: Since m is small, generate all possible columns
        // columns encoded as uint16 - 5 groups of three bits where
        // one of them will be set to 1 representing either red (0),
        // green (1) or blue (2)
        static std::unordered_map<uint32_t, int> memo;
        memo.reserve(kNumValidColumns<m> * 2000);

        return computeNumber<m>(memo, kNumValidColumns<m>, n);
    };

    int colorTheGrid(int m, int n)
    {
        auto fn = [&]
        {
            switch (m)
            {
            case 1:
                return colorTheGrid<1>;
                break;
            case 2:
                return colorTheGrid<2>;
                break;
            case 3:
                return colorTheGrid<3>;
                break;
            case 4:
                return colorTheGrid<4>;
                break;
            default:
                return colorTheGrid<5>;
                break;
            }
        }();

        return fn(static_cast<uint16_t>(n));
    }
};
