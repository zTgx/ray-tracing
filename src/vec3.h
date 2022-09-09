#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3;
inline float dot(const vec3& a, const vec3& b);

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
        inline vec3        operator* (float t) { return vec3(v[0] * t, v[1] * t, v[2] * t); }

        // initial value of reference to non-const must be an lvalue
        inline vec3& operator+(const vec3& v2) { vec3 t = vec3(v[0] + v2[0], v[1] + v2[1], v[2] + v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }

        inline vec3& operator+=(const vec3& v2) { vec3 t = vec3(v[0] + v2[0], v[1] + v2[1], v[2] + v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator-=(const vec3& v2) { vec3 t = vec3(v[0] - v2[0], v[1] - v2[1], v[2] - v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator*=(const vec3& v2) { vec3 t = vec3(v[0] * v2[0], v[1] * v2[1], v[2] * v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator/=(const vec3& v2) { vec3 t = vec3(v[0] / v2[0], v[1] / v2[1], v[2] / v2[2]); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator*=(const float f)  { vec3 t = vec3(v[0] * f    , v[1] * f    , v[2] * f    ); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }
        inline vec3& operator/=(const float f)  { vec3 t = vec3(v[0] / f    , v[1] / f    , v[2] / f    ); v[0]= t[0]; v[1]=t[1]; v[2]=t[2]; return *this; }

        inline float length() const { return sqrt(v[0]*v[0] + v[1] * v[1] + v[2] * v[2]); }
        inline float squared_length() const { return v[0]*v[0] + v[1] * v[1] + v[2] * v[2]; }
        inline float angle(vec3 a, vec3 b) { return acos(::dot(a, b) / a.length() / b.length()); }
      
    private:
        float v[3]{0.};
};      
        
inline vec3 unit_vector(vec3 x)  { return vec3(x[0] / x.length(), x[1] / x.length(), x[2] / x.length()); }

// 点积
// 1. 求夹角 2. 求A长度 3. 判断夹角钝角、锐角
inline float dot(const vec3& a, const vec3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }

// 叉积
// 1. 判断AB的方向关系 
// AB > 0  , B 在 A 的逆时针方向
// AB < 0 , B 在 A 的顺时针方向
// AB = 0 , B A共线
// 2. 计算四边形的有向面积
inline vec3 cross(const vec3& v, const vec3& v1) { return vec3(
    (  v[1] * v1[2] - v[2] * v1[1]),
    (-(v[0] * v1[2] - v[2] * v1[0])),
    (  v[0] * v1[1] - v[1] * v1[0])
); }

