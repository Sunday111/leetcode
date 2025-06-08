#pragma once

#include <algorithm>
#include <vector>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

class Solution
{
public:
    using u32 = uint32_t;
    using u64 = uint64_t;
    inline static constexpr u32 kMOD = 1'000'000'007;

    struct Order
    {
        u32 price;
        u32 amount;
    };

    template <auto offers_cmp, auto queue_cmp>
    ATTR static constexpr void processOrder(
        Order order,
        std::vector<Order>& offers,
        std::vector<Order>& queue) noexcept
    {
        while (order.amount && !offers.empty() &&
               !offers_cmp(offers.front().price, order.price))
        {
            auto& offer = offers.front();
            const u32 num = std::min(order.amount, offer.amount);
            offer.amount -= num;
            order.amount -= num;

            if (offer.amount == 0)
            {
                std::ranges::pop_heap(offers, offers_cmp, &Order::price);
                offers.pop_back();
            }
        }

        if (order.amount)
        {
            queue.push_back(order);
            std::ranges::push_heap(queue, queue_cmp, &Order::price);
        }
    }

    template <size_t tag>
    static auto& get_static_data() noexcept
    {
        static std::vector<Order> v;
        v.clear();
        v.reserve(100'000);
        return v;
    }

    [[nodiscard]] static u32 getNumberOfBacklogOrders(
        const std::vector<std::vector<int>>& orders) noexcept
    {
        auto& sell = get_static_data<0>();  // min heap
        constexpr std::greater<u32> kSellCmp{};

        auto& buy = get_static_data<1>();  // max heap
        constexpr std::less<u32> kBuyCmp{};

        for (auto& ov : orders)
        {
            Order order{
                .price = static_cast<u32>(ov[0]),
                .amount = static_cast<u32>(ov[1]),
            };

            if (ov[2])
            {
                // sell
                processOrder<kBuyCmp, kSellCmp>(order, buy, sell);
            }
            else
            {
                // buy
                processOrder<kSellCmp, kBuyCmp>(order, sell, buy);
            }
        }

        u64 r1 = 0, r2 = 0;
        for (const Order& o : buy) r1 += o.amount;
        for (const Order& o : sell) r2 += o.amount;
        return (r1 + r2) % kMOD;
    }
};
