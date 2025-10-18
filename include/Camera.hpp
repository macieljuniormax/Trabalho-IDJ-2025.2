//
//  Camera.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/10/25.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "GameObject.hpp"
#include "Vec2.hpp"

class Camera {
public:
    static void Follow(GameObject* newFocus);
    static void Unfollow();
    static void Update(float dt);
    
    static Vec2 pos;
    static Vec2 speed;
    
private:
    static GameObject* focus;
};

#endif /* Camera_hpp */
