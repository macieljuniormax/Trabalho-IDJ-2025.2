//
//  State.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#ifndef State_hpp
#define State_hpp

#include "Sprite.hpp"

#include <stdio.h>

class State {
public:
    State();
    
    void LoadAssets();
    void Update(float dt);
    void Render();
    
    bool QuitRequested();
   
private:
    Sprite* bg;
//  Music music;
    bool quitRequested;
};

#endif /* State_hpp */
