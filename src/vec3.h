#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3
{
    public:
        vec3() {}
        vec3(float v0, float v1, float v2)
        {
            v[0] = v0;
            v[1] = v1;
            v[2] = v2;
        }
    
    public:
        inline float x() const { return v[0]; }
        inline float y() const { return v[1]; }
        inline float z() const { return v[2]; }
        inline float r() const { return v[0]; }
        inline float g() const { return v[1]; }
        inline float b() const { return v[2]; }

        inline const vec3& operator+ () const { return *this; }
        inline       vec3  operator- () const { return vec3(-v[0], -v[1], -v[2]); }
        inline float       operator[] (int i) const { return v[i]; }
        inline float&      operator[] (int i) { return v[i]; }

        // initial value of reference to non-const must be an lvalue
        inline vec3& operator+=(const vec3& v2) { vec3 t = vec3(v[0] + v2[0], v[1] + v2[1], v[2] + v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator-=(const vec3& v2) { vec3 t = vec3(v[0] - v2[0], v[1] - v2[1], v[2] - v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator*=(const vec3& v2) { vec3 t = vec3(v[0] * v2[0], v[1] * v2[1], v[2] * v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator/=(const vec3& v2) { vec3 t = vec3(v[0] / v2[0], v[1] / v2[1], v[2] / v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator*=(const float f)  { vec3 t = vec3(v[0] * f    , v[1] * f    , v[2] * f    ); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator/=(const float f)  { vec3 t = vec3(v[0] / f    , v[1] / f    , v[2] / f    ); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }

        inline float length() const { return sqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2]); }
        inline float squared_length() const { return v[0]*v[0] + v[1] * v[1] + v[2] * v[2]; }
        inline vec3 unit_vector(vec3 x)  { return vec3(x[0] / x.length(), x[1] / x.length(), x[2] / x.length()); }
        inline float dot(const vec3& v1) { return v[0]*v1[0] + v[1] * v1[1] + v[2] * v1[2]; }
        
    private:
        float v[3]{0.};
};