#include "files.hpp"
#include <fstream>

#include "log.hpp"

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

    std::string FileSystem::ReadFileString(const std::filesystem::path& filepath) {
        CITRUS_CORE_INFO("Attempting to load file: {}", filepath.string());

        // Check if file exists
        if (!std::filesystem::exists(filepath)) {
            CITRUS_CORE_ERROR("File does not exist: {}", filepath.string());
            return "";
        }

        // Check current working directory
        CITRUS_CORE_INFO("Current working directory: {}", std::filesystem::current_path().string());

        std::ifstream file(filepath, std::ios::in | std::ios::binary);

        if (!file.is_open()) {
            CITRUS_CORE_ERROR("Unable to open file {}", filepath.string());
            return "";
        }

        // Get file size first
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        CITRUS_CORE_INFO("File size: {} bytes", size);

        if (size == 0) {
            CITRUS_CORE_ERROR("File is empty: {}", filepath.string());
            return "";
        }

        // Read entire file into string using iterators
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

        CITRUS_CORE_INFO("File {} loaded successfully ({} bytes)", filepath.string(), content.size());

        // Debug: show first 100 characters
        if (content.size() > 0) {
            std::string preview = content.substr(0, std::min<size_t>(100, content.size()));
            CITRUS_CORE_INFO("File preview: {}", preview);
        }

        return content;
    }
}
