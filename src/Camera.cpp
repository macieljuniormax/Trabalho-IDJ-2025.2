//
//  Camera.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/10/25.
//

#include "Camera.hpp"
#include "InputManager.hpp"
#include <algorithm>

#include <iostream>

static inline int ViewW() { return 1200; }
static inline int ViewH() { return 900; }

Vec2 Camera::pos = {0, 0};
Vec2 Camera::speed = {0, 0};
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
//    const float mapW = 2560.0f;
//    const float mapH = 2544.0f;
    
    if (focus) {
        if (focus->IsDead()) {
            Unfollow();
        } else {
            pos.x = (focus->box.x + focus->box.w / 2.0f) - ViewW() * 0.5f;
            pos.y = (focus->box.y + focus->box.h / 2.0f) - ViewH() * 0.5f;
            
            pos.x += speed.x * dt;
            pos.y += speed.y * dt;
            return;
        }
    }

    InputManager& input = InputManager::GetInstance();

    Vec2 dir{0, 0};
    if (input.IsKeyDown(LEFT_ARROW_KEY))  dir.x -= 1.0f;
    if (input.IsKeyDown(RIGHT_ARROW_KEY)) dir.x += 1.0f;
    if (input.IsKeyDown(UP_ARROW_KEY))    dir.y -= 1.0f;
    if (input.IsKeyDown(DOWN_ARROW_KEY))  dir.y += 1.0f;

    speed.x = dir.x * 200;
    speed.y = dir.y * 200;
    
    pos.x += speed.x * dt;
    pos.y += speed.y * dt;
}
