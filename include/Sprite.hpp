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
#include "Vec2.hpp"
#include <string>

class Sprite {
  public:
    Sprite();
    Sprite(std::string file, int frameCountW = 1, int frameCountH = 1);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y, int w, int h, float angle = 0);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void SetFrame(int frame);
    void SetFrameCount(int frameCountW, int frameCountH);

    void SetCameraFollower(bool on) { cameraFollower = on; };

    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale() const;
    void SetFlip(SDL_RendererFlip flip);

  private:
    int width;
    int height;
    int frameCountW;
    int frameCountH;
    SDL_Texture *texture;
    SDL_Rect clipRect;

    bool cameraFollower;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Vec2 scale;
};

#endif /* Sprite_hpp */
