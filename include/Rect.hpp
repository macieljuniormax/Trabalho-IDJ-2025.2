//
//  Rect.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#ifndef Rect_hpp
#define Rect_hpp

#include "Vec2.hpp"

class Rect {
  public:
    float x, y, w, h;

    Rect();
    Rect(float x, float y, float w, float h);
    
    Vec2 GetCenter() const;
};

#endif /* Rect_hpp */
