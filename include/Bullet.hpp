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
           float maxDistance, bool targetsPlayer);

    void Start() override;  
    void Update(float dt) override;
    void Render() override;
    void NotifyCollision(GameObject &other) override;

    int GetDamage() const;
    bool targetsPlayer;

  private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};

#endif /* Bullet_hpp */
