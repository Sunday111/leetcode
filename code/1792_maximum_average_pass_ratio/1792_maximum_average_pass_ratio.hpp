#pragma once

#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr double maxAverageRatio(
        std::vector<std::vector<int>>& in_classes,
        u32 extra) noexcept
    {
        struct Class
        {
            float failed, total;
        };

        constexpr auto cmp = [](const Class& a, const Class& b)
        {
            return a.failed * b.total * (b.total + 1) <
                   b.failed * a.total * (a.total + 1);
        };

        constexpr auto cmp2 = [](const Class& a, const Class& b)
        {
            return a.failed * b.total * (b.total + 1) >
                   b.failed * a.total * (a.total + 1);
        };

        static std::array<Class, 100'001> sorted;
        u32 num_sorted = 0;
        for (auto& in_class : in_classes)
        {
            int pass = in_class[0], total = in_class[1], failed = total - pass;
            sorted[num_sorted] = {
                .failed = static_cast<float>(failed),
                .total = static_cast<float>(total),
            };
            num_sorted += failed != 0;
        }

        static std::array<Class, 100'001> heapa;
        u32 heap_size = 0;

        if (num_sorted != 0)
        {
            std::ranges::sort(
                sorted.begin(),
                std::next(sorted.begin(), num_sorted),
                cmp);

            while (extra--)
            {
                const bool take_from_heap =
                    heap_size != 0 &&
                    (num_sorted == 0 || cmp2(heapa[0], sorted[num_sorted - 1]));

                if (take_from_heap)
                {
                    std::ranges::pop_heap(
                        heapa.begin(),
                        std::next(heapa.begin(), heap_size),
                        cmp);
                }
                else
                {
                    heapa[heap_size++] = sorted[--num_sorted];
                }

                ++heapa[heap_size - 1].total;
                std::ranges::push_heap(
                    heapa.begin(),
                    std::next(heapa.begin(), heap_size),
                    cmp);
            }
        }

        double s = 0;
        for (u32 i = 0; i != num_sorted; ++i)
        {
            auto& cls = sorted[i];
            s += static_cast<double>(cls.failed / cls.total);
        }

        for (u32 i = 0; i != heap_size; ++i)
        {
            auto& cls = heapa[i];
            s += static_cast<double>(cls.failed / cls.total);
        }

        const double num_classes = static_cast<double>(in_classes.size());
        return (num_classes - s) / num_classes;
    }
};
