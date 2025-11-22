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
#include "Timer.hpp"

class Zombie : public Component {
  public:
    Zombie(GameObject &associated);

    void Damage(int damage);

    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;

  private:
    int hitpoints;
    bool hit;
    bool dead;

    Sound hitSound;
    Sound deathSound;

    Timer hitTimer;
    Timer deathTimer;
};

#endif /* Zombie_hpp */
