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

Zombie::Zombie(GameObject &associated)
    : Component(associated), hitpoints(100),
      hitSound("resources/audio/Hit0.wav"),
      deathSound("resources/audio/Dead.wav") {
    SpriteRenderer *zombie =
        new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);
    Animator *animator = new Animator(associated);

    associated.AddComponent(zombie);
    associated.AddComponent(animator);

    animator->AddAnimation("walking", Animation(0, 3, 10));
    animator->AddAnimation("dead", Animation(5, 5, 0));

    animator->SetAnimation("walking");
}

void Zombie::Damage(int damage) {
    if (hitpoints <= 0)
        return;

    hitSound.Play(1);
    hitpoints -= damage;

    if (hitpoints <= 0) {
        hitpoints = 0;
        if (auto *anim = associated.GetComponent<Animator>()) {
            anim->SetAnimation("dead");
        }

        deathSound.Play(1);
    }
}

void Zombie::Update(float dt) {
    auto &input = InputManager::GetInstance();

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        int mouse_x = input.GetMouseX();
        int mouse_y = input.GetMouseY();

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
