#pragma once

#include <string>

#include "force_inline.hpp"

class PathHelper
{
public:
    [[nodiscard]] FORCE_INLINE static const PathHelper& Get()
    {
        return GetInternal();
    }

private:
    PathHelper();
    PathHelper(const PathHelper&) = delete;

    [[nodiscard]] static PathHelper& GetInternal()
    {
        static PathHelper instance;
        return instance;
    }

    std::string executable_path;
    std::string executable_dir;
};
