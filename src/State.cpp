//
//  State.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "State.hpp"

State::State() : bg(), music(), quitRequested(false){
    LoadAssets();
    music.Play();
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
    bg.Open("resources/img/Background.png");
    music.Open("resources/audio/BGM.wav");
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
    
    for (size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    for (size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    if (bg.IsOpen()) {
        bg.Render(0, 0);
    }
    
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
