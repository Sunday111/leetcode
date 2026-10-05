#include <bit>
#include <utility>

#include "binary_tree/make_vine.hpp"

namespace dsw_impl
{

template <typename Node>
[[gnu::always_inline]] constexpr void rotate(Node* grand, unsigned m) noexcept
{
    for (auto tmp = grand->right; m--;)
    {
        auto old = std::exchange(tmp, tmp->right);
        grand->right = tmp;
        old->right = tmp->left;
        tmp->left = old;
        grand = std::exchange(tmp, tmp->right);
    }
}

template <typename Node>
[[gnu::always_inline]] constexpr auto balanceBST(Node* root) noexcept
{
    Node dummy{0};
    dummy.right = root;
    unsigned n = make_vine(&dummy);
    unsigned m = (1u << (std::bit_width(n + 1u) - 1)) - 1u;
    rotate(&dummy, n - m);
    while (m >>= 1) rotate(&dummy, m);
    return dummy.right;
}
}  // namespace dsw_impl
