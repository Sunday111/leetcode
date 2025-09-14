#include <functional>
#include <utility>

#include "functional.hpp"

template <typename Inner, typename Outer>
static constexpr auto compose(Outer&& inner, Inner&& outer) noexcept
{
    if constexpr (std::is_lvalue_reference_v<Inner>)
    {
        if constexpr (std::is_lvalue_reference_v<Outer>)
        {
            return [&]<typename... Args>(Args&&... args) -> decltype(auto)
            {
                return (outer(inner(std::forward<Args>(args)...)));
            };
        }
        else
        {
            return [&, inner_ = std::forward<Outer>(inner)]<typename... Args>(
                       Args&&... args) -> decltype(auto)
            {
                return (outer(inner_(std::forward<Args>(args)...)));
            };
        }
    }
    else
    {
        if constexpr (std::is_lvalue_reference_v<Outer>)
        {
            return [&, outer_ = std::forward<Inner>(outer)]<typename... Args>(
                       Args&&... args) -> decltype(auto)
            {
                return (outer_(inner(std::forward<Args>(args)...)));
            };
        }
        else
        {
            return [outer_ = std::forward<Inner>(outer),
                    inner_ = std::forward<Outer>(inner)]<typename... Args>(
                       Args&&... args) -> decltype(auto)
            {
                return (outer_(inner_(std::forward<Args>(args)...)));
            };
        }
    }
}

namespace test
{

// Both are rvalues
static_assert(
    compose(
        std::bind_front(std::multiplies{}, 2),
        std::bind_front(std::plus{}, -5))(3) == 1);

inline constexpr auto minus5 = std::bind_front(plus, -5);
inline constexpr auto mul2 = std::bind_front(mul, 2);
static_assert(compose(mul2, minus5)(3) == 1);

}  // namespace test
