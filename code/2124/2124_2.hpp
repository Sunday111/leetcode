#include <string_view>

#include "solution_name.hpp"

class LC_SOLUTION_NAME(_2)
{
public:
    static bool checkString(std::string_view s) noexcept
    {
        return s.find("ba") == std::string_view::npos;
    }
};
