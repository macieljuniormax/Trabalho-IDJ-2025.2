//
//  Main.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 03/09/25.
//

#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game& game = Game::GetInstance();
    game.Run();
    
    return 0;
}
