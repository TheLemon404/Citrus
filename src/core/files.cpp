#include "files.hpp"
#include <fstream>

namespace Citrus {
    Buffer FileSystem::ReadFileBinary(const std::filesystem::path& filepath) {
        std::ifstream stream = std::ifstream(filepath, std::ios::binary | std::ios::ate);

        if (!stream) {
            return Buffer();
        }

        std::streampos end = stream.tellg();
        stream.seekg(0, std::ios::beg);
        uint64_t size = end - stream.tellg();

        if (size == 0) {
            return Buffer();
        }

        Buffer buffer = Buffer(size);
        stream.read(buffer.GetDataAs<char>(), size);
        stream.close();
        return buffer;
    }
}
