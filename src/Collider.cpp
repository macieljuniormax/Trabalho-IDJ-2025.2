//
//  Collider.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 14/11/25.
//

#include "Collider.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "SDL_include.h"
#include <cmath>

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset)
    : Component(associated), box(associated.box), scale(scale), offset(offset) {
}

void Collider::Update(float dt) {
    (void)dt;

    box = associated.box;

    box.w *= scale.x;
    box.h *= scale.y;

    const float objectCenterX = associated.box.x + associated.box.w * 0.5f;
    const float objectCenterY = associated.box.y + associated.box.h * 0.5f;

    const float angleRad =
        static_cast<float>(associated.angleDeg) * M_PI / 180.0f;

    const float cosA = std::cos(angleRad);
    const float sinA = std::sin(angleRad);

    const float rotatedOffsetX = offset.x * cosA - offset.y * sinA;
    const float rotatedOffsetY = offset.x * sinA + offset.y * cosA;

    box.x = objectCenterX - box.w * 0.5f + rotatedOffsetX;
    box.y = objectCenterY - box.h * 0.5f + rotatedOffsetY;
}

void Collider::Render() {
#ifdef DEBUG
    Vec2 center = box.GetCenter();
    SDL_Point points[5];

    const float angleRad = associated.angleDeg * (M_PI / 180.0f);

    Vec2 p0 = Vec2(box.x, box.y);
    Vec2 r0 = (p0 - center).Rotate(angleRad) + center - Camera::pos;
    points[0] = {(int)r0.x, (int)r0.y};
    points[4] = points[0];

    Vec2 p1 = Vec2(box.x + box.w, box.y);
    Vec2 r1 = (p1 - center).Rotate(angleRad) + center - Camera::pos;
    points[1] = {(int)r1.x, (int)r1.y};

    Vec2 p2 = Vec2(box.x + box.w, box.y + box.h);
    Vec2 r2 = (p2 - center).Rotate(angleRad) + center - Camera::pos;
    points[2] = {(int)r2.x, (int)r2.y};

    Vec2 p3 = Vec2(box.x, box.y + box.h);
    Vec2 r3 = (p3 - center).Rotate(angleRad) + center - Camera::pos;
    points[3] = {(int)r3.x, (int)r3.y};

    SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);

#endif
}

void Collider::SetScale(Vec2 newScale) { scale = newScale; }

void Collider::SetOffset(Vec2 newOffset) { offset = newOffset; }
