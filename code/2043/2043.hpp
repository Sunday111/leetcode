#pragma once

#include <utility>
#include <vector>

class Bank
{
public:
    using u32 = uint32_t;
    using i64 = long long;  // NOLINT
    explicit Bank(std::vector<i64>& balance_) : balance{std::move(balance_)} {}

    static constexpr u32 kInvalidIndex = std::numeric_limits<u32>::max();
    [[nodiscard]] constexpr u32 toIndex(int account) const noexcept
    {
        if (account < 1) return kInvalidIndex;
        u32 i = std::bit_cast<u32>(account - 1);
        if (std::cmp_greater_equal(i, balance.size())) return kInvalidIndex;
        return i;
    }

    [[nodiscard]] constexpr bool
    transfer(int account1, int account2, i64 money) noexcept
    {
        if (auto i2 = toIndex(account2); i2 != kInvalidIndex)
        {
            auto& v2 = balance[i2];
            if (withdraw(account1, money))
            {
                v2 += money;
                return true;
            }
        }

        return false;
    }

    [[nodiscard]] constexpr bool deposit(int account, i64 money) noexcept
    {
        if (auto i = toIndex(account); i != kInvalidIndex)
        {
            balance[i] += money;
            return true;
        }

        return false;
    }

    [[nodiscard]] bool withdraw(int account, i64 money) noexcept
    {
        if (auto i = toIndex(account); i != kInvalidIndex)
        {
            auto& v = balance[i];
            if (v >= money)
            {
                v -= money;
                return true;
            }
        }

        return false;
    }

    std::vector<i64> balance;
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */
