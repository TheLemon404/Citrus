#include "cstl.hpp"

#include "log.hpp"

namespace Citrus {
    template<typename T, unsigned int C>
    void FixedVector<T, C>::Append(T item) {
        data[marker] = item;
        marker++;
    }

    template<typename T, unsigned int C>
    T FixedVector<T, C>::Pop() {
        if (marker == 0) {
            CITRUS_CORE_FATAL("cannot Pop() an empty fixed vector");
        }

        marker--;
        return data[marker];
    }
}
