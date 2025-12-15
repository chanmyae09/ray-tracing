#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// inline double random_double() {
//     // Returns a random real in [0,1).
//     return std::rand() / (RAND_MAX + 1.0);
// }


inline double random_double() {
    // xorshift32 RNG - much faster than std::rand()
    static thread_local uint32_t state = 0x12345678;
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return (state >> 8) * 0x1.0p-24; // converts to [0,1)
}

// inline double random_double() {
//     thread_local static std::mt19937 generator(3);
//     thread_local static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//     return distribution(generator);
// }

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int (double min, double max){
    return int(random_double(min, max+1));
}


// Common Headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif