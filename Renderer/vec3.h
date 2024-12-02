#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3{
    // usable for colors, locations, direction, offsets, etc.
    public:
        double e[3];

        // Constructors, if no args given, create new vector.
        vec3() : e{0,0,0} {}
        vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

        // Return vector element functions
        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        // Operator logic for Vectors
        vec3 operator-() const { 
            return vec3(-e[0],-e[1],-e[2]);} // Inverse
        double operator[](int i) const {return e[i];} // get Element at index
        double& operator[](int i) {return e[i];} // get reference of element at index

        // Self arithmatic logic
        vec3& operator+=(const vec3& v){
            // sum together vector values from vector
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double c){
            // multiply vector by constant
            e[0] *= c;
            e[1] *= c;
            e[2] *= c;
            return *this;
        }
        
        vec3& operator/=(double c){
            // inverse multiplication
            return *this *= 1/c;
        }

        double length_squared() const {
            // magnitude of vector
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }
        
        double length() const {
            // length of vector
            return std::sqrt(length_squared());
        }
};

// useful aliases for vec3 to store rgb, etc.
using point3 = vec3;

// utility functions for Vector3
inline std::ostream& operator<<(std::ostream& out, const vec3& v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
    // summation of vectors; add each element
    return vec3(u.e[0] + v.e[0],u.e[1] + v.e[1],u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
    // combine inverse and summation
    return u + -v;
}

inline vec3 operator*(const vec3& u, const vec3& v){
    // although for math impossible, useful for colors
    return vec3(u.e[0] * v.e[0],u.e[1] * v.e[1],u.e[2] * v.e[2]);
}

inline vec3 operator*(double c, const vec3& v){
    // multiply each element by constant
    return vec3(c * v.e[0],c * v.e[1],c * v.e[2]);
}

inline vec3 operator*(const vec3& v, double c){
    // ensure order doesn't matter
    return c * v;
}

inline vec3 operator/(const vec3& v, double c){
    // inverse of multiplication for vectors
    return (1/c) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    // dot product for two vectors defined by math, 
    // show out parallel vectors are
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    // cross product measure how perpendicular vectors are
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(const vec3& v) {
    // Normalize vector by dividing by length
    return v / v.length();
}
#endif


