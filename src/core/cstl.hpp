#pragma once

#include <cstddef>

namespace Citrus {
    template<class T, unsigned int C>
    class FixedVector {
        T data[C];
        unsigned int marker = 0;

    public:
        void PushBack(T item);
        void Insert(unsigned int index, T item);

        T PopBack();
        void Clear();

        const size_t Size() { return marker; }
        const size_t Capacity() { return marker * sizeof(T); }
        const size_t FullCapacity() { return C * sizeof(T); }
    };
}