#include <algorithm>
#include <ranges>
#include <vector>


class Solution
{
public:
    using u32 = uint32_t;
    inline static u32 indices_sorted_by_value[100'001];
    inline static u32 sorted_indices_buf[100'001];
    inline static u32 tmp[100'001];
    std::vector<int> lexicographicallySmallestArray(
        std::vector<int>& nums,
        u32 limit)
    {
        auto* data = reinterpret_cast<u32*>(nums.data());
        const u32 n = static_cast<u32>(nums.size());

        // copy input array into tmp
        std::ranges::copy_n(data, n, tmp);

        // Make indices array, sort it values they point to
        std::ranges::copy(std::views::iota(0u, n), indices_sorted_by_value);
        std::ranges::sort(
            indices_sorted_by_value | std::views::take(n),
            std::less{},
            [] [[gnu::always_inline]] (u32 i) noexcept -> u32
            { return tmp[i]; });

        // after sort the array begins with joint idx group of [10 18 0]
        // it means a[0] gets value of tmp[10]
        //          a[10] gets value of tmp[18]
        //          a[18] gets value of tmp[0]
        // so I need to sort indices themseves in a separate buffer
        //

        auto handle_connected_indices = [data](u32 begin, u32 end)
        {
            const u32 group_size = end - begin;
            // copy the range into `sorted_indices_buf`
            std::copy_n(
                indices_sorted_by_value + begin,
                group_size,
                sorted_indices_buf);

            // sort sorted_indices_buf
            std::sort(sorted_indices_buf, sorted_indices_buf + group_size);

            for (u32 t = 0; t != group_size; ++t)
            {
                u32 dst = sorted_indices_buf[t];
                u32 src = indices_sorted_by_value[begin + t];
                data[dst] = tmp[src];
            }
        };

        // let i and j be indinces in `indices_sorted_by_value`
        u32 i = 0, j = 1;
        while (j != n)
        {
            u32 delta = tmp[indices_sorted_by_value[j]] -
                        tmp[indices_sorted_by_value[j - 1]];
            if (delta > limit)
            {
                handle_connected_indices(i, j);
                i = j;
            }

            ++j;
        }

        handle_connected_indices(i, j);

        return std::move(nums);
    }
};
