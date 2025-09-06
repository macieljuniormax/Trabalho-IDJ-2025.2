//
//  Music.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 06/09/25.
//

#include "Music.hpp"

Music::Music() : music(nullptr){}

Music::Music(std::string file) : music(nullptr) {
    Open(file);
}

Music::~Music() {
    if (music != nullptr) {
        Stop();
        Mix_FreeMusic(music);
    }
}

void Music::Play(int times) {
    if (music == nullptr) {
        std::cerr << "Erro: nenhuma música carregada" << std::endl;
        return;
    }
    
    if (Mix_PlayMusic(music, times)  == -1) {
        std::cerr << "Erro ao reproduzir música: " << Mix_GetError() << std::endl;
    }
}

void Music::Stop(int msToStop) {
    if (music == nullptr) {
        std::cerr << "Erro: nenhuma música carregada" << std::endl;
        return;
    }
    
    if (Mix_FadeOutMusic(msToStop) == 0) {
        std::cerr << "Erro: nenhuma música em execução" << std::endl;
    }
}

void Music::Open(std::string file) {
    if (IsOpen()) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}


