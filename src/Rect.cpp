//
//  Rect.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#include "Rect.hpp"

Rect::Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

Vec2 Rect::GetCenter() const {
    return Vec2(x + w * 0.5f, y + h * 0.5f);
}
