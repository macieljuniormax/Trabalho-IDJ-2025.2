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

    background->AddComponent(
        new SpriteRenderer(*background, "resources/img/Background.png"));

    AddObject(background);

    /* Mapa (TileMap) */
    GameObject *mapGO = new GameObject();
    TileSet *tileSet = new TileSet(64, 64, "resources/img/Tileset.png");
    TileMap *tileMap = new TileMap(*mapGO, "resources/map/map.txt", tileSet);

    mapGO->box.x = 0;
    mapGO->box.y = 0;

    mapGO->AddComponent(tileMap);

    AddObject(mapGO);

    /* Zombies */
    GameObject *zombieGO1 = new GameObject();
    zombieGO1->box.x = 600;
    zombieGO1->box.y = 450;
    zombieGO1->AddComponent(new Zombie(*zombieGO1));
    AddObject(zombieGO1);

    GameObject *zombieGO2 = new GameObject();
    zombieGO2->box.x = 400;
    zombieGO2->box.y = 250;
    zombieGO2->AddComponent(new Zombie(*zombieGO2));
    AddObject(zombieGO2);

    GameObject *zombieGO3 = new GameObject();
    zombieGO3->box.x = 800;
    zombieGO3->box.y = 120;
    zombieGO3->AddComponent(new Zombie(*zombieGO3));
    AddObject(zombieGO3);
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
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
