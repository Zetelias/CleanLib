//
// Created by zetelias on 15/05/24.
//

#ifndef OPTION_H
#define OPTION_H
#include <algorithm>
#include <stdexcept>
#include <type_traits>

/**
 * @brief A type that represents an optional value. It is a replacement for std::optional.
 * @note Wrapper around std::optional.
 * @tparam T The type of the value stored in the option.
 */
template <typename T>
class Option {
protected:
    std::optional<T> value;

public:
    constexpr Option() : value() {
    }
    constexpr Option(const T& value) : value(value) {
    }
    constexpr Option(T&& value) : value(std::move(value)) {
    }

    constexpr static Option NewNone() {
        return Option();
    }

    constexpr static Option NewSomeCopy(const T& value) {
        return Option(value);
    }

    constexpr static Option NewSomeMove(T&& value) {
        return Option(std::move(value));
    }

    constexpr explicit operator bool() const {
        return value.has_value();
    }

    T&& UnwrapMove() {
        if (!value.has_value()) {
            throw std::runtime_error("Option does not contain a value.");
        }
        return std::move(value.value());
    }

    constexpr T* UnwrapPtr() const {
        if (!value.has_value()) {
            return nullptr;
        }
        return const_cast<int*>(&value.value());
    }
};

template <typename T>
constexpr Option<T> SomeCopy(const T& value) {
    return Option<T>::NewSomeCopy(T(value));
}

template <typename T>
constexpr Option<T> SomeMove(T&& value) {
    return Option<T>::NewSomeMove(T(std::forward<T>(value)));
}

template <typename T>
constexpr Option<T> None() {
    return Option<T>::NewNone();
}

#endif //OPTION_H
