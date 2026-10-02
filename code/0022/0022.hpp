#include <algorithm>
#include <array>
#include <span>
#include <string>
#include <vector>

#include "catalan_64.hpp"
#include "namespaces.hpp"
#include "uint_for_value.hpp"

template <u32 N>
struct Data : Data<N - 1>
{
    using Base = Data<N - 1>;
    using SizeIndex = UintForValue<N>;

    std::array<char, 2 * N * kCatalan64[N]> storage{};

    consteval Data()
    {
        const Base& base = *this;
        auto* output = storage.data();
        stdr::for_each(
            stdv::iota(SizeIndex{0}, SizeIndex{N}),
            [&](SizeIndex gap)
            {
                auto left = base[gap];
                auto right_n = static_cast<SizeIndex>(N - gap - 1);
                auto right = base[right_n];
                stdr::for_each(
                    stdv::cartesian_product(
                        stdv::iota(u64{0}, kCatalan64[gap]),
                        stdv::iota(u64{0}, kCatalan64[right_n])),
                    [&](auto pair)
                    {
                        auto [l, r] = pair;
                        *output++ = '(';
                        output = stdr::copy(
                                     left.subspan(l * 2 * gap, 2 * gap),
                                     output)
                                     .out;
                        *output++ = ')';
                        output =
                            stdr::copy(
                                right.subspan(r * 2 * right_n, 2 * right_n),
                                output)
                                .out;
                    });
            });
    }

    constexpr std::span<const char> operator[](SizeIndex n) const noexcept
    {
        [[assume(n <= N)]];
        if (n == N) return storage;
        return static_cast<const Base&>(*this)[n];
    }
};

template <>
struct Data<0>
{
    using SizeIndex = UintForValue<0>;

    constexpr std::span<const char> operator[](SizeIndex n) const noexcept
    {
        [[assume(n == 0)]];
        return {};
    }
};

class Solution
{
public:
    inline static constexpr u8 kMaxN = 8;
    inline static constexpr Data<kMaxN> data;

    std::vector<std::string> generateParenthesis(
        Data<kMaxN>::SizeIndex n) const noexcept
    {
        return data[n] | stdv::chunk(2 * n) |
               stdv::transform(
                   [](auto chars)
                   { return std::string(chars.data(), chars.size()); }) |
               stdr::to<std::vector>();
    }
};
