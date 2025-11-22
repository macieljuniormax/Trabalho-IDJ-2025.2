//
//  Collider.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 14/11/25.
//

#ifndef Collider_hpp
#define Collider_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Vec2.hpp"
#include "Rect.hpp"

class Collider : public Component {
public:
    Collider(GameObject &associeated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
    
    void Update(float dt) override;
    void Render() override;
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
    
    Rect box;
    
private:
    Vec2 scale;
    Vec2 offset;
};

#endif /* Collider_hpp */
