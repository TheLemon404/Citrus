#pragma once
#include <filesystem>
#include <core/core.hpp>
#include "buffer.hpp"

namespace Citrus {
    class CITRUS_API FileSystem {
    public:
        static Buffer ReadFileBinary(const std::filesystem::path& filepath);
        static std::string ReadFileString(const std::filesystem::path& filepath);
    };
}
