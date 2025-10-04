//
//  TileSet.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 30/09/25.
//

#ifndef TileSet_hpp
#define TileSet_hpp

#include "Sprite.hpp"

#include <string>

class TileSet {
  public:
    TileSet(int tileWidth, int tileheight, const std::string &file);

    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth() const { return tileWidth; };
    int GetTileHeight() const { return tileHeight; };

  private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;
    int tileCount;
};

#endif /* TileSet_hpp */
