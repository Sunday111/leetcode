#pragma once

#include <algorithm>
#include <array>
#include <span>
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

        auto classes = [&]()
        {
            static std::array<Class, 100'001> classes_array;
            u32 n = 0;
            for (auto& in_class : in_classes)
            {
                int pass = in_class[0], total = in_class[1],
                    failed = total - pass;
                classes_array[n] = {
                    .failed = static_cast<float>(failed),
                    .total = static_cast<float>(total),
                };
                n += failed != 0;
            }
            return std::span{classes_array}.first(n);
        }();

        if (!classes.empty())
        {
            constexpr auto cmp = [](const Class& a, const Class& b)
            {
                return a.failed * b.total * (b.total + 1) <
                       b.failed * a.total * (a.total + 1);
            };

            std::ranges::make_heap(classes, cmp);

            while (extra)
            {
                std::ranges::pop_heap(classes, cmp);
                auto& best = classes.back();
                ++best.total;
                --extra;
                std::ranges::push_heap(classes, cmp);
            }
        }

        double s = 0;
        for (auto& cls : classes)
        {
            s += static_cast<double>(cls.failed / cls.total);
        }

        const double n = static_cast<double>(in_classes.size());
        return (n - s) / n;
    }
};
