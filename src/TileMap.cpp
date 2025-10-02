//
//  TileMap.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 01/10/25.
//

#include "TileMap.hpp"

#include <fstream>
#include <iostream>
#include <cstddef>



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
    
    if (!(in >> mapWidth>> comma >> mapHeight >> comma >> mapDeth >> comma)) {
        std::cerr << "Dimensões inválidas" << std::endl;
    }
    
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

void TileMap::SetTileSet(TileSet *tileSet) {
    this -> tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    const int index = x + y * mapWidth + z * mapWidth * mapHeight;
    
    if (index < 0 || index >= tileMatrix.size()) {
        std::cerr << "Índice fora do intervalo" << std::endl;
        
        static int dummy = -1;
        
        return dummy;
    }
    
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer) {
    if (!tileSet) {
        std::cerr << "TileSet não definido" << std::endl;
        return;
    }
    
    const int tileWidh = tileSet -> GetTileWidth();
    const int tileHeight = tileSet -> GetTileHeight();
    
    for (std::size_t y = 0; y < mapHeight; ++y) {
        for (std::size_t x = 0; x < mapWidth; ++x) {
            const int tileIndex = At(static_cast<int>(x), static_cast<int>(y), layer);
            
            if (tileIndex) {
                const int drawX = associated.box.x + x * tileWidh;
                const int drawY = associated.box.y + y * tileHeight;
                tileSet -> RenderTile(tileIndex, drawX, drawY);
            }
        }
    }
}

void TileMap::Render() {
    for (int layer = 0; layer < mapDeth; ++layer) {
        RenderLayer(layer);
    }
}
