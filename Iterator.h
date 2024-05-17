//
// Created by zetelias on 16/05/24.
//

#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class Iterator {
protected:
    T* start;
    T* end;

    Iterator(T* start, T* end) : start(start), end(end) {
    }
    Iterator(T* start, usize length) : start(start), end(start + length) {
    }

public:
    static Iterator New(T* start, T* end) {
        return Iterator{start, end};
    }

    static Iterator NewFromIter(T* start, usize length) {
        return Iterator{start, length};
    }

    [[nodiscard]] usize Length() const {
        return end - start;
    }
};

#endif //ITERATOR_H
