//
//  Zombie.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sound.hpp"

class Zombie : public Component {
public:
    Zombie(GameObject& associated);

    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;

private:
    int hitpoints;
    Sound deathSound;
};

#endif /* Zombie_hpp */
