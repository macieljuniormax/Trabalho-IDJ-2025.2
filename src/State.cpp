//
//  State.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "State.hpp"

State::State() {
    quitRequested = false;
    bg = new Sprite();
}

void State::LoadAssets() {
    bg->Open("resources/img/Background.png");
    // Abri Música aqui quando já tivermos
}

void State::Update(float) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    if (bg != nullptr && bg->IsOpen()) {
        bg->Render(0, 0);
    }
}

bool State::QuitRequested() {
    return quitRequested;
}
