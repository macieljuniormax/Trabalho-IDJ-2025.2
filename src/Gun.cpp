//
//  Gun.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#include "Gun.hpp"
#include "Animator.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "SpriteRenderer.hpp"

Gun::Gun(GameObject &associated, std::weak_ptr<GameObject> character)
    : Component(associated), shotSound("resources/audio/Range.wav"),
      reloadSound("resources/audio/PumpAction.mp3"), cooldownState(0),
      cdTimer(), character(std::move(character)) {

    SpriteRenderer *gun =
        new SpriteRenderer(associated, "resources/img/Gun.png", 3, 2);
    associated.AddComponent(gun);

    Animator *animator = new Animator(associated);
    associated.AddComponent(animator);

    animator->AddAnimation("idle", Animation(0, 0, 0.10f));
    animator->AddAnimation("reloading", Animation(1, 5, 0.05f));

    animator->SetAnimation("idle");
}

void Gun::Update(float dt) {
    if (auto owner = character.lock(); owner) {
        const float ownerX = owner->box.x + owner->box.w * 0.5f;
        const float ownerY = owner->box.y + owner->box.h * 0.5f;

        auto &input = InputManager::GetInstance();
        const float targetX = Camera::pos.x + input.GetMouseX();
        const float targetY = Camera::pos.y + input.GetMouseY();

        const float aimDX = targetX - ownerX;
        const float aimDY = targetY - ownerY;
        const float aimAngleRad = std::atan2(aimDY, aimDX);

        const float HAND_PIVOT_X = +6.0f;
        const float HAND_PIVOT_Y = -4.0f;
        const float HOLD_OFFSET  = 16.0f;

        const float baseX = ownerX + HAND_PIVOT_X;
        const float baseY = ownerY + HAND_PIVOT_Y;

        const float gunX = baseX + std::cos(aimAngleRad) * HOLD_OFFSET;
        const float gunY = baseY + std::sin(aimAngleRad) * HOLD_OFFSET;

        associated.box.x = gunX - associated.box.w * 0.5f;
        associated.box.y = gunY - associated.box.h * 0.5f;

        constexpr float POST_SHOT_PAUSE = 0.10f;
        constexpr float RELOADING_TIME = 0.40f;
        constexpr float POST_RELOAD_PAUSE = 0.12f;

        cdTimer.Update(dt);

        switch (cooldownState) {
        case 0: {
            if (Animator *animator = associated.GetComponent<Animator>()) {
                animator->SetAnimation("idle");
            }
        } break;

        case 1: {
            if (cdTimer.Get() >= POST_SHOT_PAUSE) {
                cooldownState = 2;
                cdTimer.Restart();
                reloadSound.Play(1);

                if (Animator *animator = associated.GetComponent<Animator>()) {
                    animator->SetAnimation("reloading");
                }
            }
        } break;

        case 2: {
            if (cdTimer.Get() >= RELOADING_TIME) {
                cooldownState = 3;
                cdTimer.Restart();

                if (Animator *animator = associated.GetComponent<Animator>()) {
                    animator->SetAnimation("idle");
                }
            }
        } break;

        case 3: {
            if (cdTimer.Get() >= POST_RELOAD_PAUSE) {
                cooldownState = 0;
                cdTimer.Restart();
            }
        } break;

        default:
            cooldownState = 0;
            cdTimer.Restart();
            break;
        }

    } else {
        associated.RequestDelete();
        return;
    }
}

void Gun::Render() {}

void Gun::Shoot(const Vec2 &target) {
    if (cooldownState != 0)
        return;

    if (auto owner = character.lock()) {
        const float ownerX = owner->box.x + owner->box.w * 0.5f;
        const float ownerY = owner->box.y + owner->box.h * 0.5f;

        const float targetDirectionX = target.x - ownerX;
        const float targetDirectionY = target.y - ownerY;

        const float angleToTarget =
            std::atan2(targetDirectionY, targetDirectionX);

        shotSound.Play(1);

        cooldownState = 1;
        cdTimer.Restart();

        if (Animator *animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("idle");
        }
    }
}
