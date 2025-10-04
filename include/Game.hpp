//
//  Game.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/09/25.
//

#ifndef Game_hpp
#define Game_hpp

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "State.hpp"

#include <string>

#include "SDL_include.h"

class Game {
  public:
    ~Game();

    void Run();

    SDL_Renderer *GetRenderer();
    State &GetState();
    static Game &GetInstance();

  private:
    Game(std::string title, int width, int height);

    static Game *instance;

    SDL_Window *window;
    SDL_Renderer *renderer;

    State *state;
};

#endif /* Game_hpp */
