#pragma once


#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <numbers> // PI

inline double degrees_to_radians(double degrees) {
    return degrees * std::numbers::pi / 180.0;
}

inline float radians_to_degrees(float radians)
{
    return radians * 180.0 / std::numbers::pi;
}

// x => (min , max)
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;

    return x;
}

inline double random_double() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max+1));
}