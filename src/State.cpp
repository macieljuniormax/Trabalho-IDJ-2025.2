//
//  State.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 05/09/25.
//

#include "State.hpp"
#include "SpriteRenderer.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Zombie.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"

#include <cstddef>

State::State() : music(), quitRequested(false) {
    LoadAssets();
    music.Play();
}

State::~State() { objectArray.clear(); }

void State::LoadAssets() {
    music.Open("resources/audio/BGM.wav");

    /* Background */
    GameObject *background = new GameObject();

    background->box.x = 0;
    background->box.y = 0;
    background->box.w = 1200;
    background->box.h = 900;
    
    SpriteRenderer *backgroundSR = new SpriteRenderer(*background, "resources/img/Background.png");
    
    backgroundSR->SetCameraFollower(true);
    background->AddComponent(backgroundSR);
    AddObject(background);

    /* Mapa (TileMap) */
    GameObject *mapGO = new GameObject();
    TileSet *tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    TileMap *tileMap = new TileMap(*mapGO, "resources/map/map.txt", tileSet);

    mapGO->box.x = 0;
    mapGO->box.y = 0;

    mapGO->AddComponent(tileMap);

    AddObject(mapGO);
}

void State::Update(float dt) {
    Camera::Update(dt);
    
    auto& input = InputManager::GetInstance();
    
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

void State::AddObject(GameObject *go) { objectArray.emplace_back(go); }
