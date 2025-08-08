#include "cstl.hpp"

#include "log.hpp"

namespace Citrus {
    template<typename T, unsigned int C>
    void FixedVector<T, C>::PushBack(T item) {
        data[marker] = item;
        marker++;
    }

    template<class T, unsigned int C>
    void FixedVector<T, C>::Insert(unsigned int index, T item) {
        if (index > marker) {
            CITRUS_CORE_FATAL("cannot Insert() beyond the marker index");
            throw(std::runtime_error("cannot Insert() beyond the marker index"));
        }

        marker++;

        for (int i = index; i < marker - 1; i++) {
            data[i + 1] = data[i];
        }

        data[index] = item;
    }

    template<typename T, unsigned int C>
    T FixedVector<T, C>::PopBack() {
        if (marker == 0) {
            CITRUS_CORE_FATAL("cannot Pop() an empty fixed vector");
            throw(std::runtime_error("cannot Pop() an empty fixed vector"));
        }

        marker--;
        return data[marker];
    }

    template<class T, unsigned int C>
    void FixedVector<T, C>::Clear() {
        marker = 0;
    }
}
