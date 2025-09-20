//
//  Sprite.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "Sprite.hpp"
#include "Game.hpp"

#include <iostream>

Sprite::Sprite() : texture(nullptr){}

Sprite::Sprite(std::string file) : texture(nullptr){
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(std::string file) {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    
    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cerr << "Erro ao consultar textura: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;
    
    if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect)) {
        std::cerr << "Erro ao renderizar textura: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

