//
//  SprintRenderer.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(GameObject &associated)
    : Component(associated), sprite() {};

SpriteRenderer::SpriteRenderer(GameObject &associated, std::string file,
                               int frameCountW, int frameCountH)
    : Component(associated), sprite(file, frameCountW, frameCountH) {
    this->associated.box.w = sprite.GetWidth();
    this->associated.box.h = sprite.GetHeight();

    sprite.SetFrame(0);
}

void SpriteRenderer::Open(std::string file) { sprite.Open(file); }

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH) {
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render() {
    if (!sprite.IsOpen())
        return;

    const int w = sprite.GetWidth();
    const int h = sprite.GetHeight();

    sprite.Render(static_cast<int>(associated.box.x),
                  static_cast<int>(associated.box.y), w, h,
                  associated.angleDeg);
}

void SpriteRenderer::SetScale(float sx, float sy) {
    const float centerX = associated.box.x + associated.box.w * 0.5f;
    const float centerY = associated.box.y + associated.box.h * 0.5f;

    sprite.SetScale(sx, sy);

    associated.box.w = static_cast<float>(sprite.GetWidth());
    associated.box.h = static_cast<float>(sprite.GetHeight());

    associated.box.x = centerX - associated.box.w * 0.5f;
    associated.box.y = centerY - associated.box.h * 0.5f;
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip) {
    sprite.SetFrame(frame);
    sprite.SetFlip(flip);
}
