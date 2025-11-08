//
//  Bullet.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 08/11/25.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "Component.hpp"
#include "Vec2.hpp"

class Bullet : public Component {
  public:
    Bullet(GameObject &associated, float angle, float speed, int damage,
           float maxDistance);

    void Update(float dt) override;
    void Render() override;

    int GetDamage() const;

  private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif /* Bullet_hpp */
