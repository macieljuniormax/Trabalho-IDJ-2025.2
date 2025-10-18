//
//  Timer.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/10/25.
//

#include "Timer.hpp"

Timer::Timer() : time(0.0f) {}

void Timer::Update(float dt) {
    time += dt;
}

void Timer::Restart() {
    time = 0.0f;
}

float Timer::Get() {
    return time;
}
