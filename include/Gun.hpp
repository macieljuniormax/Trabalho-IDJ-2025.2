//
//  Gun.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#ifndef Gun_hpp
#define Gun_hpp

#include "Component.hpp"
#include "Sound.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"
#include <memory>

class Gun : public Component {
  public:
    Gun(GameObject &associated, std::weak_ptr<GameObject> character);

    void Update(float dt) override;
    void Render() override;
    void Shoot(const Vec2 &target);

  private:
    Sound shotSound;
    Sound reloadSound;

    int cooldownState = 0;
    Timer cdTimer;

    std::weak_ptr<GameObject> character;
    float angle = 0.0f;
    
    bool isPlayerGun;
};

#endif /* Gun_hpp */
