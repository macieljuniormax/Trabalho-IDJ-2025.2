//
//  AIController.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#include "AIController.hpp"
#include "Character.hpp"
#include "GameObject.hpp"
#include "Gun.hpp"
#include <cmath>

int AIController::npcCounter = 0;

namespace {
    constexpr float NPC_REST_COOLDOWN = 1.5f;
    constexpr float NPC_ARRIVE_EPS = 10.0f;
    constexpr float NPC_SPEED = 150.0f;
}

AIController::AIController(GameObject &associated)
    : Component(associated),
      state(AIState::RESTING),
      restTimer(),
      destination(0.0f, 0.0f) {
    ++npcCounter;
}

AIController::~AIController() { --npcCounter; }

void AIController::Update(float dt) {
    // se não tem player, não faz nada
    if (Character::player == nullptr) {
        return;
    }

    switch (state) {
    case AIState::RESTING: {
        restTimer.Update(dt);
        if (restTimer.Get() >= NPC_REST_COOLDOWN) {
            GameObject &playerGO = Character::player->GetGameObject();
            destination = Vec2(playerGO.box.x + playerGO.box.w * 0.5f,
                               playerGO.box.y + playerGO.box.h * 0.5f);

            state = AIState::MOVING;
        }
    } break;

    case AIState::MOVING: {
        Character *character = associated.GetComponent<Character>();
        if (!character) {
            state = AIState::RESTING;
            restTimer.Restart();
            return;
        }

        Vec2 pos(associated.box.x + associated.box.w * 0.5f,
                 associated.box.y + associated.box.h * 0.5f);

        Vec2 dir(destination.x - pos.x, destination.y - pos.y);
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len > NPC_ARRIVE_EPS) {
            dir.x /= len;
            dir.y /= len;

            Character::Command moveCmd(
                Character::Command::CommandType::MOVE, dir.x, dir.y);
            character->Issue(std::move(moveCmd));
        } else {
            // chegou ~no destino: atira no player e volta para RESTING
            GameObject &playerGO = Character::player->GetGameObject();
            Vec2 target(playerGO.box.x + playerGO.box.w * 0.5f,
                        playerGO.box.y + playerGO.box.h * 0.5f);

            Character::Command shootCmd(
                Character::Command::CommandType::SHOOT,
                target.x,
                target.y);
            character->Issue(std::move(shootCmd));

            restTimer.Restart();
            state = AIState::RESTING;
        }
    } break;
    }
}

void AIController::Render() {}
