//
//  Zombie.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "Zombie.hpp"
#include "Animator.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "Collider.hpp"
#include "InputManager.hpp"
#include "SpriteRenderer.hpp"

int Zombie::zombieCount = 0;

Zombie::Zombie(GameObject &associated)
    : Component(associated), hitpoints(100), hit(false), dead(false),
      hitSound("resources/audio/Hit0.wav"),
      deathSound("resources/audio/Dead.wav") {
    Zombie::zombieCount++;

    SpriteRenderer *zombie =
        new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    Animator *animator = new Animator(associated);

    associated.AddComponent(zombie);
    associated.AddComponent(animator);

    animator->AddAnimation("walking", Animation(0, 3, 0.30f));
    animator->AddAnimation("dead", Animation(5, 5, 0.00f));
    animator->AddAnimation("hit", Animation(4, 4, 0.15f));

    animator->SetAnimation("walking");

    associated.AddComponent(new Collider(associated));
}

Zombie::~Zombie() {
    Zombie::zombieCount--;
}

void Zombie::Damage(int damage) {
    if (hitpoints <= 0)
        return;

    hitSound.Play(1);
    hitpoints -= damage;

    if (hitpoints <= 0) {
        hitpoints = 0;
        dead = true;

        if (auto *animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("dead");
        }

        deathTimer.Restart();
        deathSound.Play(1);
    } else {
        hit = true;
        hitTimer.Restart();

        if (auto *animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("hit");
        }
    }
}

void Zombie::Update(float dt) {
    hitTimer.Update(dt);
    deathTimer.Update(dt);

    if (dead && deathTimer.Get() >= 5) {
        associated.RequestDelete();
    }

    if (hit && !dead && hitTimer.Get() >= 0.5f) {
        if (auto *animator = associated.GetComponent<Animator>()) {
            animator->SetAnimation("walking");
        }

        hit = false;
    }

    auto &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        int mouse_x = Camera::pos.x + input.GetMouseX();
        int mouse_y = Camera::pos.y + input.GetMouseY();

        const bool isInside = (mouse_x >= associated.box.x &&
                               mouse_x <= associated.box.x + associated.box.w &&
                               mouse_y >= associated.box.y &&
                               mouse_y <= associated.box.y + associated.box.h);

        if (isInside) {
            Damage(10);
        }
    }
    
    if (!dead && Character::player != nullptr) {
        GameObject& playerGO = Character::player->GetGameObject();

        Vec2 target(playerGO.box.x, playerGO.box.y);
        Vec2 pos(associated.box.x, associated.box.y);
        Vec2 dir = target - pos;

        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len > 0.01f) {
            dir.x /= len;
            dir.y /= len;

            const float ZOMBIE_SPEED = 80.0f;
            associated.box.x += dir.x * ZOMBIE_SPEED * dt;
            associated.box.y += dir.y * ZOMBIE_SPEED * dt;
        }
    }
}

void Zombie::Render() {}

void Zombie::NotifyCollision(GameObject &other) {
    if (dead) {
        return;
    }

    if (Bullet *bullet = other.GetComponent<Bullet>()) {
        if (bullet->targetsPlayer) {
            return;
        }

        Damage(bullet->GetDamage());
    }
}
