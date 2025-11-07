//
//  Gun.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#include "Gun.hpp"
#include "SpriteRenderer.hpp"
#include "Animator.hpp"

Gun::Gun(GameObject& associated, std::weak_ptr<GameObject> character) : Component(associated), shotSound("resources/audio/Range.wav"), reloadSound("resources/audio/PumpAction.mp3"), cooldownState(0), cdTimer(), character(std::move(character)) {
    
    SpriteRenderer* gun = new SpriteRenderer(associated, "resources/img/Gun.png");
    associated.AddComponent(gun);
    
    Animator *animator = new Animator(associated);
    associated.AddComponent(animator);
    
    animator->AddAnimation("idle", Animation(0, 0, 0.10f));
    animator->AddAnimation("reloading", Animation(1, 5, 0.05f));
    
    animator->SetAnimation("idle");
}
