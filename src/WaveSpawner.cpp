//
//  WaveSpawner.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#include "WaveSpawner.hpp"
#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>

WaveSpawner::WaveSpawner(GameObject& associated)
    : Component(associated),
      zombieCounter(0),
      zombieCooldownTimer(),
      currentWave(0)
{
    waves.emplace_back(5, 1.0f);
    waves.emplace_back(8, 0.8f);
    waves.emplace_back(12, 0.6f);
}

void WaveSpawner::Update(float dt) {
    zombieCooldownTimer.Update(dt);

    if (currentWave >= (int)waves.size()) {
        associated.RequestDelete();
        return;
    }

    Wave& wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() >= wave.cooldown) {

            // Gerar direção aleatória
            float angle = (rand() % 6283) / 1000.0f;
            float distance = 600.0f;
            float x = Camera::pos.x + Game::GetInstance().GetWidth() / 2  + std::cos(angle) * distance;
            float y = Camera::pos.y + Game::GetInstance().GetHeight() / 2 + std::sin(angle) * distance;

            GameObject* zombieGO = new GameObject();
            zombieGO->box.x = x;
            zombieGO->box.y = y;

            zombieGO->AddComponent(new Zombie(*zombieGO));
            Game::GetInstance().GetState().AddObject(zombieGO);

            zombieCounter++;
            zombieCooldownTimer.Restart();
        }
    }
    else {
        if (Zombie::zombieCount == 0) {
            currentWave++;
            zombieCounter = 0;
        }
    }
}
