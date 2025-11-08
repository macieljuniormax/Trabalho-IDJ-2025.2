//
//  Sprite.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "Sprite.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Resources.hpp"
#include <iostream>

Sprite::Sprite()
    : texture(nullptr), width(0), height(0), frameCountW(1), frameCountH(1),
      cameraFollower(false), scale(1.0f, 1.0f), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(std::string file, int frameCountW, int frameCountH)
    : texture(nullptr), width(0), height(0), cameraFollower(false),
      scale(1.0f, 1.0f), flip(SDL_FLIP_NONE) {
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

void Sprite::Render(int x, int y, int w, int h, float angle) {
    SDL_Rect dstrect;

    if (cameraFollower) {
        dstrect.x = x;
        dstrect.y = y;
    } else {
        dstrect.x = x - static_cast<int>(Camera::pos.x);
        dstrect.y = y - static_cast<int>(Camera::pos.y);
    }

    dstrect.w = static_cast<int>(w * scale.x);
    dstrect.h = static_cast<int>(h * scale.y);

    SDL_RendererFlip finalFlip = static_cast<SDL_RendererFlip>(flip);

    if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect,
                         &dstrect, angle, nullptr, finalFlip)) {
        std::cerr << "Erro ao renderizar textura (Ex): " << SDL_GetError()
                  << std::endl;
        exit(1);
    }
}

int Sprite::GetWidth() {
    int baseWidth = (frameCountW > 0) ? width / frameCountW : width;
    return static_cast<int>(baseWidth * scale.x);
}

int Sprite::GetHeight() {
    int baseHeight = (frameCountH > 0) ? height / frameCountH : height;
    return static_cast<int>(baseHeight * scale.y);
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

void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0.0f) {
        scale.x = scaleX;
    }
    if (scaleY != 0.0f) {
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale() const { return scale; }

void Sprite::SetFlip(SDL_RendererFlip newFlip) { flip = newFlip; }
