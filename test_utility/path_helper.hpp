#pragma once

#include <string>

class PathHelper
{
public:
    [[nodiscard, gnu::always_inline]] inline static const PathHelper& Get()
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
