/*
    Given a matrix with n rows and m columns, the following operation can be
   performed on it:
    - select non-empty row of the matrix
    - remove an element either from the start or end of the selected row.

    Note: if the first (starting) element of a row is removed, the element
   adjacent to it becomes the starting element on that row. A similar logic
   applies to removing the last element of the row.

   Find the maximum possible sum of elements removed after exactly k operations.

   1 <= n, m <= 100
   1 <= matrix[i][j] <= 10^5
   1 <= k <= min(n*m, 2000)
 */

#include <algorithm>
#include <mdspan>
#include <numeric>
#include <span>

#include "integral_aliases.hpp"

template <typename T>
using MatrixView = std::mdspan<T, std::dextents<u32, 2>>;

template <typename T>
[[nodiscard]] auto constexpr inline get_row(T matrix, u32 row) noexcept
{
    return std::span{&matrix[row, 0], matrix.extent(1)};
}

class Solution
{
public:
    MatrixView<const u32> matrix;
    MatrixView<const u32> t;  // t[a][c] - max sum of c removed from matrix[a]
    u32 n = 0;                // number of rows
    u32 m = 0;                // number of columns
    u32 p = 0;  // maximum removals from a single row (k can be less than m)
    u32 k = 0;  // total number of removals

    void initCommon(MatrixView<const u32> matrix_, u32 k_)
    {
        matrix = matrix_;
        n = matrix.extent(0), m = matrix.extent(1);
        p = std::min(k = k_, m);  // max removals from a single row

        // Initialize max sums per row array t
        static u32 t_data[101 * 100];
        MatrixView<u32> t_local{t_data, n, p + 1};
        std::fill_n(&t_local[0, 0], t_local.size(), 0);
        t = t_local;

        for (u32 row_index = 0; row_index != n; ++row_index)
        {
            std::span row = get_row(matrix, row_index);
            u32 prefix_sum[101];
            prefix_sum[0] = 0;

            std::inclusive_scan(row.begin(), row.end(), prefix_sum + 1);

            for (u32 total_removals = 1; total_removals <= p; ++total_removals)
            {
                u32& x = t_local[row_index, total_removals] = 0;

                for (u32 front = 0, back = total_removals;
                     front <= total_removals;
                     ++front, --back)
                {
                    u32 sum_front = prefix_sum[front];
                    u32 sum_back = prefix_sum[m] - prefix_sum[m - back];
                    x = std::max(sum_front + sum_back, x);
                }
            }
        }
    }

    [[nodiscard]] u32 maximumSumBrute(
        MatrixView<const u32> matrix_,
        u32 k_) noexcept
    {
        initCommon(matrix_, k_);

        return [this](this auto dfs, u32 row_index, u32 max_removals) -> u32
        {
            if (row_index == n) return 0;

            u32 r = 0;
            for (u32 rem = 0; rem <= std::min(m, max_removals); ++rem)
            {
                r = std::max(
                    r,
                    t[row_index, rem] + dfs(row_index + 1, max_removals - rem));
            }

            return r;
        }(0, k);
    }

    [[nodiscard]] u32 maximumSumMemo(
        MatrixView<const u32> matrix_,
        u32 k_) noexcept
    {
        initCommon(matrix_, k_);
        static u32 memo[100][2001];
        std::fill_n(memo[0], 100 * 2001, 0xFFFFFFFF);

        return [this](this auto dfs, u32 row_index, u32 max_removals) -> u32
        {
            if (row_index == n) return 0;

            u32& r = memo[row_index][max_removals];
            if (r == 0xFFFFFFFF)
            {
                r = 0;
                for (u32 rem = 0; rem <= std::min(m, max_removals); ++rem)
                {
                    r = std::max(
                        r,
                        t[row_index, rem] +
                            dfs(row_index + 1, max_removals - rem));
                }
            }

            return r;
        }(0, k);
    }

    [[nodiscard]] u32 maximumSum(MatrixView<const u32> matrix_, u32 k_) noexcept
    {
        initCommon(matrix_, k_);

        static u32 dp_data[2 * 2001 * 101];
        MatrixView<u32> curr{dp_data, k + 1, p + 1};
        MatrixView<u32> prev{dp_data + curr.size(), curr.extents()};

        std::ranges::fill(get_row(curr, 0), 0);

        for (u32 c = 1; c <= p; ++c)
        {
            auto r = get_row(curr, c);
            std::ranges::fill(r.first(c - 1), 0);
            std::ranges::fill(r.subspan(c), t[0, c]);
        }

        for (u32 b = p + 1; b <= k; ++b)
        {
            std::ranges::fill(get_row(curr, b), 0);
        }

        for (u32 row_index = 1; row_index != n; ++row_index)
        {
            std::swap(curr, prev);
            for (u32 b = 0; b <= k; ++b)
            {
                curr[b, 0] = prev[b, p];
                const u32 last_c = std::min(b, m), lim_c = last_c + 1;

                for (u32 c = 1; c != lim_c; ++c)
                {
                    curr[b, c] = std::max(
                        curr[b, c - 1],
                        prev[b - c, p] + t[row_index, c]);
                }
                std::ranges::fill(
                    get_row(curr, b).subspan(lim_c),
                    curr[b, last_c]);
            }
        }

        return curr[k, p];
    }
};
