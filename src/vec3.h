#pragma once

#include <cmath>
#include <ostream>
#include "utils.h"

class vec3 {
    public:
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return *this;
        }

        vec3& operator*=(const double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        vec3& operator/=(const double t) {
            return *this *= 1/t;
        }

        // 向量的长度=√(x²+y²)。
        double length() const {
            return std::sqrt(length_squared());
        }

        // 返回向量长度的平方。适用于比较两向量的长度，避免了计算平方根。
        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        bool near_zero() const {
            // Return true if the vector is close to zero in all dimensions.
            const auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
        }

    public:
        double e[3];
};

// Type aliases for vec3
using Point = vec3;   // 3D point
using Color = vec3;   // RGB Color

// vec3 Utility Functions
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// https://www.symbolab.com/solver/vector-dot-product-calculator/%5Cbegin%7Bpmatrix%7D1%262%263%5Cend%7Bpmatrix%7D%5Ccdot%5Cbegin%7Bpmatrix%7D1%265%267%5Cend%7Bpmatrix%7D?or=ex
// (1, 2, 3) . (1, 5, 7) = 
// 1 * 1 + 2 * 5 + 3 * 7 = 32
/**
 * @brief 
 * 
 * @param u 
 * @param v 
 * @return double 
 * 
 * dot(A, B) > 0 => 锐角
 * dot(A, B) < 0 => 钝角
 * dot(A, B) = 0 => 直角
 * 
 * 
 */
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// (u1, u2, u3) x (v1, v2, v3) = 
// (u2v3 - u3v2, u1v3 - u3v1, u1v2 - u2v1)
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// In mathematics, the open unit disk (or disc) around P (where P is a given point in the plane), 
// The open unit disk -> is the set of points whose distance from P is less than 1.
// The closed unit disk around P is the set of points whose distance from P is less than or equal to 1.
inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;

        return p;
    }
}

// 求位于单位圆上的一个点
// A unit ball is the closed set of points of distance less than or equal to 1 from a fixed central point.
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() > 1) 
            continue;

        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();

    // 如果和法线的夹角是锐角，肯定在半圆上;
    // 否则，在另一半。
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// 求反射向量
inline vec3 reflect(const Point& I, const Point& N) {
    return I - 2 * dot(I,N) * N;
}

// 求折射向量
inline vec3 refract(const Point& uv, const Point& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}