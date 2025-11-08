//
//  Animation.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#ifndef Animation_hpp
#define Animation_hpp

#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"

class Animation {
  public:
    Animation(int frameStart, int frameEnd, float frameTime, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    int frameStart;
    int frameEnd;
    float frameTime;
    SDL_RendererFlip flip;
};

#endif /* Animation_hpp */
