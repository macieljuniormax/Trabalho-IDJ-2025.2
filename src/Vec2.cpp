//
//  Vec2.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#include "Vec2.hpp"
#include <cmath>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &rhs) const {
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const {
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(float rhs) const { return Vec2(x * rhs, y * rhs); }

Vec2 Vec2::Rotate(float rad) const {
    float cs = std::cos(rad);
    float sn = std::sin(rad);
    return Vec2(x * cs - y * sn, x * sn + y * cs);
}
