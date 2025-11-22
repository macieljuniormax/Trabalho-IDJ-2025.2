//
//  Character.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#include "Character.hpp"
#include "Animator.hpp"
#include "Bullet.hpp"
#include "Camera.hpp"
#include "Collider.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Gun.hpp"
#include "InputManager.hpp"
#include "Sound.hpp"
#include "SpriteRenderer.hpp"
#include "State.hpp"
#include "Zombie.hpp"

Character *Character::player = nullptr;

Character::Character(GameObject &associated, const std::string &sprite)
    : Component(associated), gun(), taskQueue(), speed(0.0f, 0.0f),
      linearSpeed(200.0f), hp(100), deathTimer(), damageCooldown() {

    SpriteRenderer *personagem = new SpriteRenderer(associated, sprite, 3, 4);
    associated.AddComponent(personagem);

    Animator *animator = new Animator(associated);
    associated.AddComponent(animator);

    animator->AddAnimation("idle", Animation(0, 5, 0.10f));
    animator->AddAnimation("walking", Animation(6, 9, 0.10f));
    animator->AddAnimation("dead", Animation(10, 11, 0.00f));

    animator->SetAnimation("idle");

    associated.AddComponent(new Collider(associated));

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
    damageCooldown.Update(dt);

    if (!taskQueue.empty()) {
        Command &command = taskQueue.front();

        if (command.type == Command::CommandType::MOVE) {
            float dirX = command.pos.x;
            float dirY = command.pos.y;

            float len = std::sqrt(dirX * dirX + dirY * dirY);
            if (len > 0.0f) {
                dirX /= len;
                dirY /= len;

                speed.x = dirX * linearSpeed;
                speed.y = dirY * linearSpeed;

                associated.box.x += speed.x * dt;
                associated.box.y += speed.y * dt;
            } else {
                speed.x = speed.y = 0.0f;
            }
        }
        else if (command.type == Command::CommandType::SHOOT) {
            if (auto sharedGun = gun.lock()) {
                if (auto *gunComponent = sharedGun->GetComponent<Gun>()) {
                    gunComponent->Shoot(command.pos);
                }
            }
        }
        else {
            speed.x = speed.y = 0.0f;
        }

        taskQueue.pop();
    } else {
        speed.x = 0.0f;
        speed.y = 0.0f;
    }

    // flip horizontal
    if (auto *sr = associated.GetComponent<SpriteRenderer>()) {
        if (std::abs(speed.x) > 0.01f) {
            sr->SetFrame(0, (speed.x < 0.0f) ? SDL_FLIP_HORIZONTAL
                                             : SDL_FLIP_NONE);
        }
    }

    const bool isDead = (hp <= 0);
    if (Animator *animator = associated.GetComponent<Animator>()) {
        if (isDead) {
            animator->SetAnimation("dead");
        } else {
            const bool isMoving =
                (std::abs(speed.x) > 0.01f || std::abs(speed.y) > 0.01f);
            animator->SetAnimation(isMoving ? "walking" : "idle");
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

void Character::Render() {}

void Character::Issue(Command task) { taskQueue.push(std::move(task)); }

void Character::NotifyCollision(GameObject &other) {
    if (other.GetComponent<Zombie>()) {
        if (this != Character::player) {
            return;
        }

        if (damageCooldown.Get() < 0.5f) {
            return;
        }
        damageCooldown.Restart();

        const int contactDamage = 10;
        hp -= contactDamage;

        Sound hitSound("resources/audio/Hit1.wav");
        hitSound.Play(1);

        if (hp <= 0) {
            Sound deathSound("resources/audio/Dead.wav");
            deathSound.Play(1);

            if (this == Character::player) {
                Camera::Unfollow();
            }

            associated.RequestDelete();
        }

        return;
    }

    Bullet *bullet = other.GetComponent<Bullet>();
    if (!bullet)
        return;

    if (bullet->targetsPlayer) {
        if (this != Character::player)
            return;
    } else {
        if (this == Character::player)
            return;
    }

    if (damageCooldown.Get() < 0.5f)
        return;
    damageCooldown.Restart();

    hp -= bullet->GetDamage();

    Sound hitSound("resources/audio/Hit1.wav");
    hitSound.Play(1);

    if (hp <= 0) {
        Sound deathSound("resources/audio/Dead.wav");
        deathSound.Play(1);

        if (this == Character::player) {
            Camera::Unfollow();
        }

        associated.RequestDelete();
    }
}
