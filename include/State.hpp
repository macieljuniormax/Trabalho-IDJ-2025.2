//
//  State.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#ifndef State_hpp
#define State_hpp

#include "Sprite.hpp"
#include "Music.hpp"
#include "GameObject.hpp"

#include <vector>
#include <memory>

class State {
public:
    State();
    ~State();
    
    void LoadAssets();
    void Update(float dt);
    void Render();
    bool QuitRequested();
    void AddObject(GameObject* go);
    
private:
    Sprite bg;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif /* State_hpp */
