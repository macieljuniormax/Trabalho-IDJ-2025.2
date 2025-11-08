//
//  Character.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#include "Character.hpp"
#include "Animator.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Gun.hpp"
#include "InputManager.hpp"
#include "SpriteRenderer.hpp"
#include "State.hpp"

Character *Character::player = nullptr;

Character::Character(GameObject &associated, const std::string &sprite)
    : Component(associated), gun(), taskQueue(), speed(0.0f, 0.0f),
      linearSpeed(200.0f), hp(100), deathTimer() {

    SpriteRenderer *personagem = new SpriteRenderer(associated, sprite, 3, 2);
    associated.AddComponent(personagem);

    Animator *animator = new Animator(associated);
    associated.AddComponent(animator);

    animator->AddAnimation("idle", Animation(0, 5, 0.10f));
    animator->AddAnimation("walking", Animation(6, 9, 0.10f));
    animator->AddAnimation("dead", Animation(10, 11, 0.00f));

    animator->SetAnimation("idle");

    if (Character::player == nullptr) {
        Character::player = this;
    }
}

Character::~Character() {
    if (Character::player == this) {
        Character::player = nullptr;
    }
}

void Character::Start() {
    State &state = Game::GetInstance().GetState();
    std::weak_ptr<GameObject> self = state.GetObjectPtr(&associated);

    GameObject *gunGO = new GameObject();

    gunGO->box.x = associated.box.x;
    gunGO->box.y = associated.box.y;

    gunGO->AddComponent(new Gun(*gunGO, self));

    gun = Game::GetInstance().GetState().AddObject(gunGO);
}

void Character::Update(float dt) {
    if (!taskQueue.empty()) {
        Command &command = taskQueue.front();

        auto &input = InputManager::GetInstance();
        Vec2 target = Vec2(input.GetMouseX() + Camera::pos.x,
                           input.GetMouseY() + Camera::pos.y);

        if (command.type == Command::CommandType::MOVE) {
            const float currentX = associated.box.x + associated.box.w * 0.5f;
            const float currentY = associated.box.y + associated.box.h * 0.5f;

            const float distanceX = command.pos.x - currentX;
            const float distanceY = command.pos.y - currentY;
            const float distance =
                std::sqrt(distanceX * distanceX + distanceY * distanceY);

            const float maxStep = linearSpeed * dt;

            if (distance <= MIN_DISTANCE_TO_TARGET ||
                maxStep <= MIN_STEP_DISTANCE || distance <= maxStep) {

                associated.box.x = command.pos.x - associated.box.w * 0.5f;
                associated.box.y = command.pos.y - associated.box.y * 0.5f;
                speed.x = speed.y = 0.0f;
                taskQueue.pop();
            } else {
                const float directionX = distanceX / distance;
                const float directionY = distanceY / distance;

                associated.box.x += directionX * maxStep;
                associated.box.y += directionY * maxStep;

                speed.x = directionX * linearSpeed;
                speed.y = directionY * linearSpeed;
            }
        } else if (command.type == Command::CommandType::SHOOT) {
            if (auto sharedGun = gun.lock()) {
                if (auto *gunComponent = sharedGun->GetComponent<Gun>()) {
                    gunComponent->Shoot(target);
                }
            }
            taskQueue.pop();
        } else {
            speed.x = speed.y = 0.0f;
        }

        const bool isDead = (hp <= 0);

        if (Animator *animator = associated.GetComponent<Animator>()) {
            if (isDead) {
                animator->SetAnimation("dead");
            } else {
                const bool isMoving =
                    (std::abs(speed.x) > 0.01f || std::abs(speed.y) > 0.01f);
            }
        }

        if (isDead) {
            deathTimer.Update(dt);
            if (deathTimer.Get() >= 0.8f) {
                associated.RequestDelete();
            }
            speed.x = speed.y = 0.0f;
        }
    }
}
