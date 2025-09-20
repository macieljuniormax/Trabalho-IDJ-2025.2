//
//  GameObject.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Rect.hpp"
#include <iostream>

class Component;


class GameObject {
public:
    Rect box;
    
    GameObject();
    ~GameObject();
    
    void Update(float dt);
    void Render();
    bool IsDead();
    
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);

    Component* GetComponent(std::string type);
    
private:
std::vector<Component*> components;
    bool isDead;
};

#endif /* GameObject_hpp */
