//
//  Zombie.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "Zombie.hpp"
#include "Animator.hpp"
#include "InputManager.hpp"
#include "SpriteRenderer.hpp"
#include "Camera.hpp"

Zombie::Zombie(GameObject &associated)
    : Component(associated), hitpoints(100), hit(false), dead(false),
      hitSound("resources/audio/Hit0.wav"),
      deathSound("resources/audio/Dead.wav") {
    SpriteRenderer *zombie =
        new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    Animator *animator = new Animator(associated);

    associated.AddComponent(zombie);
    associated.AddComponent(animator);

    animator->AddAnimation("walking", Animation(0, 3, 0.30f));
    animator->AddAnimation("dead", Animation(5, 5, 0.00f));
    animator->AddAnimation("hit", Animation(4, 4, 0.15f));

    animator->SetAnimation("walking");
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
    
    if (dead && deathTimer.Get() >=5) {
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
}

void Zombie::Render() {}
