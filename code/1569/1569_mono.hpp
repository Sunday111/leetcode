#include <array>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    [[gnu::always_inline]] constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator+(
        const ModInt& rhs) const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator-=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator-(
        const ModInt& rhs) const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator*=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
        const ModInt& rhs) const noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt inverse() const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator/=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator/(
        const ModInt& rhs) const noexcept;

    template <std::unsigned_integral Exp>
    [[nodiscard, gnu::always_inline]] constexpr ModInt pow(
        Exp exp) const noexcept;

    u32 value = 0;
};

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::inverse()
    const noexcept
{
    auto a = value;
    u32 x0 = 1, x1 = 0, mod = kMOD;
    while (a)
    {
        u32 q = mod / a;
        u32 r = mod % a;
        u32 x2 = x1 - q * x0;
        mod = a;
        a = r;
        x1 = x0;
        x0 = x2;
    }
    return {(x1 + kMOD) % kMOD};
}

template <typename To>
inline static constexpr auto cast =
    []<typename From> [[nodiscard, gnu::always_inline]] (From&& v) noexcept
{
    return static_cast<To>(std::forward<From>(v));
};

[[gnu::always_inline]] constexpr ModInt& ModInt::operator*=(
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= value;
    if (v >= kMOD) v %= kMOD;
    value = cast<u32>(v);
    return *this;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::operator*(
    const ModInt& rhs) const noexcept
{
    auto copy = *this;
    copy *= rhs;
    return copy;
}

[[gnu::always_inline]] constexpr ModInt& ModInt::operator/=(
    const ModInt& rhs) noexcept
{
    return *this *= rhs.inverse();
}

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::operator/(
    const ModInt& rhs) const noexcept
{
    auto copy = *this;
    copy /= rhs;
    return copy;
}

template <std::size_t lim_factorial>
constexpr ModInt
binomial_coefficient(const std::array<ModInt, lim_factorial>& f, u32 n, u32 k)
{
    assert(n >= k);
    return f[n] / (f[k] * f[n - k]);
}

template <u32 max_index>
inline constexpr auto factorials_mods()
{
    std::array<ModInt, max_index + 1> r;  // NOLINT
    r[0] = ModInt{1};
    for (u32 i = 1; i != r.size(); ++i)
    {
        r[i] = r[i - 1] * ModInt{i};
    }

    return r;
}
#ifndef LC_LOCAL_BUILD
auto init = []()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 'c';
}();
#endif

struct Node
{
    u16 v{};
    u16 l = 0xFFFF;
    u16 r = 0xFFFF;
};

class Solution
{
public:
    inline static Node nodes[1001];
    inline static u16 q[1001];
    inline static constexpr auto factorials = factorials_mods<1000>();

    u32 numOfWays(std::vector<int>& nums)
    {
        u16 next_node = 0;

        Node* root = &nodes[next_node++];
        *root = {};
        root->v = nums[0] & 0xFFFF;

        auto insert = [&](this auto&& f, Node* x, u16 v) -> void
        {
            u16& t = v < x->v ? x->l : x->r;
            if (t != 0xFFFF)
            {
                f(&nodes[t], v);
            }
            else
            {
                t = next_node++;
                (nodes[t] = {}).v = v;
            }
        };

        for (size_t i = 1; i != nums.size(); ++i)
        {
            insert(root, nums[i] & 0xFFFF);
        }

        auto [_, x] = [&](this auto&& dfs,
                          u16 node_id) -> std::pair<u16, ModInt>
        {
            if (node_id == 0xFFFF) return {0, {1}};

            auto [num, ways] = dfs(nodes[node_id].l);
            auto [rnum, rways] = dfs(nodes[node_id].r);
            num += rnum;
            ways *= rways;

            if ((!!num) & (num != rnum))
            {
                ways *= binomial_coefficient(factorials, num, rnum);
            }

            return {num + 1, ways};
        }(0);

        return x.value - 1;
    }
};
