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
    sprite.Render(associated.box.x, associated.box.y, associated.box.w,
                  associated.box.h);
}

void SpriteRenderer::SetFrame(int frame) { sprite.SetFrame(frame); }
