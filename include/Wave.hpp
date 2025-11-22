//
//  Wave.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#ifndef Wave_hpp
#define Wave_hpp

class Wave {
  public:
    int zombies;
    float cooldown;

    Wave(int zombies, float cooldown) : zombies(zombies), cooldown(cooldown) {}
};

#endif /* Wave_hpp */
