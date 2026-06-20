#pragma once

#include <random>

// Made to test linked list with random values
namespace Random
{
    template <typename T>       // exempt from ODR
    T get()
    {
        static std::mt19937 mt { std::random_device{}() };      // static in function, initialized once
        static std::uniform_int_distribution<T> range(3, 20);

        return range(mt);
    }
}
