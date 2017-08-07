#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <string>

template <typename T>
struct Vector2 {

    T x;
    T y;

    Vector2() {

    }

    Vector2(T x, T y) {

        this->x = x;
        this->y = y;
    }

    std::string ToString() {

        return "x:" + to_string(x) + ", y:" + to_string(y);
    }

    void operator=(const Vector2 &vec) {

        x = vec.x;
        y = vec.y;
    }

    bool operator==(const Vector2 <T> &vec) {

        if ((x == vec.x) && (y == vec.y)) {

            return true;
        }

        return false;
    }

    bool operator!=(const Vector2 <T> &vec) {

        if ((x != vec.x) || (y != vec.y)) {

            return true;
        }

        return false;
    }

    void operator+=(const Vector2 <T> &vec) {

        x += vec.x;
        y += vec.y;
    }

    void operator-=(const Vector2 <T> &vec) {

        x -= vec.x;
        y -= vec.y;
    }

    void operator*=(const Vector2 <T> &vec) {

        x *= vec.x;
        y *= vec.y;
    }

    Vector2 operator+(const Vector2 <T> &vec) {

        return Vector2 <T> (x + vec.x, y + vec.y);;
    }

    Vector2 operator+(const T &var) {

        return Vector2 <T> (x + var, y + var);;
    }

    Vector2 operator-(const Vector2 &vec) {

        return Vector2 <T> (x - vec.x, y - vec.y);;
    }

    Vector2 operator-(const T &var) {

        return Vector2 <T> (x - var, y - var);;
    }

    Vector2 operator*(const Vector2 &vec) {

        return Vector2 <T> (x * vec.x, y * vec.y);;
    }

    Vector2 operator*(const T &var) {

        return Vector2 <T> (x * var, y * var);;
    }
};

#endif // VECTOR2_H
