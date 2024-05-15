/**
 * @brief Defines to know which compiler we're using, which features are available,
 * how are we compiling, and other useful information.
 *
 * @note There's spaghetti preprocessor code here, and it's fine,
 * it helps us not write spaghetti preprocessor code in other files.
 *
 * @note This library is C++23 minimum, so we assume every
 * C++23 feature is available.
 */

#ifndef DEFINES_H
#define DEFINES_H

#define IS_GCC __GNUG__
#define IS_CLANG __clang__
#define IS_MSVC _MSC_VER

#endif //DEFINES_H
