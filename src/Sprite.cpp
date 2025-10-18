//
//  Sprite.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include <iostream>

Sprite::Sprite()
    : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : texture(nullptr), width(0), height(0) {
    this->frameCountW = (frameCountW > 0 ? frameCountW : 1);
    this->frameCountH = (frameCountH > 0 ? frameCountH : 1);
    Open(file);
}

Sprite::~Sprite() { texture = nullptr; }

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);

    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
        std::cerr << "Erro ao consultar textura: " << SDL_GetError()
                  << std::endl;
        exit(1);
    }

    SetClip(0, 0, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, int w, int h) {
    SDL_Rect dstrect;
    dstrect.x = x - Camera::pos.x;
    dstrect.y = y - Camera::pos.y;
    dstrect.w = w;
    dstrect.h = h;

    if (SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect,
                       &dstrect)) {
        std::cerr << "Erro ao renderizar textura: " << SDL_GetError()
                  << std::endl;
        exit(1);
    }
}

int Sprite::GetWidth() {
    return (frameCountW > 0) ? width / frameCountW : width;
}

int Sprite::GetHeight() {
    return (frameCountH > 0) ? height / frameCountH : height;
}

bool Sprite::IsOpen() { return texture != nullptr; }

void Sprite::SetFrame(int frame) {
    if ((frame < 0) || (frame >= frameCountW * frameCountH)) {
        std::cerr << "Frame não existe!" << std::endl;
        return;
    }

    int w = width / (frameCountW > 0 ? frameCountW : 1);
    int h = height / (frameCountH > 0 ? frameCountH : 1);

    int row = frame / frameCountW;
    int col = frame % frameCountW;

    int x = col * w;
    int y = row * h;

    if (x + w > width)
        x = width - w;
    if (y + h > height)
        y = height - h;
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    SetClip(x, y, w, h);
}

void Sprite::SetFrameCount(int frameCountW, int frameCountH) {
    this->frameCountH = frameCountH;
    this->frameCountW = frameCountW;
}
