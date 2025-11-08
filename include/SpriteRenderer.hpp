//
//  SprintRenderer.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 20/09/25.
//

#ifndef SprintRenderer_hpp
#define SprintRenderer_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include <string>

class SpriteRenderer : public Component {
  public:
    SpriteRenderer(GameObject &associated);
    SpriteRenderer(GameObject &associated, std::string file,
                   int frameCountW = 1, int frameCountH = 1);

    void Open(std::string file);
    void SetFrameCount(int frameCountW, int frameCountH);
    void Update(float dt) override;
    void Render() override;

    void SetCameraFollower(bool on) { sprite.SetCameraFollower(on); };

    void SetScale(float scaleX, float scaleY);
    void SetFrame(int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

  private:
    Sprite sprite;
};

#endif /* SprintRenderer_hpp */
