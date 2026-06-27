#include <print>
#include <string>
#include <string_view>
#include <utility>

#include "print/print.hpp"

template <typename F>
class ScopeExit
{
public:
    ~ScopeExit() { func_(); }

    F func_;
};

template <typename F>
ScopeExit(F) -> ScopeExit<F>;

inline static constexpr bool kWithLog = false;

inline static std::string kk;  // NOLINT

inline static constexpr auto mlog =
    []<typename... Args>(std::format_string<Args...> fmt, Args&&... args)
{
    if constexpr (kWithLog)
    {
        print("{}", kk);
        std::println(fmt, std::forward<Args>(args)...);
    }
};

inline static constexpr auto mlog_enter_scope = []()
{
    kk += "  ";
};

inline static constexpr auto mlog_leave_scope = []()
{
    kk.resize(kk.size() - 2);
};

class Solution
{
public:
    bool isMatch(std::string_view s, std::string_view p)
    {
        return impl(s, p, 0);
    }
    static bool
    impl(std::string_view s, std::string_view p, size_t max_start) noexcept
    {
        mlog("isMatch(\"{}\", \"{}\", {})", s, p, max_start);
        auto ret = [](bool res)
        {
            mlog("-> {}", res);
            return res;
        };
        mlog_enter_scope();
        auto _ = ScopeExit(mlog_leave_scope);

        const size_t ns = s.size(), np = p.size();

        if (np == 0) return ret(ns == max_start);

        if (np > 1)
        {
            if (p.starts_with(".*"))
            {
                return ret(impl(s, p.substr(2), ns));
            }

            if (isalpha(p[0]) && p[1] == '*')
            {
                while (max_start != ns && s[max_start] == p[0])
                {
                    ++max_start;
                }
                return ret(impl(s, p.substr(2), max_start));
            }
        }

        if (ns)
        {
            if (p.starts_with("."))
            {
                max_start = std::min(max_start + 1, ns);
                return ret(impl(s.substr(1), p.substr(1), max_start - 1));
            }

            for (auto i = s.find(p[0], 0); i <= max_start;
                 i = s.find(p[0], i + 1))
            {
                if (impl(s.substr(i + 1), p.substr(1), 0))
                {
                    return ret(true);
                }
            }
        }

        return ret(false);
    }
};
