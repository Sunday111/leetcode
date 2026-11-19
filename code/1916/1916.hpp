#pragma once

#include <array>
#include <span>
#include <vector>

inline static constexpr uint32_t kMOD = 1'000'000'007;

constexpr uint32_t modMul(uint64_t a, uint64_t b)
{
    return (a * b) % kMOD;
}

constexpr uint32_t modAdd(uint64_t a, uint64_t b)
{
    return (a + b) % kMOD;
}

constexpr uint32_t modInverse(uint32_t a)
{
    uint32_t x0 = 1, x1 = 0, mod = kMOD;
    while (a != 0)
    {
        uint32_t q = mod / a;
        uint32_t r = mod % a;
        uint32_t x2 = x1 - q * x0;
        mod = a;
        a = r;
        x1 = x0;
        x0 = x2;
    }
    return (x1 + kMOD) % kMOD;
}

constexpr uint32_t modDiv(uint64_t a, uint32_t b)
{
    return modMul(a, modInverse(b));
}

template <typename T, size_t... sizes>
inline constexpr auto joinArrays(const std::array<T, sizes>&... arrays)
{
    constexpr size_t total_size = (0 + ... + sizes);
    std::array<T, total_size> r;  // NOLINT
    uint32_t num_added = 0;

    (
        [&](const auto& arr)
        {
            std::ranges::copy(arr, std::next(r.begin(), num_added));
            num_added += arr.size();
        }(arrays),
        ...);
    return r;
}

template <
    const uint32_t* src_values,
    uint32_t num_src_values,
    uint32_t step,
    uint32_t iteration>
struct PrecomputedInverseI
{
    static inline constexpr auto kValues = []()
    {
        constexpr size_t cnt =
            step * (iteration + 1) > num_src_values
                ? (step - ((step * (iteration + 1)) % num_src_values))
                : step;
        std::array<uint32_t, cnt> r;  // NOLINT

        for (uint32_t i = 0; i != r.size(); ++i)
        {
            r[i] = modInverse(src_values[i + step * iteration]);  // NOLINT
        }

        return r;
    }();
};

template <const uint32_t* src_values, uint32_t num_src_values, uint32_t step>
struct PrecomputedInverse
{
    static constexpr uint32_t kNumIters =
        (num_src_values / step) + (((num_src_values % step) == 0) ? 0 : 1);
    static inline constexpr auto kValues =
        []<size_t... iter>(std::index_sequence<iter...>)
    {
        return joinArrays(
            PrecomputedInverseI<src_values, num_src_values, step, iter>::
                kValues...);
    }(std::make_index_sequence<kNumIters>());
};

class Solution
{
public:
    inline static constexpr auto kInvalidNode =
        std::numeric_limits<uint32_t>::max();

    static inline constexpr auto kPrecomputedFactorials1 = []
    {
        std::array<uint32_t, 50001> fact;  // NOLINT
        fact[0] = 1;
        for (uint32_t i = 1; i != fact.size(); i++)
        {
            fact[i] = modMul(fact[i - 1], i);
        }
        return fact;
    }();

    static inline constexpr auto kPrecomputedFactorials2 = []
    {
        std::array<uint32_t, 50001> fact;  // NOLINT
        fact[0] = modMul(
            kPrecomputedFactorials1.back(),
            kPrecomputedFactorials1.size());
        for (uint32_t i = 1; i != fact.size(); i++)
        {
            fact[i] = modMul(
                fact[i - 1],
                i + static_cast<uint32_t>(kPrecomputedFactorials1.size()));
        }
        return fact;
    }();

    static constexpr auto kFactorials =
        joinArrays(kPrecomputedFactorials1, kPrecomputedFactorials2);

    static inline constexpr auto kFactInverse =
        PrecomputedInverse<kFactorials.data(), kFactorials.size(), 6000>::
            kValues;

    struct NodeInfo
    {
        uint32_t child = kInvalidNode;
        uint32_t sibling = kInvalidNode;
    };

    std::vector<NodeInfo> nodes;

    std::pair<uint32_t, uint32_t> dfs(uint32_t node)
    {
        if (node == kInvalidNode) return {0, 0};

        uint32_t numerator = 1;
        uint32_t size = 0;

        for (uint32_t child = nodes[node].child; child != kInvalidNode;
             child = nodes[child].sibling)
        {
            auto [child_ways_to_build, child_size] = dfs(child);
            numerator = modMul(numerator, child_ways_to_build);
            nodes[child].child = child_size;
            size += child_size;
        }

        for (uint32_t child = nodes[node].child; child != kInvalidNode;
             child = nodes[child].sibling)
        {
            numerator = modMul(numerator, kFactInverse[nodes[child].child]);
        }

        auto ways_to_build = modMul(numerator, kFactorials[size]);

        return {ways_to_build, size + 1};
    }

    int32_t waysToBuildRooms(std::span<const int32_t> parents)
    {
        nodes.clear();
        nodes.resize(parents.size());

        // Gather nodes info for dfs
        for (size_t node = 1; node != parents.size(); ++node)
        {
            uint32_t parent = std::bit_cast<uint32_t>(parents[node]);
            nodes[node].sibling = std::exchange(nodes[parent].child, node);
        }

        return static_cast<int32_t>(dfs(0).first);
    }
};
