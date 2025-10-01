//
//  TileSet.cpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 30/09/25.
//

#include "TileSet.hpp"

#include <iostream>

TileSet::TileSet(int tileWidth, int tileheight, const std::string &file)
    : tileSet(), tileWidth(tileWidth), tileHeight(tileheight), tileCount(0) {

    tileSet.Open(file);

    if (!tileSet.IsOpen()) {
        std::cerr << "Erro: não foi possível abrir o TileSet" << std::endl;
        return;
    }

    int cols = (tileWidth > 0) ? (tileSet.GetWidth() / tileWidth) : 0;
    int rows = (tileheight > 0) ? (tileSet.GetHeight() / tileheight) : 0;

    if (cols <= 0 || rows <= 0) {
        std::cerr << "TileSet: dimensões inválidas para o grid" << std::endl;
        cols = rows = 0;
        return;
    }

    tileCount = cols * rows;

    if (cols > 0 && rows > 0) {
        tileSet.SetFrameCount(cols, rows);
    }
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
    if (tileCount == 0 || index >= tileCount) {
        std::cerr << "Índice fora de range" << std::endl;
        return;
    }
    
    tileSet.SetFrame(index);
    tileSet.Render(x, y, tileWidth, tileHeight);
}
