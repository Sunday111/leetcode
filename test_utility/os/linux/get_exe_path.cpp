#include <unistd.h>

#include <cerrno>

#include "os/os.hpp"

std::string OS::GetExecutablePath()
{
    std::string buffer;
    buffer.resize(256, '\0');

    while (true)
    {
        auto len = readlink("/proc/self/exe", buffer.data(), buffer.size());

        if (len < 0)
        {
            int err = errno;
            throw std::runtime_error(
                "readlink(\"/proc/self/exe\") failed: " +
                std::string(std::strerror(err)));
        }

        // If the buffer was large enough, we're done
        if (static_cast<size_t>(len) < buffer.size())
        {
            buffer.resize(static_cast<size_t>(len));
            break;
        }

        // Otherwise the result was truncated — grow and retry
        buffer.resize(buffer.size() * 2);
    }

    return buffer;
}
