#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <math.h>

template<typename T>
class Vec2 {
public:
    Vec2()
     : x(T(0)), y(T(0)) { }

    Vec2(T x, T y)
     : x(x), y(y) { }

    Vec2<T> operator+(const Vec2<T> &rhs) const {
        return Vec2<T>(this->x + rhs.x, this->y + rhs.y);
    }

    Vec2<T> operator-(const Vec2<T> &rhs) const {
        return Vec2<T>(this->x - rhs.x, this->y - rhs.y);
    }

    T operator*(const Vec2<T> &rhs) const {
        return this->x * rhs.x +
               this->y * rhs.y;
    }

    Vec2<T> operator*(T value) const {
        return Vec2<T>(this->x * value, this->y * value);
    }

    T x, y;
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<unsigned int> Point2D;

template<typename T>
class Vec3 {
public:
    Vec3()
     : x(T(0)), y(T(0)), z(T(0)) { }

    Vec3(T x, T y, T z)
     : x(x), y(y), z(z) { }

    Vec3<T> operator+(const Vec3<T> &rhs) const {
        return Vec3<T>(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }

    Vec3<T> operator-(const Vec3<T> &rhs) const {
        return Vec3<T>(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    }

    T operator*(const Vec3<T> &rhs) const {
        return this->x * rhs.x +
               this->y * rhs.y +
               this->z * rhs.z;
    }

    Vec3<T> operator*(T value) const {
        return Vec3<T>(this->x * value, this->y * value, this->z * value);
    }

    Vec3<T> operator^(const Vec3<T> &rhs) const {
        return Vec3<T>(this->y * rhs.z - this->z * rhs.y,
                       this->z * rhs.x - this->x * rhs.z,
                       this->x * rhs.y - this->y * rhs.x);
    }

    T norm() const {
        return std::sqrt(this->x * this->x +
                         this->y * this->y +
                         this->z * this->z);
    }

    Vec3<T> &normalize(T l = 1) {
        T len = norm();
        if (len > 0) {
            T reciproLen = 1 / len;
            this->x = x * reciproLen;
            this->y = y * reciproLen;
            this->z = z * reciproLen;
        }
        return *this;
    }

    T x, y, z;
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif //__GEOMETRY_H__
