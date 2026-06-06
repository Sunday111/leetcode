#include <bit>
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <vector>




template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};


using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#ifdef LC_LOCAL_BUILD

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x),
          left(left),
          right(right)
    {
    }
};

#endif




inline static constexpr auto iif =
    []<std::integral T> [[nodiscard, gnu::always_inline]] (
        bool c,
        T a,
        std::type_identity_t<T> b) noexcept -> T
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
};

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard, gnu::always_inline]] constexpr T
ptrif(bool c, T a, std::type_identity_t<T> b) noexcept
{
    return std::bit_cast<T>(
        iif(c, std::bit_cast<std::size_t>(a), std::bit_cast<std::size_t>(b)));
}

class Solution
{
    inline static TreeNode nodes[100001];

    inline static const auto node_numbers_init = []
    {
        // Init val only once
        for (u32 i = 0; TreeNode& node : nodes) node.val = cast<int>(i++);
        return 'a';
    }();

public:
    [[nodiscard]] TreeNode* createBinaryTree(
        const std::vector<std::vector<int>>& descriptions)
    {
        constexpr u32 nw = (100'001 / 64) + 1;
        static u64 roots[nw], init[nw];

        auto set_bit = [] [[gnu::always_inline]] (
                           u64 * words,
                           u32 i,
                           bool condition = true) noexcept
        {
            words[i >> 6] |= (u64{condition} << (i & 63));
        };

        auto get_bit = [] [[nodiscard, gnu::always_inline]] (
                           const u64* words,
                           u32 i) noexcept -> bool
        {
            return words[i >> 6] & (u64{1} << (i & 63));
        };

        auto clear_bit = [] [[gnu::always_inline]]
                         (u64 * words, u32 i, bool condition = true) noexcept
        {
            words[i >> 6] &= ~(u64{condition} << (i & 63));
        };

        for (auto& descr : descriptions)
        {
            u32 p_id = cast<u32>(descr[0]), c_id = cast<u32>(descr[1]);
            auto &p = nodes[p_id], &c = nodes[c_id];
            bool p_new = !get_bit(init, p_id), c_new = !get_bit(init, c_id);
            set_bit(init, p_id), set_bit(init, c_id);
            set_bit(roots, p_id, p_new);
            clear_bit(roots, c_id);
            c.left = ptrif<TreeNode*>(c_new, nullptr, c.left);
            c.right = ptrif<TreeNode*>(c_new, nullptr, c.right);
            TreeNode** t[2]{&p.right, &p.left};
            *t[descr[2]] = &c;
            *t[!descr[2]] = ptrif<TreeNode*>(p_new, nullptr, *t[!descr[2]]);
        }

        u32 ri = 0;
        for (u32 wi = 0; wi != nw; ++wi)
        {
            init[wi] = 0;
            u64 w = std::exchange(roots[wi], 0);
            bool has_bit = w != 0;
            u32 bit_index = (wi << 6) | cast<u32>(std::countr_zero(w));
            ri = std::max(ri, bit_index & -u32{has_bit});
        }

        return &nodes[ri];
    }
};

#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif
