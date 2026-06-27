#include <print>

inline static constexpr auto print =
    []<typename... Args> [[gnu::always_inline]] (
        std::format_string<Args...> fmt,
        Args&&... args) noexcept
{
    std::print(fmt, std::forward<Args>(args)...);
};
