//
//  Zombie.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "Zombie.hpp"
#include "SpriteRenderer.hpp"

Zombie::Zombie(GameObject &associated) : Component(associated), hitpoints(100) {
    SpriteRenderer *zombie =
        new SpriteRenderer(associated, "resources/img/Enemy.png", 3, 2);

    zombie->SetFrame(1);

    associated.AddComponent(zombie);
}

void Zombie::Damage(int damage) {
    hitpoints -= damage;
    
    if (hitpoints <= 0) {
        SpriteRenderer *zombie =
            associated.GetComponent<SpriteRenderer>();
        
        if (zombie != nullptr) {
            zombie -> SetFrame(5);
        }
    }
}

void Zombie::Update(float dt) {
    Damage(1);
}

void Zombie::Render() {}
