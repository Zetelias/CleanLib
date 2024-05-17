#include <chrono>
#include <string>
#include <vector>
#include <iostream>

#include "DynamicArray.h"
#define SIZE 100'000

int main(int argc, char *argv[]) {
    std::vector<std::string> vec(SIZE);
    auto now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++) {
        vec.push_back(std::to_string(i) + " hello :DDDDDD");
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - now).count();
    std::cout << "Elapsed time: " << elapsed_ns << " ns" << std::endl;

    DynamicArray<std::string, SIZE> dyn_array;
    now = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; i++) {
        dyn_array.AppendMove(std::to_string(i) + " hello :DDDDDD");
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - now).count();
    std::cout << "Elapsed time: " << elapsed_ns << " ns" << std::endl;
}
