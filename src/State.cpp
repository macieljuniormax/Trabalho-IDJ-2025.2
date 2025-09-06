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

void State::LoadAssets() {
    bg.Open("resources/img/Background.png");
    music.Open("resources/audio/BGM.wav");
}

void State::Update(float) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    if (bg.IsOpen()) {
        bg.Render(0, 0);
    }
}

bool State::QuitRequested() {
    return quitRequested;
}
