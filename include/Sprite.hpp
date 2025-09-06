//
//  Sprite.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"

#include <string>

class Sprite {
public:
    Sprite();
    Sprite(std::string file);
    ~Sprite();
    
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    
private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif /* Sprite_hpp */
