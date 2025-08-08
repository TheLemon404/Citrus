#pragma once
#include <filesystem>

#include "buffer.hpp"

namespace Citrus {
    class FileSystem {
    public:
        static Buffer ReadFileBinary(const std::filesystem::path& filepath);
    };
}
