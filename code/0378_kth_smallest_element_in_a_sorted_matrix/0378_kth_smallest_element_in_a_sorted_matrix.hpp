#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    static int kthSmallest(std::vector<std::vector<int>>& matrix, int k)
    {
        int n = static_cast<int>(matrix.size());
        std::array<int, 300> fe{};

        int start = 0;

        while (true)
        {
            int v = std::numeric_limits<int>::max();
            int vr = start, vc = n;
            for (int row = start; row != n; ++row)
            {
                int col = fe[static_cast<uint32_t>(row)];
                if (col == n)
                {
                    if (row == start) ++start;
                    continue;
                }

                if (col >= vc) continue;

                int vv = matrix[static_cast<uint32_t>(row)]
                               [static_cast<uint32_t>(col)];
                if (vv < v)
                {
                    v = vv;
                    vc = col;
                    vr = row;

                    if (vc == 0) break;
                }
            }

            if (--k == 0)
            {
                return v;
            }

            ++fe[static_cast<uint32_t>(vr)];
        }

        std::unreachable();
    }
};
