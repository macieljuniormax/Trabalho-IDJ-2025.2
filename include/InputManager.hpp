//
//  InputManager.hpp
//  Trabalho IDJ 2025.2
//
//  Created by Maciel Ferreira Custódio Júnior on 16/10/25.
//

#ifndef InputManager_hpp
#define InputManager_hpp

#include <unordered_map>

class InputManager {
public:
    static InputManager& GetInstance();
    
    void Update();
    
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);
    
    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);
    
    int GetMouseX() const { return mouseX; }
    int GetMouseY() const { return mouseY; }
    
    bool QuitRequested();
    
private:
    InputManager();
    ~InputManager();
    
    static constexpr int MOUSE_BUTTONS = 6;
    
    bool mouseState[MOUSE_BUTTONS];
    int mouseUpdate[MOUSE_BUTTONS];
    
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    
    bool quitRequested;
    
    int updateCounter;
    
    int mouseX;
    int mouseY;
};

#endif /* InputManager_hpp */

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define SPACE_KEY         SDLK_SPACE
