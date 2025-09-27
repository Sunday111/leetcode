#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <span>
#include <vector>

template <std::integral T>
[[nodiscard]] static constexpr T ceil_div(T a, T b) noexcept
{
    return ((a + b) - 1) / b;
}

class Solution
{
public:
    using u64 = int64_t;
    using u32 = uint32_t;
    struct RankInfo
    {
        static u64 calc(u64 n, u64 rank) { return n * n * rank; }

        void Init() { finish_time_1 = calc(cars + 1, rank); }

        void AddCar()
        {
            ++cars;
            Init();
        }

        [[nodiscard]] constexpr u64 GetFinishTime() const noexcept
        {
            return calc(cars, rank);
        }

        u32 rank = 0;
        u32 mechanics = 0;
        u32 cars = 0;
        u64 finish_time_1 = 0;
    };

    [[nodiscard]] inline static constexpr u64 repairCars(
        std::vector<int>& ranks,
        u32 cars) noexcept
    {
        std::array<RankInfo, 101> info;
        for (int rank : ranks) ++info[rank & 0xFF].mechanics;

        u32 num_ranks = 0;
        for (u32 i = 0; i != 101; ++i)
        {
            if (info[i].mechanics)
            {
                auto& r = info[num_ranks++];
                r = info[i];
                r.rank = i;
                r.Init();
            }
        }

        const auto heap = std::span{info}.first(num_ranks);
        auto heap_op = [&]<typename Op>(Op&& op)
        {
            std::forward<Op>(
                op)(heap, std::greater{}, &RankInfo::finish_time_1);
        };

        if (heap.size() == 1)
        {
            return RankInfo::calc(
                ceil_div(cars, heap[0].mechanics),
                heap[0].rank);
        }

        heap_op(std::ranges::make_heap);
        while (cars)
        {
            heap_op(std::ranges::pop_heap);

            auto& curr = heap.back();
            auto& next = heap.front();

            u32 a = curr.cars;
            u32 da = std::max(
                         a + 1,
                         static_cast<u32>(
                             static_cast<float>(next.cars) *
                             std::sqrtf(
                                 static_cast<float>(next.rank / curr.rank)))) -
                     a;

            cars -= std::min(cars, da * curr.mechanics);
            curr.cars += da;
            curr.Init();

            heap_op(std::ranges::push_heap);
        }

        return std::ranges::max_element(
                   heap,
                   std::less{},
                   &RankInfo::GetFinishTime)
            ->GetFinishTime();
    }
};
