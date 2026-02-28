#include "path_helper.hpp"

#include <filesystem>
#include <print>

#include "os/os.hpp"

namespace fs = std::filesystem;

PathHelper::PathHelper()
{
    auto& instance = GetInternal();

    fs::path path = fs::canonical(OS::GetExecutablePath());

    instance.executable_path = path.string();
    instance.executable_dir = path.parent_path().string();
    std::println("Executable path: {}", instance.executable_path);
    std::println("Executable dir: {}", instance.executable_dir);
}
