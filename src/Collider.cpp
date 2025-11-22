//
//  Collider.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 14/11/25.
//

#include "Collider.hpp"
#include "GameObject.hpp"

#include <cmath>

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
    : Component(associated),
      box(associated.box),
      scale(scale),
      offset(offset) {}

void Collider::Update(float dt) {
    (void)dt;
    
    box = associated.box;

    box.w *= scale.x;
    box.h *= scale.y;

    const float objectCenterX = associated.box.x + associated.box.w * 0.5f;
    const float objectCenterY = associated.box.y + associated.box.h * 0.5f;

    const float angleRad = static_cast<float>(associated.angleDeg) * M_PI / 180.0f;

    const float cosA = std::cos(angleRad);
    const float sinA = std::sin(angleRad);

    const float rotatedOffsetX = offset.x * cosA - offset.y * sinA;
    const float rotatedOffsetY = offset.x * sinA + offset.y * cosA;

    box.x = objectCenterX - box.w * 0.5f + rotatedOffsetX;
    box.y = objectCenterY - box.h * 0.5f + rotatedOffsetY;
}

void Collider::Render() {}

void Collider::SetScale(Vec2 newScale) {
    scale = newScale;
}

void Collider::SetOffset(Vec2 newOffset) {
    offset = newOffset;
}
