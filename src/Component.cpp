//
//  Component.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#include "Component.hpp"
#include "GameObject.hpp"

Component::Component(GameObject &associated) : associated(associated) {}
Component::~Component() = default;
