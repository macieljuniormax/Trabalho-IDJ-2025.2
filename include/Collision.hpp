//
//  Collision.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 21/11/25.
//

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "Rect.hpp"
#include "Vec2.hpp"

class Collision {
  public:
    static bool IsColliding(Rect &a, Rect &b, float angleOfA, float angleOfB);

  private:
    static float Mag(const Vec2 &p);
    static Vec2 Norm(const Vec2 &p);
    static float Dot(const Vec2 &a, const Vec2 &b);
    static Vec2 Rotate(const Vec2 &p, float angle);
};

#endif /* COLLISION_HPP */
