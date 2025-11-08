//
//  Animation.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#include "Animation.hpp"

Animation::Animation(int frameStart, int frameEnd, float frameTime,
                     SDL_RendererFlip flip)
    : frameStart(frameStart),
      frameEnd(frameEnd),
      frameTime(frameTime),
      flip(flip) {}
