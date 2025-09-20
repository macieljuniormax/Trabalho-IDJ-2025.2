//
//  State.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "State.hpp"
#include "SpriteRenderer.hpp"
#include "Zombie.hpp"

#include <cstddef>

State::State() : music(), quitRequested(false){
    LoadAssets();
    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    music.Open("resources/audio/BGM.wav");

    /* Background */
    GameObject* background = new GameObject();

    background -> box.x = 0;
    background -> box.y = 0;
    background -> box.w = 1200;
    background -> box.h = 900;

    background -> AddComponent(new SpriteRenderer(*background, "resources/img/Background.png"));

    AddObject(background);
    
    
    /* Zombie */
    GameObject* zombieGO = new GameObject();
    Zombie* zombie = new Zombie(*zombieGO);
    
    zombieGO -> box.x = 600;
    zombieGO -> box.y = 600;

    zombieGO -> AddComponent(zombie);
    
    AddObject(zombieGO);
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }

    for (std::size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (std::size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    for (const auto& obj : objectArray) {
        obj -> Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::AddObject(GameObject *go) {
    objectArray.emplace_back(go);
}
