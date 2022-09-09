#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <numbers> // PI

// PI = 180
// degree -> radian
inline double degrees_to_radians(double degrees) {
    return degrees * std::numbers::pi / 180.0;
}

// radian -> degree
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

// [0,1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// [min,max)
inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}

// [min,max]
inline int random_int(int min, int max) {
    return static_cast<int>(random_double(min, max+1));
}