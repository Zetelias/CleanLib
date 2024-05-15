/**
 * @brief Typedefs for integer types.
 * Should be used for all integer types in this library's code,
 * and also your code if you want to be consistent.
 * The naming is the same as Rust, with additional fast types.
 *
 * @note Use fast types when you don't need a specific size.
 * For example, use `u8fast` instead of `u8fast` if you know that your variable
 * will not exceed 255, and you don't need it to be exactly 8 bits.
 *
 * @authors Zetelias (@zetelias.proton.me), and contributors
 */

#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <cstddef>
#include <cstdint>
#include "CompilerDefines.h"

// Unsigned integer with the size of a pointer.
// Can hold any array index or size of any object.
// Should be used for indexing arrays and loops.
typedef size_t usize;

// Signed `usize`
typedef std::ptrdiff_t isize;

typedef int8_t i8; // signed integer on 8 bits
typedef int_fast8_t i8fast; // fastest signed integer available, at least 8 bits
typedef uint8_t u8; // unsigned integer on 8 bits
typedef uint_fast8_t u8fast; // fastest unsigned integer available, at least 8 bits

typedef int16_t i16; // signed integer on 16 bits
typedef int_fast16_t i16fast; // fastest signed integer available, at least 16 bits
typedef uint16_t u16; // unsigned integer on 16 bits
typedef uint_fast16_t u16fast; // fastest unsigned integer available, at least 16 bits

typedef int32_t i32; // signed integer on 32 bits
typedef int_fast32_t i32fast; // fastest signed integer available, at least 32 bits
typedef uint32_t u32; // unsigned integer on 32 bits
typedef uint_fast32_t u32fast; // fastest unsigned integer available, at least 32 bits

typedef int64_t i64; // signed integer on 64 bits
typedef int_fast64_t i64fast; // fastest signed integer available, at least 64 bits
typedef uint64_t u64; // unsigned integer on 64 bits
typedef uint_fast64_t u64fast; // fastest unsigned integer available, at least 64 bits

// If we're on GCC or clang, use the builtin i128
#if defined(IS_GCC) || defined(IS_CLANG)
typedef __int128 i128;
typedef __uint128_t u128;

// Else if we're on MSVC, use the one in the header
#elif defined(IS_MSVC)
#include <__msvc_int128.hpp>
typedef _Int128 i128;
typedef _Uint128 u128;
#endif

#endif //TYPEDEFS_H
