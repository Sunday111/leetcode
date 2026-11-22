#include <string_view>

#include "solution_name.hpp"

class LC_SOLUTION_NAME()
{
public:
    bool checkString(std::string_view s) const noexcept
    {
        return s.find("ba") == std::string_view::npos;
    }
};
