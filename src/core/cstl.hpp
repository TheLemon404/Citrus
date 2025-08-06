#pragma once

namespace Citrus {
    template<class T, unsigned int C>
    class FixedVector {
        T data[C];
        unsigned int marker = 0;

    public:
        void Append(T item);
        T Pop();
    };
}