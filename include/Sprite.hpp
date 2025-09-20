//
//  Sprite.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#define INCLUDE_SDL_IMAGE

#include <string>

#include "SDL_include.h"

class Sprite {
public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();
    
    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);
    
private:
    int width;
    int height;
    int frameCountW;
    int frameCountH;
    SDL_Texture* texture;
    SDL_Rect clipRect;
};

#endif /* Sprite_hpp */
