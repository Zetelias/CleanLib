//
// Created by zetelias on 16/05/24.
//

#ifndef SLICE_H
#define SLICE_H
#include <numeric>

#include "IntegerTypedefs.h"

/**
 * @brief A non owned view into an array.
 *
 * @note Have clear ownership. If for example, you have a Slice into a DynamicArray,
 * and you delete the DynamicArray, or it gets outs of scope, or the array resizes, the Slice will be invalid.
 * This is just a pointer and a length, and it's up to you to manage the lifetime of the data.
 *
 * @tparam T The type of the elements in the slice.
 */
template <typename T>
class Slice {
protected:
    T* data;
    usize length;
private:
    constexpr Slice(T* data, usize length) : data(data), length(length) {
    }
    constexpr Slice(T* data, T* end) : data(data), length(end - data) {
    }
public:
    Slice() = delete;

    constexpr static Slice New(T* data, usize length) {
        return Slice{data, length};
    }

    constexpr static Slice NewFromIter(T* start, T* end) {
        return Slice{start, end - start};
    }

    [[nodiscard]] constexpr usize Length() const {
        return length;
    }

    constexpr auto begin() {
        return data;
    }

    constexpr auto end() {
        return data + length;
    }

    constexpr auto begin() const {
        return data;
    }

    constexpr auto end() const {
        return data + length;
    }

    constexpr T Sum() {
        static_assert(std::is_arithmetic_v<T>, "T must be an arithmetic type.");
        return std::accumulate(begin(), end(), T{});
    }
};

#endif //SLICE_H
