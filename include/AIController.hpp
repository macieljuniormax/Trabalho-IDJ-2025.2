//
//  AIController.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 22/11/25.
//

#ifndef AIController_hpp
#define AIController_hpp

#include "Component.hpp"
#include "Timer.hpp"
#include "Vec2.hpp"

class AIController : public Component {
  public:
    explicit AIController(GameObject &associated);
    ~AIController() override;

    void Update(float dt) override;
    void Render() override;

  private:
    enum class AIState { MOVING, RESTING };

    static int npcCounter;

    AIState state;
    Timer restTimer;
    Vec2 destination;
};

#endif /* AIController_hpp */
