//
//  Vec2.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#ifndef Vec2_hpp
#define Vec2_hpp

class Vec2 {
  public:
    float x, y;

    Vec2();
    Vec2(float x, float y);
    
    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator*(float rhs) const;
};

#endif /* Vec2_hpp */
