//
//  GameObject.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#include "GameObject.hpp"
#include "Component.hpp"

GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {
    for (size_t i = components.size() - 1; i >= 0; i--) {
        delete *(components.begin() + i);
    }
    
    components.clear();
}

void GameObject::Update(float dt) {
    for (auto component : components) {
        component -> Update(dt);
    }
}

void GameObject::Render() {
    for (auto componet : components) {
        componet -> Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (*it == cpt) {
            delete *it;
            components.erase(it);
            break;
        }
    }
}
