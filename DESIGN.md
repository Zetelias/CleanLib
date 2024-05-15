**This is how we design the library.
You can also use it as your own design, 
and you should if you use this library**

# Zen of the library
Everything has a "Zen" nowadays, so here's the 
TLDR of this document:
1. We must tell the user what they are doing,
   with explicit functions and explicit copies.
2. You do not need to know the library for basic use,
   an IDE's autocomplete should be enough.
3. Multiple ways to do the same thing is bad.
4. Insisting on having one way to do something,
   neglecting what the user would want to do,
   is worse.
5. Make it easy and possible for the user to tune
   containers for performance, and make them
   aware they should do it.
6. Exceptions for very rare errors, Result and
   Option for common errors.
7. If implementing something correctly is hard,
   don't reinvent the wheel: make a wrapper
   around the STL or another library.

# Explicitness
Explicitness is generally good in software dev,
especially with lower level code. It makes it so
people with less knowledge can understand the code,
## Prefer static function `New` to constructors
You can both make an object with a 
constructor and a static function. However, 
the user should use `Class::New()`,
similar to `Struct::new()` in Rust,
for explicitness reasons.
`Class::New()` can take parameters.
Even though the constructor is public, it is only 
public so that other containers can hold the object.

## Prefer explicit functions to a `New` with default parameters or to overloaded `New` functions
Say you want to create a vector class,
normally, the user can preallocate space
for elements of the vector, for performance tuning.
For example, with the STL, you can do `std::vector<int> v(100)`.
Should we do `DynamicArray::New(100)` ?

No, you have no clue what the 100 is for.
Remember, this library, and code using it
must be readable, instead of relying
on your knowledge of the library.
Instead, we should have `DynamicArray::NewWithCapacity(100)`.
Now we know what the 100 is for.

## Explicit copies, explicit moving
A good example of this is the `DynamicArray` API.
If you want to add a copy of your object to the array, 
you use `AppendCopy`, and if you want to move
your object to the array, you use `AppendMove`.

Here, you can see that the user is explicitly telling the library
what they want to do with their object. It avoids a lot of confusion,
and makes writing performant code easier.

Also, when constructing something from a reference
(copying), use `copy = T(original)` syntax instead
of `copy = original` or `copy(original)`.

# Naming
## Visibility and naming
- Anything **public** is in **UpperCamelCase** 
- Anything **private** is in **lowerCamelCase**
- Anything that **must be public** but should **not
  be used by the user** is in **_lowerCamelCase**
  with an underscore at the beginning. We try to
  re-export our "utility" functions for them to be used for the user,
  so this is not used often.

## File naming
- A file containing a class is named after the class, in UpperCamelCase. 
  Example: `DynamicArray.h`
- A file containing a class, and functions related to it is still named after the class.
- A file containing mostly functions, is named after the functions, in UpperCamelCase.
  Do not be afraid to put `utils` in the name of the file.
- A file containing anything else, is named after the content, in UpperCamelCase.
  Example: `CompilerDefines.h`, `IntegerTypedefs.h`