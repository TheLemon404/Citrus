#pragma once
#include <cstdint>
#include <string.h>

namespace Citrus {
    struct Buffer {
        uint8_t* data = nullptr;
        uint64_t size = 0;

        Buffer() = default;

        Buffer(uint64_t size) {
            Allocate(size);
        }

        static Buffer Copy(Buffer other) {
            Buffer result(other.size);
            memcpy(result.data, other.data, other.size);
            return result;
        }

        void Allocate(uint64_t size) {
            Release();
            data = new uint8_t[size];
            this->size = size;
        }

        void Release() {
            delete[] data;
            data = nullptr;
            size = 0;
        }

        template<typename T>
        T* GetDataAs() {
            return (T*)data;
        }

        operator bool() const {
            return (bool)data;
        }
    };
}
