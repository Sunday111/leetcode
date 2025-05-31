#pragma once

#include <bitset>
#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int snakesAndLadders(
        std::vector<std::vector<int>>& board)
    {
        using u16 = uint16_t;
        const auto n = static_cast<u16>(board.size());
        const u16 n2 = n * n;
        const u16 last_idx = n2 - 1;

        auto index_or_link = [&](u16 i) -> u16
        {
            u16 y = i / n;
            u16 x = i % n;
            x = (y % 2) ? n - (x + 1) : x;
            y = n - (y + 1);

            if (auto link = board[y][x]; link != -1)
            {
                return (link - 1) & 0xFFFF;
            }

            return i;
        };

        std::array<u16, 400> q;  // NOLINT (no need to init)
        std::bitset<q.size()> visited;
        u16 front = 0, back = 0;

        auto enqueue = [&](u16 i)
        {
            visited[i] = true;
            q[back++] = i;
        };

        enqueue(0);

        for (int num_steps = 1; front != back; ++num_steps)
        {
            const u16 bfs_end = back;
            for (; front != bfs_end; ++front)
            {
                u16 i = q[front] + 1;
                const u16 i_end = std::min<u16>(i + 6, n2);
                for (; i != i_end; ++i)
                {
                    const u16 dst = index_or_link(i);
                    if (dst == last_idx) return num_steps;
                    if (!visited[dst]) enqueue(dst);
                }
            }
        }

        return -1;
    }
};
