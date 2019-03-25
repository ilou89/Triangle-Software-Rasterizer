#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

namespace modload {

template<typename T>
class Vec2 {
public:
    Vec2()
     : x(0), y(0) { }

    Vec2(T x, T y)
     : x(x), y(y) { }

    Vec2& operator+=(const Vec2& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

private:
    T x, y;
};


template<typename T>
class Vec3 {
public:
    Vec3()
     : x(0), y(0), x(0) { }

    Vec3(T x, T y, T z)
     : x(x), y(y), x(z) { }

    Vec3& operator+=(const Vec3& rhs) {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

private:
    T x, y, z;
};

template<typename T>
inline T operator+(T lhs, const T& rhs) {
    lhs += rhs;
    return lhs;
}

}

#endif //__GEOMETRY_H__
