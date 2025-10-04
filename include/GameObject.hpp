//
//  GameObject.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Rect.hpp"

#include <vector>

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
    void AddComponent(Component *cpt);
    void RemoveComponent(Component *cpt);

    template <typename T> T *GetComponent() {
        long unsigned int index;
        for (index = 0; index < components.size(); index++) {
            T *component = dynamic_cast<T *>(components[index]);
            if (component != nullptr) {
                return component;
            }
        }
        return nullptr;
    }

  private:
    std::vector<Component *> components;
    bool isDead;
};

#endif /* GameObject_hpp */
