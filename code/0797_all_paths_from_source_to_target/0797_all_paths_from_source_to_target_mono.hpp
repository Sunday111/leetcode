#include <cstdint>
#include <span>
#include <utility>
#include <vector>




#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

template <typename To, typename From, std::size_t extent = std::dynamic_extent>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static auto reinterpret_range(
    std::span<From, extent> in) noexcept
{
    return std::span<To, extent>{
        reinterpret_cast<To*>(in.data()),  // NOLINT
        in.size()};
}

template <typename To, typename From, typename Allocator>
    requires(sizeof(To) == sizeof(From))
[[nodiscard]] FORCE_INLINE static std::span<To> reinterpret_range(
    std::vector<From, Allocator>& v) noexcept
{
    return reinterpret_range<To>(std::span{v});
}



using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Solution
{
    u32 target{};
    std::vector<u32> curr;
    std::vector<std::vector<u32>> result;
    std::span<const std::vector<u32>> g;

    constexpr void dfs(u32 i) noexcept
    {
        curr.push_back(i);

        if (i == target)
        {
            result.push_back(curr);
        }
        else
        {
            for (u32 j : g[i]) dfs(j);
        }

        curr.pop_back();
    }

public:
    [[nodiscard]] constexpr std::vector<std::vector<int>> allPathsSourceTarget(
        const std::vector<std::vector<int>>& graph) noexcept
    {
        target = static_cast<u32>(graph.size() - 1);
        g = reinterpret_cast<const std::vector<std::vector<u32>>&>(graph);
        dfs(0);
        return std::move(
            reinterpret_cast<std::vector<std::vector<int>>&>(result));
    }
};
