//
//  TileMap.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 01/10/25.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "TileSet.hpp"

#include <string>
#include <vector>
#include <memory>

class TileMap : public Component {
public:
    TileMap(GameObject& associated, const std::string& file, TileSet* tileSet);
    
    void Load(std::string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void Render();
    void RenderLater(int layer);
    
    int GetWidth() const { return mapWidth; };
    int GetHeight() const { return mapHeight; };
    int GetDepth() const { return mapDeth; };
    
private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth;
    int mapHeight;
    int mapDeth;
};

#endif /* TileMap_hpp */
