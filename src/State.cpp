//
//  State.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "State.hpp"
#include "Camera.hpp"
#include "Character.hpp"
#include "InputManager.hpp"
#include "SpriteRenderer.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Zombie.hpp"
#include "PlayerController.hpp"
#include "Collider.hpp"
#include "Collision.hpp"
#include "WaveSpawner.hpp"

#include <cstddef>

State::State() : music(), quitRequested(false), started(false) {}

void State::Start() {
    if (started)
        return;

    LoadAssets();
    music.Play();

    for (auto &sp : objectArray) {
        if (sp) {
            sp->Start();
        }
    }

    started = true;
}

State::~State() { objectArray.clear(); }

void State::LoadAssets() {
    music.Open("resources/audio/BGM.wav");

    /* Background */
    {
        GameObject *background = new GameObject();

        background->box.x = 0;
        background->box.y = 0;
        background->box.w = 1200;
        background->box.h = 900;

        SpriteRenderer *backgroundSR =
            new SpriteRenderer(*background, "resources/img/Background.png");

        backgroundSR->SetCameraFollower(true);
        background->AddComponent(backgroundSR);
        AddObject(background);
    }

    /* Mapa (TileMap) */
    {
        GameObject *mapGO = new GameObject();
        TileSet *tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
        TileMap *tileMap = new TileMap(*mapGO, "resources/map/map.txt", tileSet);

        tileMap->SetParallax(0, 0.3f, 0.3f);
        tileMap->SetParallax(1, 1.0f, 1.0f);

        mapGO->box.x = 0;
        mapGO->box.y = 0;

        mapGO->AddComponent(tileMap);

        AddObject(mapGO);
    }

    /* Personagem Jogável*/
    {
        GameObject *playerGO = new GameObject();
        playerGO->box.x = 1280.0f;
        playerGO->box.y = 1280.0f;

        Character *character = new Character(*playerGO, "resources/img/Player.png");
        PlayerController *playerController = new PlayerController(*playerGO);
        
        playerGO->AddComponent(character);
        playerGO->AddComponent(playerController);

        std::weak_ptr<GameObject> playerPtr = AddObject(playerGO);
        Camera::Follow(playerGO);
    }
    
    /* Wave Spawner */
    {
        GameObject* spawnerGO = new GameObject();
        spawnerGO->box.x = 0.0f;
        spawnerGO->box.y = 0.0f;

        spawnerGO->AddComponent(new WaveSpawner(*spawnerGO));
        AddObject(spawnerGO);
    }
}

void State::Update(float dt) {
    Camera::Update(dt);

    auto &input = InputManager::GetInstance();

    if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    if (input.KeyPress(SPACE_KEY)) {
        int mouse_x = Camera::pos.x + input.GetMouseX();
        int mouse_y = Camera::pos.y + input.GetMouseY();

        GameObject *zombie = new GameObject();
        zombie->box.x = mouse_x;
        zombie->box.y = mouse_y;
        zombie->AddComponent(new Zombie(*zombie));
        AddObject(zombie);
    }

    for (std::size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    for (std::size_t i = 0; i < objectArray.size(); ++i) {
        auto &objA = objectArray[i];
        if (!objA) continue;

        Collider *colA = objA->GetComponent<Collider>();
        if (!colA) continue;

        for (std::size_t j = i + 1; j < objectArray.size(); ++j) {
            auto &objB = objectArray[j];
            if (!objB) continue;

            Collider *colB = objB->GetComponent<Collider>();
            if (!colB) continue;

            if (Collision::IsColliding(colA->box,
                                       colB->box,
                                       objA->angleDeg,
                                       objB->angleDeg)) {
                objA->NotifyCollision(*objB);
                objB->NotifyCollision(*objA);
            }
        }
    }

    for (std::size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            i--;
        }
    }
}

void State::Render() {
    for (const auto &obj : objectArray) {
        obj->Render();
    }
}

bool State::QuitRequested() { return quitRequested; }

std::weak_ptr<GameObject> State::AddObject(GameObject *go) {
    std::shared_ptr<GameObject> sp(go);
    objectArray.push_back(sp);

    if (started && sp) {
        //        sp->Start()
    }

    return std::weak_ptr<GameObject>(sp);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for (auto &sp : objectArray) {
        if (sp.get() == go) {
            return std::weak_ptr<GameObject>(sp);
        }
    }

    return std::weak_ptr<GameObject>();
}
