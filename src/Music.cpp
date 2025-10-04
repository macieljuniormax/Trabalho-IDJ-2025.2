//
//  Music.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 06/09/25.
//

#include "Music.hpp"
#include "Resources.hpp"

#include <iostream>

Music::Music() : music(nullptr) {}

Music::Music(const std::string &file) : Music() { Open(file); }

Music::~Music() {
    Stop();
    music = nullptr;
}

void Music::Play(int times) {
    if (music == nullptr) {
        std::cerr << "Erro: nenhuma música carregada" << std::endl;
        return;
    }

    if (Mix_PlayMusic(music, times) == -1) {
        std::cerr << "Erro ao reproduzir música: " << Mix_GetError()
                  << std::endl;
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

void Music::Open(const std::string &file) {
    music = Resources::GetMusic(file);

    if (music == nullptr) {
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen() { return music != nullptr; }
