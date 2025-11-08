//
//  Component.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 18/09/25.
//

#ifndef Component_hpp
#define Component_hpp

class GameObject;

class Component {
  public:
    Component(GameObject &associated);

    virtual ~Component();

    virtual void Start() {};
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

  protected:
    GameObject &associated;
};

#endif /* Component_hpp */
