//
//  Animator.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "Animator.hpp"
#include "SpriteRenderer.hpp"

Animator::Animator(GameObject &associated)
    : Component(associated), frameStart(0), frameEnd(0), frameTime(0),
      currentFrame(0), timeElapsed(0) {}

void Animator::Update(float dt) {
    if (frameTime == 0.0f)
        return;

    timeElapsed += dt;

    if (timeElapsed > frameTime) {
        currentFrame++;
        timeElapsed -= frameTime;

        if (currentFrame > frameEnd) {
            currentFrame = frameStart;
        }

        SpriteRenderer *sr = associated.GetComponent<SpriteRenderer>();
        if (sr != nullptr)
            sr->SetFrame(currentFrame);
    }
}

void Animator::Render() {}

void Animator::SetAnimation(const std::string name) {
    auto it = animations.find(name);
    if (it == animations.end())
        return;

    const Animation &animation = it->second;

    frameStart = animation.frameStart;
    frameEnd = animation.frameEnd;
    frameTime = animation.frameTime;

    currentFrame = frameStart;
    timeElapsed = 0.0f;

    SpriteRenderer *sr = associated.GetComponent<SpriteRenderer>();
    if (sr != nullptr)
        sr->SetFrame(currentFrame);
}

void Animator::AddAnimation(const std::string name, const Animation &anim) {
    if (animations.find(name) == animations.end()) {
        animations.emplace(name, anim);
    }
}
