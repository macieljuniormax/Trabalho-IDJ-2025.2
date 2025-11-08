//
//  PlayerController.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 08/11/25.
//

#ifndef PlayerController_hpp
#define PlayerController_hpp

#include "Component.hpp"
#include "GameObject.hpp"

class PlayerController : public Component {
public:
    PlayerController(GameObject& associated);
    ~PlayerController() override = default;
    
    void Start() override;
    void Update(float dt) override;
    void Render() override;
};

#endif /* PlayerController_hpp */
