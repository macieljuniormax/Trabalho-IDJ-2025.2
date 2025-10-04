//
//  Animation.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#ifndef Animation_hpp
#define Animation_hpp

class Animation {
  public:
    Animation(int frameStart, int frameEnd, float frameTime);

    int frameStart;
    int frameEnd;
    float frameTime;
};

#endif /* Animation_hpp */
