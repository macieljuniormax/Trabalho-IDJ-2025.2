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

#include "SDL_include.h"

#include <string>

class State;

class Game {
public:
    static Game& GetInstance();
    
//    State& GetState();
    SDL_Renderer* GetRenderer();
    
    void Run();
    
    ~Game();
    
private:
    Game(std::string title, int width, int height);
    
    static Game* instance;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    
//    State* state;
};

#endif /* Game_hpp */
