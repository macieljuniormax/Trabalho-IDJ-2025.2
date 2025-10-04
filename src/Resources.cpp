//
//  Resources.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 04/10/25.
//

#include "Resources.hpp"
#include "Game.hpp"

#include <iostream>

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;

SDL_Texture *Resources::GetImage(const std::string &file) {
    auto it = imageTable.find(file);

    if (it != imageTable.end()) {
        return it->second;
    }

    SDL_Texture *texture =
        IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (!texture) {
        std::cerr << "Falha ao carregar textura" << IMG_GetError() << std::endl;
        return nullptr;
    }

    imageTable.emplace(file, texture);

    return texture;
}

Mix_Music *Resources::GetMusic(const std::string &file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    }

    Mix_Music *music = Mix_LoadMUS(file.c_str());

    if (!music) {
        std::cerr << "Falha ao carregar música" << Mix_GetError() << std::endl;
        return nullptr;
    }

    musicTable.emplace(file, music);
    return music;
}

Mix_Chunk *Resources::GetSound(const std::string &file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    }

    Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());

    if (!chunk) {
        std::cerr << "Falha ao carregar som" << Mix_GetError() << std::endl;
        return nullptr;
    }

    soundTable.emplace(file, chunk);
    return chunk;
}

void Resources::ClearImages() {
    for (auto &image : imageTable) {
        if (image.second != nullptr) {
            SDL_DestroyTexture(image.second);
        }
    }

    imageTable.clear();
}

void Resources::ClearMusics() {
    for (auto &music : musicTable) {
        if (music.second != nullptr) {
            Mix_FreeMusic(music.second);
        }
    }

    musicTable.clear();
}

void Resources::ClearSounds() {
    for (auto &sound : soundTable) {
        if (sound.second != nullptr) {
            Mix_FreeChunk(sound.second);
        }
    }

    soundTable.clear();
}
