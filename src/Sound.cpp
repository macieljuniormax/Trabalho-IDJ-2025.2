//
//  Sound.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/10/25.
//

#include "Sound.hpp"

#include <iostream>

Sound::Sound() : chunk(nullptr) {}

Sound::Sound(const std::string& file) : Sound() {
    Open(file);
}

Sound::~Sound() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
        chunk = nullptr;
    }
}

void Sound::Play(int times) {
    if (!chunk) {
        std::cerr << "Nenhum som carregado" << std::endl;
        return;
    }
    
    int loops = times > 0 ? times -1 : 0;
    
    if ((channel = Mix_PlayChannel(-1, chunk, loops)) == -1) {
        std::cerr << "Sound::Play: erro ao tocar som: " << Mix_GetError() << std::endl;
    }
}

void Sound::Stop() {
    if (chunk != nullptr  && channel != -1) {
        Mix_HaltChannel(channel);
        channel = -1;
    }
}

void Sound::Open(const std::string file) {
    if (chunk != nullptr) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
    
    chunk = Mix_LoadWAV(file.c_str());
    
    if (!chunk) {
        std::cerr << "Erro ao carregar som: " << Mix_GetError() << std::endl;
    }
    
}
