//
//  Animator.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#ifndef Animator_hpp
#define Animator_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Animation.hpp"

#include <string>
#include <unordered_map>

class Animator : public Component {
public:
    Animator(GameObject& associated);
    
    void Update(float dt);
    void Render();
    void SetAnimation(const std::string name);
    void AddAnimation(const std::string name, const Animation& anim);
    
private:
    std::unordered_map<std::string, Animation> animations;
    
    int frameStart;
    int frameEnd;
    float frameTime;
    int currentFrame;
    float timeElapsed;
};

#endif /* Animator_hpp */
