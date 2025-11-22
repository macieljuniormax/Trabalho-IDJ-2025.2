//
//  WaveSpawner.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#ifndef WaveSpawner_hpp
#define WaveSpawner_hpp

#include "Component.hpp"
#include "Timer.hpp"
#include "Wave.hpp"
#include <vector>

class WaveSpawner : public Component {
  public:
    WaveSpawner(GameObject &associated);

    void Update(float dt) override;
    void Render() override {}

  private:
    int zombieCounter;
    std::vector<Wave> waves;
    Timer zombieCooldownTimer;
    int currentWave;
};

#endif /* WaveSpawner_hpp */
