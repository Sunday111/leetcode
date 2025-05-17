#pragma once

#include <array>
#include <string_view>

inline static constexpr int kMOD = 1'000'000'007;

constexpr int modAdd(int a, int b)
{
    return (a + b) % kMOD;
}

class Solution
{
public:
    int lengthAfterTransformations(std::string_view s, unsigned t)
    {
        std::array<int, 26> cnt{};
        for (char c : s) ++cnt[std::bit_cast<unsigned>(c - 'a')];

        unsigned num_full_cycles = t / 26;
        unsigned num_remaining_iterations = t % 26;

        for (auto i = 0u; i != num_full_cycles; ++i)
        {
            // clang-format off
            cnt[ 0] = modAdd(cnt[ 0], cnt[25]);
            cnt[25] = modAdd(cnt[25], cnt[24]);
            cnt[24] = modAdd(cnt[24], cnt[23]);
            cnt[23] = modAdd(cnt[23], cnt[22]);
            cnt[22] = modAdd(cnt[22], cnt[21]);
            cnt[21] = modAdd(cnt[21], cnt[20]);
            cnt[20] = modAdd(cnt[20], cnt[19]);
            cnt[19] = modAdd(cnt[19], cnt[18]);
            cnt[18] = modAdd(cnt[18], cnt[17]);
            cnt[17] = modAdd(cnt[17], cnt[16]);
            cnt[16] = modAdd(cnt[16], cnt[15]);
            cnt[15] = modAdd(cnt[15], cnt[14]);
            cnt[14] = modAdd(cnt[14], cnt[13]);
            cnt[13] = modAdd(cnt[13], cnt[12]);
            cnt[12] = modAdd(cnt[12], cnt[11]);
            cnt[11] = modAdd(cnt[11], cnt[10]);
            cnt[10] = modAdd(cnt[10], cnt[ 9]);
            cnt[ 9] = modAdd(cnt[ 9], cnt[ 8]);
            cnt[ 8] = modAdd(cnt[ 8], cnt[ 7]);
            cnt[ 7] = modAdd(cnt[ 7], cnt[ 6]);
            cnt[ 6] = modAdd(cnt[ 6], cnt[ 5]);
            cnt[ 5] = modAdd(cnt[ 5], cnt[ 4]);
            cnt[ 4] = modAdd(cnt[ 4], cnt[ 3]);
            cnt[ 3] = modAdd(cnt[ 3], cnt[ 2]);
            cnt[ 2] = modAdd(cnt[ 2], cnt[ 1]);
            cnt[ 1] = modAdd(cnt[ 1], cnt[ 0]);
            // clang-format on
        }

        // residual loop
        uint8_t offset = 0;
        for (auto i = 0u; i != num_remaining_iterations; ++i)
        {
            if (offset == 0)
            {
                offset = 25;
                cnt[0] = modAdd(cnt[0], cnt[25]);
            }
            else
            {
                auto b_idx = offset;
                offset = offset - 1;
                cnt[b_idx] = modAdd(cnt[b_idx], cnt[offset]);
            }
        }

        int r = 0;
        for (auto v : cnt) r = modAdd(r, v);

        return r;
    }
};
