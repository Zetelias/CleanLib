cmake_minimum_required(VERSION 3.28)
project(CleanLib)

set(CMAKE_CXX_STANDARD 23)

add_executable(CleanLib main.cpp
        DynamicArray.h
        IntegerTypedefs.h
        CompilerDefines.h
        Option.h)
