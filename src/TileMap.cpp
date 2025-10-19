//
//  TileMap.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 01/10/25.
//

#include "TileMap.hpp"
#include "Camera.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>


static inline int ViewW() { return 1200; }
static inline int ViewH() { return 900; }

TileMap::TileMap(GameObject &associated, const std::string &file,
                 TileSet *tileSet)
    : Component(associated), tileSet(tileSet), mapWidth(0), mapHeight(0),
      mapDeth(0) {

    if (!file.empty()) {
        Load(file);
    }
}

void TileMap::Load(const std::string file) {
    std::ifstream in(file);

    if (!in.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo" << std::endl;
    }

    char comma;
    int value;

    if (!(in >> mapWidth >> comma >> mapHeight >> comma >> mapDeth >> comma)) {
        std::cerr << "Dimensões inválidas" << std::endl;
    }
    
    parallaxX.assign(mapDeth, 1.0f);
    parallaxY.assign(mapDeth, 1.0f);

    tileMatrix.clear();
    tileMatrix.reserve(mapWidth * mapHeight * mapDeth);

    for (std::size_t d = 0; d < mapDeth; ++d) {
        for (std::size_t h = 0; h < mapHeight; ++h) {
            for (std::size_t w = 0; w < mapWidth; ++w) {
                if (!(in >> value)) {
                    std::cerr << "Falha na leitura" << std::endl;
                    return;
                }

                tileMatrix.push_back(value);

                if (!(in >> comma)) {
                    std::cerr << "Vírgula esperada não encontrada" << std::endl;
                    return;
                }
            }
        }
    }
}

void TileMap::SetTileSet(TileSet *tileSet) { this->tileSet.reset(tileSet); }

int &TileMap::At(int x, int y, int z) {
    const int index = x + y * mapWidth + z * mapWidth * mapHeight;

    if (index < 0 || index >= tileMatrix.size()) {
        std::cerr << "Índice fora do intervalo" << std::endl;

        static int dummy = -1;

        return dummy;
    }

    return tileMatrix[index];
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDeth; ++layer) {
        RenderLayer(layer);
    }
}

void TileMap::Update(float dt) {}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) {
        std::cerr << "TileSet não definido" << std::endl;
        return;
    }
    
    if (layer < 0 || layer >= mapDeth) return;

    const int tileWidh = tileSet->GetTileWidth();
    const int tileHeight = tileSet->GetTileHeight();
    
    const float px = (layer < (int)parallaxX.size()) ? parallaxX[layer] : 1.0f;
    const float py = (layer < (int)parallaxY.size()) ? parallaxY[layer] : 1.0f;

    for (std::size_t y = 0; y < mapHeight; ++y) {
        for (std::size_t x = 0; x < mapWidth; ++x) {
            const int tileIndex =
                At(static_cast<int>(x), static_cast<int>(y), layer);
            
            if (tileIndex < 0) continue;

            const int drawX = (associated.box.x + x * tileWidh) - Camera::pos.x * px;
            const int drawY = (associated.box.y + y * tileHeight) - Camera::pos.y * py;
            
            tileSet->RenderTile(tileIndex, drawX, drawY);
        }
    }
}

void TileMap::SetParallax(int layer, float px, float py) {
    if (layer < 0 || layer >= mapDeth) return;
    
    if (parallaxX.size() != mapDeth) {
        parallaxX.assign(mapDeth, 1.0f);
        parallaxY.assign(mapDeth, 1.0f);
    }
    
    parallaxX[layer] = px;
    parallaxY[layer] = py;
}
