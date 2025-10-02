//
//  TileMap.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 01/10/25.
//

#include "TileMap.hpp"

TileMap::TileMap(GameObject& associated, const std::string& file, TileSet* tileSet)
    : Component(associated) {
    SetTileSet(tileSet);
    Load(file);
}


