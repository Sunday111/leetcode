#pragma once

#include <utility>

template <typename Node>
[[gnu::always_inline]] constexpr unsigned make_vine(Node* grand) noexcept
{
    unsigned count = 0;
    auto tmp = grand->right;

    while (tmp)
    {
        if (tmp->left)
        {
            auto old = std::exchange(tmp, tmp->left);
            old->left = std::exchange(tmp->right, old);
            grand->right = tmp;
        }
        else
        {
            count++;
            grand = std::exchange(tmp, tmp->right);
        }
    }

    return count;
}
