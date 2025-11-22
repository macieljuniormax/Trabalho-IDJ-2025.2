//
//  Bullet.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 08/11/25.
//

#include "Bullet.hpp"
#include "Character.hpp"
#include "Collider.hpp"
#include "SpriteRenderer.hpp"
#include "Zombie.hpp"
#include <cmath>

Bullet::Bullet(GameObject &associated, float angle, float speedValue,
               int damageValue, float maxDistance, bool targetsPlayer)
    : Component(associated),
      speed(std::cos(angle) * speedValue, std::sin(angle) * speedValue),
      distanceLeft(maxDistance), damage(damageValue),
      targetsPlayer(targetsPlayer) {

    SpriteRenderer *sprite =
        new SpriteRenderer(associated, "resources/img/Bullet.png");
    associated.AddComponent(sprite);

    associated.angleDeg = angle * (180.0 / M_PI);

    if (auto *sr = associated.GetComponent<SpriteRenderer>()) {
        sr->SetScale(0.75f, 0.75);
    }
}

void Bullet::Start() {
    associated.AddComponent(new Collider(associated));
}

void Bullet::Update(float dt) {
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    distanceLeft -= std::sqrt(speed.x * speed.x + speed.y * speed.y) * dt;

    if (distanceLeft <= 0.0f) {
        associated.RequestDelete();
    }
}

void Bullet::Render() {}

int Bullet::GetDamage() const { return damage; }

void Bullet::NotifyCollision(GameObject &other) {

    if (other.GetComponent<Bullet>())
        return;

    if (auto *ch = other.GetComponent<Character>()) {
        if (targetsPlayer && Character::player != ch)
            return;
        if (!targetsPlayer && Character::player == ch)
            return;

        associated.RequestDelete();
        return;
    }

    if (other.GetComponent<Zombie>()) {
        associated.RequestDelete();
        return;
    }
}
