//
//  Character.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 07/11/25.
//

#ifndef Character_hpp
#define Character_hpp

#include "Component.hpp"
#include "GameObject.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"
#include <queue>
#include <string>

class Character : public Component {
  public:
    class Command {
      public:
        enum class CommandType { MOVE, SHOOT };

        Command(CommandType type, float x, float y) : type(type), pos(x, y) {}

        CommandType type;
        Vec2 pos;
    };

    Character(GameObject &associeated, std::string &sprite);
    ~Character() override;

    void Start() override;
    void Update(float dt) override;
    void Render() override;

    void Issue(Command task);

    static Character *player;

  private:
    std::weak_ptr<GameObject> gun;
    std::queue<Command> taskQueue;

    Vec2 speed;
    float linearSpeed = 0.0f;
    int hp = 0;
    Timer deathTimer;
};

#endif /* Character_hpp */
