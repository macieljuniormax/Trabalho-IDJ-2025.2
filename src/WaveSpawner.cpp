//
//  WaveSpawner.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#include "WaveSpawner.hpp"
#include "AIController.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Zombie.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

WaveSpawner::WaveSpawner(GameObject &associated)
    : Component(associated), zombieCounter(0), zombieCooldownTimer(),
      currentWave(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    waves.emplace_back(5, 1.0f);
    waves.emplace_back(8, 0.8f);
    waves.emplace_back(12, 0.6f);
}

void WaveSpawner::Update(float dt) {
    if (!npcSpawned) {
        for (int i = 0; i < 2; ++i) {
            GameObject *npcGO = new GameObject();

            float baseX = Camera::pos.x + 400.0f + i * 80.0f;
            float baseY = Camera::pos.y + 300.0f;

            npcGO->box.x = baseX;
            npcGO->box.y = baseY;

            auto *character = new Character(*npcGO, "resources/img/NPC.png");
            npcGO->AddComponent(character);

            npcGO->AddComponent(new AIController(*npcGO));

            Game::GetInstance().GetState().AddObject(npcGO);
        }

        npcSpawned = true;
    }

    zombieCooldownTimer.Update(dt);

    if (currentWave >= static_cast<int>(waves.size())) {
        associated.RequestDelete();
        return;
    }

    Wave &wave = waves[currentWave];

    if (zombieCounter < wave.zombies) {
        if (zombieCooldownTimer.Get() >= wave.cooldown) {
            float angle = static_cast<float>(std::rand() % 6283) / 1000.0f;
            float distance = 600.0f;

            float x = Camera::pos.x + Game::GetInstance().GetWidth() / 2.0f +
                      std::cos(angle) * distance;
            float y = Camera::pos.y + Game::GetInstance().GetHeight() / 2.0f +
                      std::sin(angle) * distance;

            GameObject *zombieGO = new GameObject();
            zombieGO->box.x = x;
            zombieGO->box.y = y;

            zombieGO->AddComponent(new Zombie(*zombieGO));
            Game::GetInstance().GetState().AddObject(zombieGO);

            zombieCounter++;
            zombieCooldownTimer.Restart();
        }
    } else {
        // só avança para a próxima wave quando não houver mais zumbis vivos
        if (Zombie::zombieCount == 0) {
            currentWave++;
            zombieCounter = 0;
        }
    }
}

void WaveSpawner::Render() {}
