//
//  Character.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#include "Character.hpp"
#include "Animator.hpp"
#include "SpriteRenderer.hpp"
#include "State.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Gun.hpp"

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
    State& state = Game::GetInstance().GetState();
    std::weak_ptr<GameObject> self = state.GetObjectPtr(&associated);
    
    GameObject* gunGO = new GameObject();
    
    gunGO->box.x = associated.box.x;
    gunGO->box.y = associated.box.y;
    
    gunGO->AddComponent(new Gun(*gunGO, self));
    
    gun = Game::GetInstance().GetState().AddObject(gunGO);
}
