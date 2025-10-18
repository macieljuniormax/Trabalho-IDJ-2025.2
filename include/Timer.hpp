//
//  Timer.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/10/25.
//

#ifndef Timer_hpp
#define Timer_hpp

class Timer {
public:
    Timer();
    
    void Update(float dt);
    void Restart();
    float Get();
    
private:
    float time;
};

#endif /* Timer_hpp */
