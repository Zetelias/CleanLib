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
    Option() : value() {
    }

    Option(const T& value) : value(value) {
    }

    Option(T&& value) : value(std::move(value)) {
    }

    T& Unwrap() {
        if (!value.has_value()) {
            throw std::runtime_error("Option does not contain a value.");
        }
        return value.value();
    }
};

template <typename T>
Option<T> SomeCopy(const T& value) {
    return Option<T>(value);
}

template <typename T>
Option<T> SomeMove(T&& value) {
    return Option<T>(std::forward<T>(value));
}

template <typename T>
Option<T> None() {
    return Option<T>();
}

#endif //OPTION_H
