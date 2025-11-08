//
//  PlayerController.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 08/11/25.
//

#include "PlayerController.hpp"
#include "InputManager.hpp"
#include "Character.hpp"
#include "Camera.hpp"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {}

void PlayerController::Update(float dt) {
    Character* character = associated.GetComponent<Character>();
    if (!character) return;

    auto& input = InputManager::GetInstance();

    Vec2 dir{0, 0};
    if (input.IsKeyDown(SDLK_w)) dir.y -= 1.0f;
    if (input.IsKeyDown(SDLK_s)) dir.y += 1.0f;
    if (input.IsKeyDown(SDLK_a)) dir.x -= 1.0f;
    if (input.IsKeyDown(SDLK_d)) dir.x += 1.0f;

    if (dir.x != 0.0f || dir.y != 0.0f) {
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.0f) {
            dir.x /= len;
            dir.y /= len;
        }

        Character::Command cmd(Character::Command::CommandType::MOVE, dir.x, dir.y);
        character->Issue(std::move(cmd));
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        float worldX = static_cast<float>(input.GetMouseX()) + Camera::pos.x;
        float worldY = static_cast<float>(input.GetMouseY()) + Camera::pos.y;
        Character::Command cmd(Character::Command::CommandType::SHOOT, worldX, worldY);
        character->Issue(std::move(cmd));
    }
}

void PlayerController::Render() {}
