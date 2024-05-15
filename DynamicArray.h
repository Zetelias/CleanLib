/**
 * @brief Defines a DynamicArray class, seeks to replace std::vector.
 *
 * @note It stores elements in a stack-allocated array until it reaches a certain size,
 * then it falls back to a heap-allocated array. This is called "small buffer optimization".
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <memory>

#include "IntegerTypedefs.h"

/**
 * @brief A dynamic array that stores elements in a stack-allocated array until it reaches a certain size,
 * seeks to replace std::vector.
 *
 * @tparam T The type of the elements stored in the array.
 * @tparam StackSize How much space to reserve in the stack for elements. Defaults to 16.
 * Absolutely tune this for your use case, and for best performance.
 * @tparam TAlloc The allocator used to allocate memory for the elements. Defaults to std::allocator<T>.
 * @tparam GrowthFactor
 */
template <
    typename T,
    usize StackSize = 16, // TODO: Calculate the default so stackArr and heapArr are same size
    int GrowthFactor = 2
>
class DynamicArray {

protected:
    usize capacity;
    usize length;
    union {
        T* heapArr;
        T stackArr[StackSize];
    };

    void growToHeap() {
        capacity = StackSize * GrowthFactor;
        T* newHeapArr = new T[capacity];
        std::copy(stackArr, stackArr + length, newHeapArr);
        heapArr = newHeapArr;
    }

    void growHeap() {
        capacity *= GrowthFactor;
        T* newHeapArr = new T[capacity];
        std::copy(heapArr, heapArr + length, newHeapArr);
        delete[] heapArr;
        heapArr = newHeapArr;
    }

public:
    DynamicArray() : capacity(StackSize), length(0), stackArr{} {
    }

    DynamicArray(const DynamicArray& other) : capacity(other.capacity), length(other.length) {
        if (capacity <= StackSize) {
            std::copy(other.stackArr, other.stackArr + length, stackArr);
        } else {
            heapArr = new T[capacity];
            std::copy(other.heapArr, other.heapArr + length, heapArr);
        }
    }

    DynamicArray(DynamicArray&& other) noexcept : capacity(other.capacity), length(other.length) {
        if (capacity <= StackSize) {
            std::move(other.stackArr, other.stackArr + length, stackArr);
        } else {
            heapArr = other.heapArr;
            other.heapArr = nullptr;
        }
    }

    static DynamicArray New() {
        return DynamicArray();
    }

    ~DynamicArray() {
        if (capacity > StackSize) {
            delete[] heapArr;
        }
    }

    void AppendCopy(const T& element) {
        if (capacity <= StackSize) {
            if (length == StackSize) {
                growToHeap();
                heapArr[length++] = T(element);
            } else {
                stackArr[length++] = T(element);
            }
        } else {
            if (length == capacity) {
                growHeap();
            }
            heapArr[length++] = T(element);
        }
    }

    void AppendMove(T&& element) {
        if (capacity <= StackSize) {
            if (length == StackSize) {
                growToHeap();
                heapArr[length++] = std::move(element);
            } else {
                stackArr[length++] = std::move(element);
            }
        } else {
            if (length == capacity) {
                growHeap();
            }
            heapArr[length++] = std::move(element);
        }
    }

    void ResizeIfOnHeap(usize newCapacity) {
        if (capacity > StackSize) {
            T* newHeapArr = new T[newCapacity];
            std::copy(heapArr, heapArr + length, newHeapArr);
            delete[] heapArr;
            heapArr = newHeapArr;
            capacity = newCapacity;
        }
    }

    [[nodiscard]] usize Length() const {
        return length;
    }

    [[nodiscard]] usize Capacity() const {
        return capacity;
    }

    [[nodiscard]] bool IsOnHeap() const {
        return capacity > StackSize;
    }

    [[nodiscard]] bool IsEmpty() const {
        return length == 0;
    }

    [[nodiscard]] bool IsFull() const {
        return length == capacity;
    }

    T& operator[](usize index) {
        return (capacity <= StackSize) ? stackArr[index] : heapArr[index];
    }
};

#endif //DYNAMICARRAY_H
